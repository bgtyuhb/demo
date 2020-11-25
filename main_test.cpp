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
    MediaRecorderListenerTest(){
        ALOGD("YXK:MediaRecorderListenerTest construct");
    }

};

void MediaRecorderListenerTest::notify(int msg, int ext1, int ext2)
{
    ALOGD("YXK:notify");
    int ext =ext2;
    ext =0;
    if (msg == MEDIA_RECORDER_EVENT_INFO &&
        ext1 == MEDIA_RECORDER_INFO_MAX_DURATION_REACHED)
    {
        ALOGD("YXK:max duration reached");
        // mMediaRT.mMaxDurationCond->open();
    }
}

int main(){
  ALOGD("YXK");
  sp<MediaRecorderListenerTest> MLTest = new MediaRecorderListenerTest();
  
  android::String8 st("123");
  printf("1.String\n");
  int status;
  int fdname;
	//create MediaRecorder
	MediaRecorder *mRecorder = new MediaRecorder(String16("com.test.mediarecorder")); //app package name
  printf("2.new MediaRecorder\n");

  

	status = mRecorder->setAudioSource(AUDIO_SOURCE_MIC);
  printf("3.setAudioSource:%d\n",status);
  mRecorder->setListener(MLTest);

  status = mRecorder->enableAudioDeviceCallback(true);
  printf("3.enableAudioDeviceCallback:%d\n",status);

  //set outfile format
	status = mRecorder->setOutputFormat(OUTPUT_FORMAT_THREE_GPP);
  printf("3.setOutputFormat:%d\n",status);



	//set audio encoder
	status = mRecorder->setAudioEncoder(AUDIO_ENCODER_AAC);
  printf("3.setAudioEncoder:%d\n",status);
	//set some param
	const String8 params1("audio-param-number-of-channels=2"); //set sampling at 16khz
	status = mRecorder->setParameters(params1);
  printf("4.set sampling:%d\n",status);

	const String8 params2("audio-param-sampling-rate=44100"); //set sound channel to 2
	status = mRecorder->setParameters(params2);
  printf("5.set channel:%d\n",status);

	const String8 params3("audio-param-encoding-bitrate=320000"); //set encoding-bitrate to 256000
	status = mRecorder->setParameters(params3);
  printf("6.set encoding:%d\n",status);

  const String8 params4("max-filesize=9617551360");
  status = mRecorder->setParameters(params4);
  printf("7.set max-filesize:%d\n",status);

  const String8 params5("max-duration=5000");
  status = mRecorder->setParameters(params5);

  
  // printf("8.max-duration:%d\n",status);

  
  printf("setListener:%d\n",status);
	//set fd outfile, attention to linux permission
	FILE* fd = fopen("/sdcard/recorder.mp3","wb");
  FILE* fd2 = fopen("/sdcard/recorder1.acc","wb+");
  FILE* fd3 = fopen("/sdcard/recorder2.acc","wb+");
  if (fd == NULL) {
    printf("9.open failed\n");
  }else{
    printf("9.success opened\n" );
  }

  fdname = fileno(fd);
  printf("fdname:%d\n",fdname);
  fdname = fileno(fd2);
  printf("fdname2:%d\n",fdname);
  fdname = fileno(fd3);
  printf("fdname3:%d\n",fdname);
	status = mRecorder->setOutputFile(fileno(fd));
  printf("10.setOutputFile:%d\n",status);
  //The file character describes the transformation: fileno(fd)



	//prepare
	status = mRecorder->prepare();
  printf("11.prepare:%d.\n",status);
  //usleep(50000);
	//EXPECT_EQ(NO_ERROR,status);
	//start audio recording
	status = mRecorder->start();
  printf("12.start:%d.\n",status);
	//set sleep time
	sleep(10);
  

	//finish recording
	status = mRecorder->stop();
  printf("13.stop:%d.\n",status);

  fclose(fd);
  //mRecorder=NULL;
  return 0;
}
