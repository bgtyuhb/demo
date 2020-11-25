#include <utils/String8.h>
#include <utils/String16.h>
#include <utils/Log.h>
#include <media/mediarecorder.h>
#include <stdio.h>
#include <stdlib.h>

using namespace android;

class MediaRecorderListenerTest : public MediaRecorderListener
{
private:

public:
	void notify(int msg, int ext1, int ext2);
	MediaRecorderListenerTest() {
		ALOGD("YXK:MediaRecorderListenerTest construct");
	}

};

void MediaRecorderListenerTest::notify(int msg, int ext1, int ext2)
{
	ALOGD("YXK:notify");
	int ext = ext2;
	ext = 0;
	if (msg == MEDIA_RECORDER_EVENT_INFO &&
		ext1 == MEDIA_RECORDER_INFO_MAX_DURATION_REACHED)
	{
		ALOGD("YXK:max duration reached");
	}
}

int main() {
	ALOGD("YXK");
	sp<MediaRecorderListenerTest> MLTest = new MediaRecorderListenerTest();

	
	int status;
	int fdname;
	//create MediaRecorder
	MediaRecorder* mRecorder = new MediaRecorder(String16("com.test.mediarecorder")); //app package name

	status = mRecorder->setAudioSource(AUDIO_SOURCE_MIC);
	
	mRecorder->setListener(MLTest);

	status = mRecorder->enableAudioDeviceCallback(true);

	//set outfile format
	status = mRecorder->setOutputFormat(OUTPUT_FORMAT_THREE_GPP);

	//set audio encoder
	status = mRecorder->setAudioEncoder(AUDIO_ENCODER_AAC);

	//set some param
	const String8 params1("audio-param-number-of-channels=2"); //set sampling at 16khz
	status = mRecorder->setParameters(params1);

	const String8 params2("audio-param-sampling-rate=44100"); //set sound channel to 2
	status = mRecorder->setParameters(params2);

	const String8 params3("audio-param-encoding-bitrate=320000"); //set encoding-bitrate to 256000
	status = mRecorder->setParameters(params3);

	const String8 params4("max-filesize=9617551360");
	status = mRecorder->setParameters(params4);

	const String8 params5("max-duration=5000");
	status = mRecorder->setParameters(params5);


	//set fd outfile, attention to linux permission
	FILE* fd = fopen("/sdcard/recorder.mp3", "wb");

	fdname = fileno(fd);
	status = mRecorder->setOutputFile(fileno(fd));

	//prepare
	status = mRecorder->prepare();
	//usleep(50000);

	 //start audio recording
	status = mRecorder->start();

	//set sleep time
	sleep(10);

	//finish recording
	status = mRecorder->stop();

	fclose(fd);
	status = mRecorder->release();
	//mRecorder=NULL;
	
	return 0;
}
