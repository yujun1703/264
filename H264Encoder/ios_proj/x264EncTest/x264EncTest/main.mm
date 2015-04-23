//
//  main.m
//  x264EncTest
//
//  Created by kwen on 14-4-1.
//  Copyright (c) 2014年 tencent. All rights reserved.
//

#import <UIKit/UIKit.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/time.h>

#import "AppDelegate.h"

#include "../../../H264Enc/x264Encoder.h"

#define SAFE_DEL_MEM( buf ) if (buf) {delete[] buf; buf = NULL;}
#define SAFE_CLOSE( f ) if (f) {fflush(f);fclose(f);f=NULL;}

typedef enum
{
    RC_MODE_CQ=0,
    RC_MODE_CBR,
    RC_MODE_VBR,
    RC_MODE_MAX
} enc_rc_mode;


typedef struct EncCMD
{
	char		pSeqName[80];			// input yuv seqence file name
	char		pOutputFileName[80];    // output file name pointer
	char		profile[80];			// BP,MP,HP
	int			gop;				//
	int			gfGOP;				//
	int			spGOP;				//
    //
    int			fps;				// frame per second
    int			totalFrame;			// number of frames to encode
    int			width;				// width
    int			height;				// height
    int         kbps;				// bankwidth kbps
	enc_rc_mode    rc_mode;			// cq or cbr
    X264ENCPARAM::enumComplexity         speed_opt;					// cq
    int         rc_max_q;			// max_q
    int			rc_min_q;			// min_q
}EncCMD_PARAM;

EncCMD_PARAM gCmd = {"encode2.yuv", "test.264", "BP", 1500, 15, 0, 15, 2000, 640, 360, 200, RC_MODE_CBR, X264ENCPARAM::cp_normal , 45, 16};

void parse_cmd_enc( const int argc, char * argv[]);
void set_default_cmd(void);
int verfy_cmd(void);
void cmd_help(void);

EmFrameType getFrameType(int frameNum,int gop,int gfgop,int spgop);

int VQQ_GetTickCount()
{
#ifdef WIN32
	return GetTickCount();
#else
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
#endif
}


void init_encoder(CX264Encoder* e )
{
	X264ENCPARAM Info;
    
	Info.iBitrate = gCmd.kbps;
	Info.iFPS = gCmd.fps;
	Info.iHeight = gCmd.height;
	Info.iWidth  = gCmd.width;
	Info.iGOP = gCmd.gop;
    Info.igfGOP = gCmd.gfGOP;
    Info.ispGOP = gCmd.spGOP;
    Info.iMaxQP = gCmd.rc_max_q;
    Info.iMinQP = gCmd.rc_min_q;
    Info.cp = gCmd.speed_opt;
	if(0==strcmp((gCmd.profile),"BP"))
	{
		Info.eProfileLevel = X264ENCPARAM::emProfileLevel_Base;
	}
	else if(0==strcmp((gCmd.profile),"MP"))
	{
		Info.eProfileLevel = X264ENCPARAM::emProfileLevel_Main;
	}
	else if(0==strcmp((gCmd.profile),"HP"))
	{
		Info.eProfileLevel = X264ENCPARAM::emProfileLevel_High;
	}
    
	e->Init( Info );
}

/*
+ (NSString *) GetConnectingPath
{
    NSString *imagePath = [[NSBundle mainBundle] pathForResource:@"bali_640x360_P420" ofType:@"yuv"];
    
    return  imagePath;
}
 */

struct stat fileInfo;

int encoder(CX264Encoder* e, EncCMD_PARAM* e_p)
{
	FILE *fpInput;
	FILE *fpOutput;
	int ret = 1;
	int frame_count, nbytes, nTotalBytes = 0, width = e_p->width, height=e_p->height;
    int use_gf,use_sp,total;
    
	int frame_size = width * height * 3 / 2;
	unsigned char* inbuf = new unsigned char[frame_size];
	unsigned char* outbuf_encoder = NULL;
	unsigned int   fileSize,fileFrames;
	EmFrameType frame_type;
 //   char filepPath[256] = {0};
    
	//CTimer mytimer;
    
	use_gf = 0;
	use_sp = 0;
    
    
	if(e_p->gfGOP>0)
	{
		use_gf =1;
	}
    
	if(e_p->spGOP>0)
	{
		use_sp =1;
	}
    
    NSString *pathDocuments=[NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) objectAtIndex:0];
   // NSString *inputFileName= [NSString stringWithFormat:@"%s", e_p->pSeqName];
   // NSString *inputFilePath=[NSString stringWithFormat:@"%@/%@",pathDocuments,inputFileName];
    
  //  int len = [inputFilePath length];
    NSString *FilePath = [[NSBundle mainBundle] pathForResource:@"bali_640x360_P420" ofType:@"yuv"];

    int len = [FilePath length];
    
    char* inputFile = (char*)malloc(sizeof(char) * len + 1);
   // BOOL val = [inputFilePath getCString:inputFile maxLength:len + 1 encoding:NSUTF8StringEncoding];
    
//    NSLog(@"val : %d",val);
//    NSLog(@"path : %@",inputFilePath);
    BOOL val = [FilePath getCString:inputFile maxLength:len + 1 encoding:NSUTF8StringEncoding];
    
	if(stat(inputFile,&fileInfo))
	{
		printf("can't find this file\n");
		exit(1);
	}
	fileSize = fileInfo.st_size;
	
	fpInput = fopen(inputFile, "rb");
	if(!fpInput)
	{
		printf("can't open input file :%s.\n",e_p->pSeqName);
		exit(1);
	}
    
    NSString *outputFileName= [NSString stringWithFormat:@"%s", "test.h264"];
    NSString *outputFilePath=[NSString stringWithFormat:@"%@/%@",pathDocuments,outputFileName];
   // NSString *OutFile = [[NSBundle mainBundle] pathForResource:@"bali_640x360_P420" ofType:@"264"];

    len = [outputFilePath length];
    char* outputFile = (char*)malloc(sizeof(char) * len + 1);
    val = [outputFilePath getCString:outputFile maxLength:len + 1 encoding:NSUTF8StringEncoding];
    
//    NSLog(@"val : %d",val);
//    NSLog(@"path :    %@",outputFilePath);
 
	fpOutput = fopen(outputFile, "wb");
	if(!fpOutput)
	{
		printf("can't open output file.\n");
		exit(1);
	}
	fileFrames = fileInfo.st_size/frame_size;
    
    
	total = e_p->totalFrame;
    
	if(e_p->totalFrame==0)
	{
		total = fileFrames;
	}
	else if(e_p->totalFrame>fileFrames)
	{
		total = fileFrames;
	}
    
    printf("begin to encode.\n");
	frame_count = 0;
    int alltime = 0;
	while (frame_count < total)
	{
		if (frame_size !=(fread(inbuf, 1, frame_size, fpInput)))
		{
			break;
		}
		frame_type = getFrameType(frame_count,e_p->gop,e_p->gfGOP,e_p->spGOP);
        
		//mytimer.Start();
        int start_time = VQQ_GetTickCount();
		if ( true != e->Encode(inbuf, frame_size, &outbuf_encoder, (long*)&nbytes, frame_type) )
		{
			printf("Encode(): error");
			goto exit;
		}
        int end_time = VQQ_GetTickCount();
        alltime += (end_time - start_time);
		//mytimer.Stop();
        
		nTotalBytes += nbytes;
        
		if ( nbytes != fwrite(outbuf_encoder, 1, nbytes, fpOutput))
		{
			ret = 1;
			goto exit;
		}
		frame_count++;
        printf("frame_count = %d\n", frame_count);
	}
    
    ret = 0;
	//≤‚ ‘–Ú¡– gop spgop gfgop fps ƒø±Í¬Î¬   µº ¬Î¬  ÷°±‡¬Î ±º‰
	printf("%s_%s_%d_%d_%d\t",e_p->profile,e_p->pSeqName,e_p->gop,e_p->gfGOP,e_p->spGOP);
	printf("%d\t",e_p->fps);
	printf("%d\t",e_p->kbps);
	printf("%d\t",nTotalBytes*8/1000/(frame_count/e_p->fps));
	printf("fps %.2f fps\n", (double)frame_count * 1000/alltime);
    
exit:
	if (inbuf)
	{
		delete[] inbuf;
		inbuf = NULL;
	}
    
    free(outputFile);
    free(inputFile);
	SAFE_CLOSE(fpInput);
	SAFE_CLOSE(fpOutput);
    
	return ret;
}


/*
 encoder - decoder
 cbr or cq
 ppinloop
 rebuild.yuv size.txt ssim.txt
 */
void run_codec_test(char argc, char** argv)
{
	CX264Encoder e;
    
//	set_default_cmd();
//	parse_cmd_enc( argc, argv);
//	if(1==verfy_cmd())
//	{
//		cmd_help();
//	}

    init_encoder( &e );
    
    encoder( &e, &gCmd);
}


int main(int argc, char * argv[])
{
    run_codec_test( argc, argv );

    @autoreleasepool {
        return UIApplicationMain(argc, argv, nil, NSStringFromClass([AppDelegate class]));
    }
}

EmFrameType getFrameType(int frameNum,int gop,int gfgop,int spgop)
{
	int inner;
	EmFrameType frame_type;
    
	inner = frameNum%gop;
	if(0==inner)
	{
		frame_type = emType_IDR;
	}
	else
	{
		frame_type = emType_PnoSP;
        
		if(spgop > 0)
		{
			frame_type = emType_PwithSP;
			if(0==inner%spgop)
			{
				frame_type = emType_SP;
			}
		}
		
		if(gfgop > 0)
		{
			if(0==inner%gfgop)
			{
				frame_type = emType_GF;
			}
		}
	}
	return frame_type;
}
