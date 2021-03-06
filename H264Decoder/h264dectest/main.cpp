#ifdef __cplusplus
extern "C" {
#endif

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#ifndef WIN32
#include <sys/time.h>
#endif
#include "../h264decoder/ffmpeg-h264-decoder.h"

#define MY_JNI

#ifdef MY_JNI
#include <jni.h>
#include <android/log.h>
#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, "libnav",__VA_ARGS__)
 
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG  , "libnav",__VA_ARGS__)
 
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO   , "libnav",__VA_ARGS__)
 
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN   , "libnav",__VA_ARGS__)
 
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR  , "libnav",__VA_ARGS__)

#define EXPORT 
#else
#define EXPORT __declspec(dllexport)
#endif

//#include "../h264decoder/H264Decoder.h"

//#include "CTimer.h"
//#define STREAM_HEADER_TRACE 1
#define MAXWIDTH		1920
#define MAXHEIGHT		1200

#define YUV_BUF_SIZE	(MAXWIDTH*MAXHEIGHT*3/2)
#define G               (1024*1024*1024)

#ifdef WIN32
#pragma comment(lib, "h264decoder.lib")
#endif

struct stat fileInfo;

int fileNum;

char outputfile[80];
#define SKIPPACKETCOUNT		300000

int StreamYUVID =0;
#ifndef WIN32
int VQQ_GetTickCount()
{
	int unCurrentTime;

	struct timeval Current;
	if(gettimeofday(&Current, NULL) != 0)
	{
		unCurrentTime = 0;
	}
	else
	{
		unCurrentTime = Current.tv_sec * 1000  + Current.tv_usec/1000;
	}
	return unCurrentTime;
}
#endif

int main(int argc,  char* argv[])  
{
    dec_stats ret;
    void* decoder = NULL;
    unsigned int frame_count, yuv_buf_length, width, height;
    unsigned int flag;
    unsigned int currentIndex,packetEndIndex;

	unsigned int predWidth,predHeight;

    unsigned char* stream_buf;
    unsigned char* yuv_buf;
    FILE *fpRead,*fpWrite;
    int write_flag=0;

    unsigned int stream_len;
    unsigned int totalFrames=0;
	
	// used for packetloss test
    unsigned int doDecodeFlag;
    int     skipCount;

	predWidth = -1;
	predHeight= -1;
	fpWrite   = NULL;
	
	//CTimer mytimer;

    yuv_buf_length = 0;

    if(argc <2 || argc >3)
    {
        printf("testDec a.264 [a]\n");
        exit(1);
    }
    if(3==argc)
    {
	write_flag = 1;       
    }

    if(stat(argv[1],&fileInfo))
    {
        printf("can't find the %sfile.\n",argv[1]);
        exit(1);
    }
    stream_len = fileInfo.st_size;
    if(stream_len>G)
    {
        printf("large file\n");
    }
    stream_buf = (unsigned char*)malloc(stream_len);
    if(!stream_buf)
    {
        printf("not enough memory to malloc\n");
        exit(1);
    }

    yuv_buf = (unsigned char*)malloc(YUV_BUF_SIZE);
    if(!yuv_buf)
    {
        printf("not enough memory to malloc\n");
        exit(1);
    }

    fpRead = fopen(argv[1], "rb");
    if(!fpRead)
    {
        printf("can't open the .264 file\n");
        exit(1);
    }

    if(fread(stream_buf,1,stream_len,fpRead) !=stream_len)
    {
        printf("read the %s fail ");
        exit(1);
    }

    ffh264_create_decoder( &decoder );

    frame_count = 0;

	skipCount = 0;

    currentIndex   = 0;
    packetEndIndex = 4;
	int alltime = 0;
    while(1)
    {
        while(packetEndIndex<stream_len-4)
        {
            int tmpflag0,tmpflag1;

            tmpflag0 = (stream_buf[packetEndIndex] == 0) &&(stream_buf[packetEndIndex+1]==0) && (stream_buf[packetEndIndex+2]==0)&& (stream_buf[packetEndIndex+3]==1);
            tmpflag1 = (stream_buf[packetEndIndex] == 0) &&(stream_buf[packetEndIndex+1]==0) && (stream_buf[packetEndIndex+2]==1);

            if(tmpflag0||tmpflag1)
            {
                flag =1;
                break;
            }			

            packetEndIndex++;
        }

		doDecodeFlag = 1;

		skipCount++;

		if(totalFrames> 3 && skipCount >= SKIPPACKETCOUNT)
		{
			doDecodeFlag = 0;
			skipCount    = 0;
		}

        if(0==flag)
            packetEndIndex = stream_len;
		
#if STREAM_HEADER_TRACE
        printf("%02x %02x %02x %02x===",stream_buf[currentIndex+1],stream_buf[currentIndex+2],stream_buf[currentIndex+3],stream_buf[currentIndex+4]);
#endif

        yuv_buf_length = YUV_BUF_SIZE;

		if(doDecodeFlag)
		{
#ifndef WIN32
			int start_time = VQQ_GetTickCount();
#endif
			ret = ffh264_decode( decoder, stream_buf+currentIndex, packetEndIndex-currentIndex, 
				yuv_buf, &yuv_buf_length,&width, &height, &frame_count);	
#ifndef WIN32
			alltime += (VQQ_GetTickCount() - start_time);
#endif
		}

#if STREAM_HEADER_TRACE
        switch(ret)
        {
        case dec_success:
            {
                printf("frame:%d  bufferlength:%d ",frame_count ,yuv_buf_length);
                printf("OK\n");
                break;
            }
        case dec_padding:
            {
                printf("frame:%d  ", frame_count);
                printf("padding\n");
                break;
            }

        default:// dec_failed
            {
                printf("decode fail\n");
                break;
            }
        }
#endif

        if(dec_success==ret )
        {
             if(write_flag)
              {
				if((predWidth != width)||(predHeight != height))
				 {
				     if(fpWrite)
				     {
						fclose(fpWrite);
				     }

			     /*sprintf(outputfile,"%s_%d_%d_%i.yuv",argv[2],width,height,StreamYUVID);
		     	   fpWrite = fopen(outputfile, "wb");*/
			     sprintf(outputfile,"%s_%d_%d.yuv",argv[2],width,height);
			     fpWrite = fopen(outputfile, "ab+");
			     if(!fpWrite)
			     {
			        printf("can't open the write file.\n");
					exit(1);
			     }
			     predWidth  = width;
			     predHeight = height;
			     StreamYUVID ++;
				}
                fwrite(yuv_buf, 1, yuv_buf_length, fpWrite);
                fflush(fpWrite);			
            }

		    totalFrames ++;
        }

        if( 0==flag )
            break;

        currentIndex = packetEndIndex;

        packetEndIndex +=3;

        flag = 0;
    }
	printf("%-40s alltime=%6dms %5dms/pic, %6.2f fps\n",argv[1],alltime,alltime/totalFrames,totalFrames/(alltime/1000.0f));

    fclose( fpRead );
    if(fpWrite)
    {
       fclose(fpWrite);
    }
    free(stream_buf);
    free(yuv_buf);

    ffh264_release_decoder( &decoder );

    return 0;
}

#ifdef MY_JNI


JNIEXPORT jlong JNICALL Java_com_x264_VView_TestDec(JNIEnv* env, jobject thiz,jstring str264, jstring strYUV)
{	  
	
	 char *tmpYUVFilePath = (char*)(env)->GetStringUTFChars(strYUV,NULL);
	 char *tmp264FilePath = (char*)(env)->GetStringUTFChars(str264,NULL);
	
	  LOGD("#############test decoder  in JNI,TAG is libnav");

    dec_stats ret;
    void* decoder = NULL;
    unsigned int frame_count, yuv_buf_length, width, height;
    unsigned int flag;
    unsigned int currentIndex,packetEndIndex;

	  unsigned int predWidth,predHeight;

    unsigned char* stream_buf;
    unsigned char* yuv_buf;
    FILE *fpRead,*fpWrite;
    int write_flag=0;

    unsigned int stream_len;
    unsigned int totalFrames=0;
	
	// used for packetloss test
    unsigned int doDecodeFlag;
    int     skipCount;

	  predWidth = -1;
	  predHeight= -1;
	  fpWrite   = NULL;
	
	//CTimer mytimer;

    yuv_buf_length = 0;

 
   
	  write_flag = 0;       
   

    if(stat(tmp264FilePath,&fileInfo))
    {
        LOGD("can't find the %sfile.\n",tmp264FilePath);
        return 0;
    }
    stream_len = fileInfo.st_size;
    if(stream_len>G)
    {
        LOGD("large file\n");
    }
    stream_buf = (unsigned char*)malloc(stream_len);
    if(!stream_buf)
    {
        LOGD("not enough memory to malloc\n");
        return 0;
    }

    yuv_buf = (unsigned char*)malloc(YUV_BUF_SIZE);
    if(!yuv_buf)
    {
        LOGD("not enough memory to malloc\n");
        return 0;
    }

    fpRead = fopen(tmp264FilePath, "rb");
    if(!fpRead)
    {
        LOGD("can't open the .264 file\n");
        return 0;
    }

    if(fread(stream_buf,1,stream_len,fpRead) !=stream_len)
    {
        LOGD("read the %s fail ");
        return 0;
    }

    ffh264_create_decoder( &decoder );

    frame_count = 0;

	  skipCount = 0;

    currentIndex   = 0;
    packetEndIndex = 4;
	int alltime = 0;
    while(1)
    {
        while(packetEndIndex<stream_len-4)
        {
            int tmpflag0,tmpflag1;

            tmpflag0 = (stream_buf[packetEndIndex] == 0) &&(stream_buf[packetEndIndex+1]==0) && (stream_buf[packetEndIndex+2]==0)&& (stream_buf[packetEndIndex+3]==1);
            tmpflag1 = (stream_buf[packetEndIndex] == 0) &&(stream_buf[packetEndIndex+1]==0) && (stream_buf[packetEndIndex+2]==1);

            if(tmpflag0||tmpflag1)
            {
                flag =1;
                break;
            }			

            packetEndIndex++;
        }

		doDecodeFlag = 1;

		skipCount++;

		if(totalFrames> 3 && skipCount >= SKIPPACKETCOUNT)
		{
			doDecodeFlag = 0;
			skipCount    = 0;
		}

        if(0==flag)
            packetEndIndex = stream_len;
		
#if STREAM_HEADER_TRACE
        printf("%02x %02x %02x %02x===",stream_buf[currentIndex+1],stream_buf[currentIndex+2],stream_buf[currentIndex+3],stream_buf[currentIndex+4]);
#endif

        yuv_buf_length = YUV_BUF_SIZE;

		if(doDecodeFlag)
		{
#ifndef WIN32
			int start_time = VQQ_GetTickCount();
#endif
			ret = ffh264_decode( decoder, stream_buf+currentIndex, packetEndIndex-currentIndex, 
				yuv_buf, &yuv_buf_length,&width, &height, &frame_count);	
#ifndef WIN32
			alltime += (VQQ_GetTickCount() - start_time);
#endif
		}

#if STREAM_HEADER_TRACE
        switch(ret)
        {
        case dec_success:
            {
                printf("frame:%d  bufferlength:%d ",frame_count ,yuv_buf_length);
                printf("OK\n");
                break;
            }
        case dec_padding:
            {
                printf("frame:%d  ", frame_count);
                printf("padding\n");
                break;
            }

        default:// dec_failed
            {
                printf("decode fail\n");
                break;
            }
        }
#endif

        if(dec_success==ret )
        {
             if(write_flag)
              {
				if((predWidth != width)||(predHeight != height))
				 {
				     if(fpWrite)
				     {
						fclose(fpWrite);
				     }

			     /*sprintf(outputfile,"%s_%d_%d_%i.yuv",argv[2],width,height,StreamYUVID);
		     	   fpWrite = fopen(outputfile, "wb");*/
			    // sprintf(outputfile,"%s_%d_%d.yuv",argv[2],width,height);
			     fpWrite = fopen(tmpYUVFilePath, "ab+");
			     if(!fpWrite)
			     {
			        printf("can't open the write file.\n");
					exit(1);
			     }
			     predWidth  = width;
			     predHeight = height;
			     StreamYUVID ++;
				}
                fwrite(yuv_buf, 1, yuv_buf_length, fpWrite);
                fflush(fpWrite);			
            }
     //   LOGD("#############decode  frame %d", totalFrames);
		    totalFrames ++;
        }

        if( 0==flag )
            break;

        currentIndex = packetEndIndex;

        packetEndIndex +=3;

        flag = 0;
    }
	  LOGD("%-40s alltime=%6dms %5dms/pic, %6.2f fps\n",tmp264FilePath,alltime,alltime/totalFrames,totalFrames/(alltime/1000.0f));

    fclose( fpRead );
    if(fpWrite)
    {
       fclose(fpWrite);
    }
    free(stream_buf);
    free(yuv_buf);

    ffh264_release_decoder( &decoder );
  
  	(env)->ReleaseStringUTFChars(strYUV,tmpYUVFilePath);
	(env)->ReleaseStringUTFChars(str264,tmp264FilePath);
	LOGD("#############test log in JNI,TAG is libnav2");
	
	return alltime;
	
 // exit(0); //tmp added by sensong 201404
}

#endif

#ifdef __cplusplus
};
#endif


