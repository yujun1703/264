//#include "../X264Encoder/x264Encoder.h"


#define  _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "x264Encoder.h"

#ifdef WIN32
#include <windows.h>
#else
#include <stdarg.h>
#include <sys/time.h>
#include <utils/Log.h>
#endif


#define SAFE_DEL_MEM( buf ) if (buf) {delete[] buf; buf = NULL;}
#define SAFE_CLOSE( f ) if (f) {fflush(f);fclose(f);f=NULL;}

typedef enum
{
    RC_MODE_CQ=0,
    RC_MODE_CBR,
    RC_MODE_VBR,
    RC_MODE_MAX	
} enc_rc_mode;

char RATECONTROLMODE[RC_MODE_MAX][4] = {"CQ","CBR","VBR"};

enum ap_Has_arg { ap_no, ap_yes, ap_maybe };


struct ap_Option
{
		const char * name;		/* Long option name (maybe null) */
		void *param;
		enum ap_Has_arg has_arg;
		int  OPTYPE;
#define OPT_INT      0
#define OPT_FLOAT    1
#define OPT_STRING   2
};

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
    int         cq;					// cq 
    int         rc_max_q;			// max_q
    int			rc_min_q;			// min_q    
}EncCMD_PARAM;

EncCMD_PARAM gCmd;

struct ap_Option g_cmd_enc_opts[] =
{
	{ "-INPUT",    &gCmd.pSeqName,         ap_yes,     OPT_STRING},
	{ "-OUTPUT",   &gCmd.pOutputFileName,  ap_yes,     OPT_STRING},
	{ "-PROFILE",  &gCmd.profile,          ap_maybe,   OPT_STRING},
	{ "-GOP",      &gCmd.gop,              ap_yes,     OPT_INT},
	{ "-GFGOP",    &gCmd.gfGOP,            ap_maybe,   OPT_INT},
	{ "-SPGOP",    &gCmd.spGOP,            ap_maybe,   OPT_INT},
	{ "-FPS",      &gCmd.fps,              ap_yes,     OPT_INT},
	{ "-TOTAL",    &gCmd.totalFrame,	   ap_maybe,   OPT_INT},
	{ "-WIDTH",    &gCmd.width,            ap_yes,     OPT_INT},
	{ "-HEIGHT",   &gCmd.height,           ap_yes,     OPT_INT},
	{ "-KBPS",     &gCmd.kbps,             ap_yes,     OPT_INT},
	{ "-RCMODE",   &gCmd.rc_mode,          ap_maybe,   OPT_INT},
	{ "-CQ",       &gCmd.cq,               ap_maybe,   OPT_INT},
	{ "-MAXQ",     &gCmd.rc_max_q,         ap_maybe,   OPT_INT},
	{ "-MINQ",     &gCmd.rc_min_q,         ap_maybe,   OPT_INT},
	{  NULL,      NULL,					   ap_no,      OPT_INT}
};

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

void parse_cmd_enc( const int argc, char * argv[]);
void set_default_cmd(void);
int verfy_cmd(void);
void cmd_help(void);

EmFrameType getFrameType(int frameNum,int gop,int gfgop,int spgop);


void init_encoder(CX264Encoder* e )
{
	X264ENCPARAM Info;

	Info.iBitrate = gCmd.kbps*1000;
	Info.iFPS = gCmd.fps;
	Info.iHeight = gCmd.height;
	Info.iWidth  = gCmd.width;
	Info.iGOP = gCmd.gop;
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

struct stat fileInfo;


int encoder(CX264Encoder* e, EncCMD_PARAM* e_p)
{
	FILE *fpInput;
	FILE *fpOutput;    
	int ret = 1;
	int iGOP = e_p->gop, fps = e_p->fps;
	int frame_count, nbytes, nTotalBytes = 0, width = e_p->width, height=e_p->height;
    int use_gf,use_sp,total;
	int inner;

	int frame_size = width * height * 3 / 2;
	unsigned char* inbuf = new unsigned char[frame_size];	
	unsigned char* outbuf_encoder = NULL;
	unsigned int   fileSize,fileFrames;
	EmFrameType frame_type;

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


	if(stat(e_p->pSeqName,&fileInfo))
	{
		printf("can't find this file\n");
		exit(1);
	}
	fileSize = fileInfo.st_size;
	
	fpInput = fopen(e_p->pSeqName, "rb");
	if(!fpInput)
	{
		printf("can't open input file :%s.\n",e_p->pSeqName);
		exit(1);
	}
	fpOutput = fopen(e_p->pOutputFileName, "wb");
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
	}

       ret = 0;
	//测试序列 gop spgop gfgop fps 目标码率 实际码率 帧编码时间 
	printf("%s_%s_%d_%d_%d\t",e_p->profile,e_p->pSeqName,e_p->gop,e_p->gfGOP,e_p->spGOP);
	printf("%d\t",e_p->fps);
	printf("%d\t",e_p->kbps);
	printf("%d\t",nTotalBytes*8/1000/(frame_count/e_p->fps));			
	printf("fps %d\n",frame_count*1000/alltime);

exit:
	if (inbuf)
	{
		delete[] inbuf;
		inbuf = NULL;
	}

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

	set_default_cmd();    
	parse_cmd_enc( argc, argv);
	if(1==verfy_cmd())
	{
		cmd_help();
	}

	init_encoder( &e );

    encoder( &e, &gCmd);
}


int main(char argc, char**argv)
{
	run_codec_test( argc, argv );
        return true;
}

void parse_cmd_enc( const int argc,  char *  argv[])
{
	int argvIndex;
	char tmpcmd[80];
	struct ap_Option *pOption;

	if(argc<2)
	{
		cmd_help();
		exit(1);
	}

	argvIndex =1;	
	while(1)
	{
		pOption = g_cmd_enc_opts;
		strcpy(tmpcmd,argv[argvIndex]);
		//strupr(tmpcmd);

		while(pOption->name!=NULL )
		{
			if(0==strcmp(tmpcmd,pOption->name))
				break;
			else
				pOption++;
		}
		if(!pOption->name)
		{
			printf("error param input %s\n",argv[argvIndex]);
			exit(1);
		}
		if(argvIndex == argc)
		{
			printf("miss param value\n");
			exit(1);
		}
		switch(pOption->OPTYPE)
		{
			case OPT_INT:
				*(int *)(pOption->param) = strtol(argv[argvIndex+1],NULL,0);
				argvIndex +=2;
				break;
			case OPT_STRING:
				
				strcpy((char *)pOption->param,argv[argvIndex+1]);
				argvIndex +=2;
				break;
			default:
				printf("Error option type %d \n",pOption->OPTYPE);
				exit(1);
				break;
		}

		if(argvIndex== argc)
			break;
	}
}


void set_default_cmd(void)
{
	memset(&gCmd,0,sizeof(EncCMD_PARAM));
	strcpy(gCmd.profile,"BP");
}



int verfy_cmd(void)
{
	struct ap_Option *pOption;
	int flag =0;
	pOption = g_cmd_enc_opts;
	while(pOption->name!=NULL )
	{
		if(pOption->has_arg==ap_yes)
		{
			switch ( pOption->OPTYPE)
			{
				case OPT_INT:
					if(0==*(int *)(pOption->param))
					{
						printf("miss param %s\n",pOption->name);
						flag =1;
					}
				break;
				case OPT_STRING:
					if('\0'==(*(char *)pOption->param))
					{
						printf("miss param %s\n",pOption->name);
						flag =1;
					}				
				break;
			default:
				break;
			}
		}
		pOption++;
	}
	return flag;
}
void cmd_help(void)
{

	printf("-input   yuv(420p format) file name\n" \
		   "-output  annuxB format file name\n"    \
		   "-profile BP,MP,HP default[BP]   \n"    \
		   "-gop     gop                    \n"    \
		   "-gfgop   golden frame gop       \n"    \
		   "-spgop   sp gop                 \n"    \
		   "-fps     frame per second       \n"    \
		   "-total   frames to encode       \n"    \
		   "-width   sequence's width       \n"    \
		   "-height  sequence's height      \n"    \
		   "-kbps    kilo-bits per second\n");
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
