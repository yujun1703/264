//
//  main.m
//  x264DecTest
//
//  Created by Landyji on 14-6-4.
//  Copyright (c) 2014年 ___FULLUSERNAME___. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "AppDelegate.h"
#include <sys/time.h>
#include <sys/stat.h>
#include "../../../h264decoder/ffmpeg-h264-decoder.h"

char input_file_cr1[80] = "sr_1920x1080_excel.264";
char output_file_cr1[80] = "test1.yuv";
char input_file_cr2[80] = "sr_1920x1080_word.264";
char output_file_cr2[80] = "test2.yuv";
char input_file_cr3[80] = "sr_1920x1080_ppt.264";
char output_file_cr3[80] = "test3.yuv";
char input_file_cr4[80] = "sr_word_1440x900.264";
char output_file_cr4[80] = "test4.yuv";
char input_file_cr5[80] = "sr_excel_1440x900.264";
char output_file_cr5[80] = "test5.yuv";
char input_file_cr6[80] = "sr_ppt_1440x900.264";
char output_file_cr6[80] = "test6.yuv";


char input_file_b1[80] = "BP320x240_15_1S_emMe1_fast.264";
char input_file_b2[80] = "BP480x360_15_1S_emMe1_fast.264";
char input_file_b3[80] = "BP640x480_15_1S_emMe1_fast.264";
char input_file_b4[80] = "BP960x540_20_1S_emMe1_fast.264";
char input_file_b5[80] = "BP1280x720_20_1S_emMe1_fast.264";
char input_file_h1[80] = "HP320x240_15_2S_emMe3_best.264";
char input_file_h2[80] = "HP480x360_15_2S_emMe3_best.264";
char input_file_h3[80] = "HP640x480_15_2S_emMe3_best.264";
char input_file_h4[80] = "HP960x540_20_2S_emMe3_best.264";
char input_file_h5[80] = "HP1280x720_20_2S_emMe3_best.264";
char input_file_m1[80] = "MP320x240_15_1_5S_emMe2_normal.264";
char input_file_m2[80] = "MP480x360_15_1_5S_emMe2_normal.264";
char input_file_m3[80] = "MP640x480_15_1_5S_emMe2_normal.264";
char input_file_m4[80] = "MP960x540_20_1_5S_emMe2_normal.264";
char input_file_m5[80] = "MP1280x720_20_1_5S_emMe2_normal.264";

#define MAXWIDTH		1920
#define MAXHEIGHT		1200

#define YUV_BUF_SIZE	(MAXWIDTH*MAXHEIGHT*3/2)
#define G               (1024*1024*1024)

struct stat fileInfo;

int fileNum;

//char outputfile[80];
#define SKIPPACKETCOUNT		300000

int StreamYUVID =0;

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

int find_start_code (unsigned char *Buf, int zeros_in_startcode)
{
    int i;
    for (i = 0; i < zeros_in_startcode; i++)
        if(Buf[i] != 0)
            return 0;
    return Buf[i];
}

int get_next_nal(FILE* inpf, unsigned char* Buf)
{
    
    int pos = 0;
    int StartCodeFound = 0;
    int info2 = 0;
    int info3 = 0;
    while(!feof(inpf)&&(/*Buf[pos++]=*/fgetc(inpf))==0);
    
    while (pos < 3) Buf[pos++] = fgetc (inpf);
    while (!StartCodeFound)
    {
        if (feof (inpf))
        {
            //            return -1;
            return pos-1;
        }
        Buf[pos++] = fgetc (inpf);
        info3 = find_start_code(&Buf[pos-4], 3);
        if(info3 != 1)
            info2 = find_start_code(&Buf[pos-3], 2);
        StartCodeFound = (info2 == 1 || info3 == 1);
    }
    fseek (inpf, - 4 + info2, SEEK_CUR);
    return pos - 4 + info2;
}

int video_decode_example(const char *filename, const char *outfilename)
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
    
    unsigned int stream_len;
	unsigned int totalFrames=0;
	
	// used for packetloss test
	unsigned int doDecodeFlag;
	int     skipCount;
    
	predWidth = -1;
	predHeight= -1;
	fpWrite   = NULL;
    
    yuv_buf_length = 0;
    
    if(stat(filename, &fileInfo))
    {
        exit(1);
    }
    stream_len = fileInfo.st_size;
    
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
    
    fpRead = fopen(filename, "rb");
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
			int start_time = VQQ_GetTickCount();
			ret = ffh264_decode( decoder, stream_buf+currentIndex, packetEndIndex-currentIndex,
                                yuv_buf, &yuv_buf_length,&width, &height, &frame_count);
			alltime += (VQQ_GetTickCount() - start_time);
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
        
        if(dec_success==ret)
        {
			if((predWidth != width)||(predHeight != height))
			{
				if(fpWrite)
				{
					fclose(fpWrite);
				}
                
				/*sprintf(outputfile,"%s_%d_%d_%i.yuv",argv[2],width,height,StreamYUVID);
                 fpWrite = fopen(outputfile, "wb");*/
				//sprintf(outputfile,"%s_%d_%d.yuv",argv[2],width,height);
				fpWrite = fopen(outfilename, "wb");
				if(!fpWrite)
				{
					printf("can't open the write file.\n");
					exit(1);
				}
				predWidth  = width;
				predHeight = height;
				StreamYUVID ++;
			}
            
			totalFrames ++;
            fwrite(yuv_buf, 1, yuv_buf_length, fpWrite);
            fflush(fpWrite);
#if 0
            
			printf("\t\t\t\t\t frame %dX%d %d \n",width,height,totalFrames);
#endif
        }
        
        if( 0==flag )
            break;
        
        currentIndex = packetEndIndex;
        
        packetEndIndex +=3;
        
        flag = 0;
    }
	printf("%dX%d_%s alltime=%dms  %dns/pic %dfps\n",width,height,filename,alltime,alltime*1000/totalFrames, totalFrames*1000*10/alltime);
    
    fclose( fpRead );
    fclose( fpWrite);
    free(stream_buf);
    free(yuv_buf);
    
    ffh264_release_decoder( &decoder );
    
    return 0;
}

int hevc_dec_test( char *filename,  char *outfilename)
{
    //int frame_size = width * height * 3 / 2;
    NSString *pathDocuments=[NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) objectAtIndex:0];
    NSString *inputFileName= [NSString stringWithFormat:@"%s", filename];
    NSString *inputFilePath=[NSString stringWithFormat:@"%@/%@",pathDocuments,inputFileName];
    
    int len = [inputFilePath length];
    char* inputFile = (char*)malloc(sizeof(char) * len + 1);
    BOOL val = [inputFilePath getCString:inputFile maxLength:len + 1 encoding:NSUTF8StringEncoding];
    
	//if(stat(inputFile,&fileInfo))
	//{
	//	printf("can't find this file\n");
	//	exit(1);
	//}
    
    NSString *outputFileName= [NSString stringWithFormat:@"%s", outfilename];
    NSString *outputFilePath=[NSString stringWithFormat:@"%@/%@",pathDocuments,outputFileName];
    
    len = [outputFilePath length];
    char* outputFile = (char*)malloc(sizeof(char) * len + 1);
    val = [outputFilePath getCString:outputFile maxLength:len + 1 encoding:NSUTF8StringEncoding];
    
    video_decode_example(inputFile, outputFile);
    return 0;
}

int main(int argc, char * argv[])
{
#if 0
    hevc_dec_test(input_file_cr1, output_file_cr1);
        hevc_dec_test(input_file_cr2, output_file_cr2);
        hevc_dec_test(input_file_cr3, output_file_cr3);
        hevc_dec_test(input_file_cr4, output_file_cr4);
        hevc_dec_test(input_file_cr5, output_file_cr5);
        hevc_dec_test(input_file_cr6, output_file_cr6);
#else
    hevc_dec_test(input_file_b1, output_file_cr1);
    hevc_dec_test(input_file_b2, output_file_cr1);
    hevc_dec_test(input_file_b3, output_file_cr1);
    hevc_dec_test(input_file_b4, output_file_cr1);
    hevc_dec_test(input_file_b5, output_file_cr1);
    
    hevc_dec_test(input_file_h1, output_file_cr1);
    hevc_dec_test(input_file_h2, output_file_cr1);
    hevc_dec_test(input_file_h3, output_file_cr1);
    hevc_dec_test(input_file_h4, output_file_cr1);
    hevc_dec_test(input_file_h5, output_file_cr1);
    
    hevc_dec_test(input_file_m1, output_file_cr1);
    hevc_dec_test(input_file_m2, output_file_cr1);
    hevc_dec_test(input_file_m3, output_file_cr1);
    hevc_dec_test(input_file_m4, output_file_cr1);
    hevc_dec_test(input_file_m5, output_file_cr1);

#endif
    @autoreleasepool {
        return UIApplicationMain(argc, argv, nil, NSStringFromClass([AppDelegate class]));
    }
}
