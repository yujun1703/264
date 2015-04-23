#ifdef __cplusplus
extern "C" {
#endif

#include "x264Encoder.h"
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include "x264.h"
#include <time.h>
//高精度时间，精确到ms，甚至微秒
#include   <sys/time.h>
//surport log
//#include <utils/Log.h>
#include "common/common.h"

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

//x264_param_t param;
//x264_t *h = NULL;						/* H264_t是一个结构体，定义了encoder parameters 编码器参数*/


//做成全局的，测试编码
#define IN_PIC_WIDTH 352 //640
#define IN_PIC_HEIGHT 288 //480

#define GOP  15

//#define BUFDATA_MAX (720*576*4)
#define BUFDATA_MAX (640*480*4)

unsigned char indata[BUFDATA_MAX];
unsigned char outdata[BUFDATA_MAX];
static long l_encTime = 0;
x264_param_t *param;
x264_t *h;
x264_picture_t *pic_in, *pic_out;
x264_nal_t *nal;
//t264_t  *t; //new struct

CX264Encoder e;

int width = 0;
int height = 0;


static void x264_log_default( void *p_unused, int i_level, const char *psz_fmt, va_list arg )
{
    char *psz_prefix;
    char buf[1000] = {0};
    switch( i_level )
    {
        case X264_LOG_ERROR:
            psz_prefix = "error";
            break;
        case X264_LOG_WARNING:
            psz_prefix = "warning";
            break;
        case X264_LOG_INFO:
            psz_prefix = "info";
            break;
        case X264_LOG_DEBUG:
            psz_prefix = "debug";
            break;
        default:
            psz_prefix = "unknown";
            break;
    }
    vsprintf(buf, psz_fmt, arg );
    LOGD("%s", buf);
  //  fprintf( stderr, "x264 [%s]: ", psz_prefix );
 //   vfprintf( stderr, psz_fmt, arg );
}



int com_encoder_open(void)
{
	param = (x264_param_t *)x264_malloc( sizeof(x264_param_t) );	
	param->i_width         = IN_PIC_WIDTH;
	param->i_height        = IN_PIC_HEIGHT;	
	
	x264_param_default( param );
	
	param->i_width         = IN_PIC_WIDTH;
	param->i_height        = IN_PIC_HEIGHT;	
       param->rc.i_rc_method =  X264_RC_ABR;
       param->rc.i_bitrate = 200;
       param->pf_log = x264_log_default;
       param->i_log_level = X264_LOG_DEBUG;
       param->i_bframe = 0;
       param->b_cabac = 1;
       param->i_fps_den =1;
       param->i_fps_num = 30;
   //    param->b_open_gop = 1;
   //    param->

    if( ( h = x264_encoder_open( param ) ) == NULL )
    {
        LOGD("x264 [error]: x264_encoder_open failed\n" );
        return -1;
    }

    //x264_encoder_parameters( h, param );

    /* YV12p */
	pic_in = (x264_picture_t *)x264_malloc( sizeof(x264_picture_t) );
	pic_out = (x264_picture_t *)x264_malloc( sizeof(x264_picture_t) );

	x264_picture_init(pic_out);
	LOGD("sfsdfgsddgsgs");
	//x264_picture_alloc(pic_in, X264_CSP_I420, param->i_width, param->i_height);//melloc pic_in space
	memset(pic_in, 0, sizeof(x264_picture_t));

       pic_in->i_type = X264_TYPE_AUTO;
    pic_in->i_qpplus1 = X264_QP_AUTO;
    pic_in->i_pic_struct = X264_CSP_I420;

    pic_in->img.i_csp = X264_CSP_I420;
    pic_in->img.i_plane = 3;
	pic_in->img.i_csp = X264_CSP_I420;
	pic_in->img.i_plane = 3;
 	pic_in->img.i_stride[0] = param->i_width;
	pic_in->img.i_stride[1] = param->i_width / 2;
	pic_in->img.i_stride[2]	= param->i_width / 2;
 	pic_in->img.plane[0] = indata;
	pic_in->img.plane[1] = indata + param->i_width*param->i_height;
	pic_in->img.plane[2] = indata + param->i_width*param->i_height + (param->i_width*param->i_height >> 2);
	return 0;
}
int com_encoder_encode(int i_frame)
{
	int i_frame_size, i;
	int i_nal;
	pic_in->i_pts = i_frame;
	pic_in->i_type = X264_TYPE_AUTO;
	pic_in->i_qpplus1 = 0;
	pic_in->img.i_plane = 3;
	pic_in->img.plane[0] = indata;
	pic_in->img.plane[1] = indata + param->i_width*param->i_height;
	pic_in->img.plane[2] = indata + param->i_width*param->i_height + (param->i_width*param->i_height >> 2);
	pic_in->img.i_stride[0] = param->i_width;
	pic_in->img.i_stride[1] = param->i_width / 2;
	pic_in->img.i_stride[2] = param->i_width /2;
	
	i_frame_size = x264_encoder_encode( h, &nal, &i_nal, pic_in, pic_out );
	return i_frame_size;
}

void com_encoder_close(void)
{
	x264_encoder_close( h );
	x264_free(pic_in);
	x264_free(pic_out);
}





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
       char      pSeqName[80];           // input yuv seqence file name
       char      pOutputFileName[80];    // output file name pointer
       char      profile[80];            // BP,MP,HP
       int       gop;                    // 
       int       gfGOP;                  // 
       int       spGOP;                  // 
                                         // 
       int       fps;                    // frame per second
       int       totalFrame;             // number of frames to encode
       int       width;                  // width
       int       height;                 // height    
       int       kbps;                   // bankwidth kbps
       
       enc_rc_mode         rc_mode;      // cq or cbr    
       X264ENCPARAM::enumComplexity          cp;           // cp
       int                 rc_max_q;     // max_q
       int                 rc_min_q;     // min_q    
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
	{ "-TOTAL",    &gCmd.totalFrame,	     ap_maybe,   OPT_INT},
	{ "-WIDTH",    &gCmd.width,            ap_yes,     OPT_INT},
	{ "-HEIGHT",   &gCmd.height,           ap_yes,     OPT_INT},
	{ "-KBPS",     &gCmd.kbps,             ap_yes,     OPT_INT},
	{ "-RCMODE",   &gCmd.rc_mode,          ap_maybe,   OPT_INT},
	{ "-CMODE",    &gCmd.cp,               ap_maybe,   OPT_INT},
	{ "-MAXQ",     &gCmd.rc_max_q,         ap_maybe,   OPT_INT},
	{ "-MINQ",     &gCmd.rc_min_q,         ap_maybe,   OPT_INT},
	{  NULL,       NULL,					         ap_no,      OPT_INT}
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


void init_encoder(CX264Encoder* e , int mode, int bitrate, int w, int h)
{
	X264ENCPARAM Info;

	Info.iBitrate = bitrate;
	Info.iFPS = GOP;
	Info.iHeight = h;
	Info.iWidth  = w;
	Info.iGOP = GOP;
	Info.cp =   X264ENCPARAM::cp_fast;	
	
	Info.eProfileLevel = X264ENCPARAM::emProfileLevel_Main;

	if(mode == 0)
		Info.eProfileLevel = X264ENCPARAM::emProfileLevel_Base;
	else if(mode ==1)
		Info.eProfileLevel = X264ENCPARAM::emProfileLevel_Main;
	else if(mode ==2)
		Info.eProfileLevel = X264ENCPARAM::emProfileLevel_High;


   width = w;
   height = h;
	

	e->Init( Info );
}

struct stat fileInfo;


int encoder(CX264Encoder* e, EncCMD_PARAM* e_p1, char *input, char *output)
{
	FILE *fpInput;
	FILE *fpOutput;    
	int ret = 1;
	int frame_count, nbytes, nTotalBytes = 0;
    int use_gf,use_sp,total;
	int inner;

	int frame_size = width * height * 3 / 2;
	unsigned char* inbuf;	
	unsigned char* outbuf_encoder = NULL;
	unsigned int   fileSize,fileFrames;
	EmFrameType frame_type;
	int alltime = 0;


	inbuf = (unsigned char *)malloc(frame_size);
	if(NULL == inbuf)
	{
	   LOGD("error not enough memory!\n");
	   return 0;
	}

	use_gf = 0;
	use_sp = 0;


	

	


	
	fpInput = fopen(input, "rb");
	if(!fpInput)
	{
		LOGD("can't open input file :%s.\n",input);
		return 0;
	}
	fpOutput = fopen(output, "wb");
	if(!fpOutput)
	{
		LOGD("can't open output file.\n");
		return 0;
	}
	fileFrames = fileInfo.st_size/frame_size;


	total = 5000;

	frame_count = 0;
       
	while (frame_count < total)
	{
		if (frame_size !=(fread(inbuf, 1, frame_size, fpInput)))
		{
			break;
		}
		frame_type = getFrameType(frame_count, GOP ,0 , 0);	
		
	//	LOGD("Encode  frame  %d", frame_count);	


    int start_time = VQQ_GetTickCount();
    
		if ( true != e->Encode(inbuf, frame_size, &outbuf_encoder, (long*)&nbytes, frame_type) )
		{
			LOGD("Encode(): error");
			goto exit;
		}

    alltime += (VQQ_GetTickCount() - start_time);


		nTotalBytes += nbytes;

		if ( nbytes != fwrite(outbuf_encoder, 1, nbytes, fpOutput)) 
		{
			ret = 1;
			goto exit;
		}
		frame_count++;
	}


	//测试序列 gop spgop gfgop fps 目标码率 实际码率 帧编码时间 
	
	l_encTime = alltime;
	
	LOGD("fps %.2f fps   total time %d, total frames  %d\n", (double)frame_count * 1000/alltime, alltime, frame_count);

exit:
	if (inbuf)
	{
		free(inbuf);
		inbuf = NULL;
	}
	
	if(fpInput)
	{
		fclose(fpInput);
		fpInput = NULL;
	}
	if(fpOutput)
	{
		fflush(fpOutput);
		fclose(fpOutput);
		fpOutput = NULL;
	}	
	
  return 0;
}







JNIEXPORT jlong JNICALL Java_com_x264_VView_TestEnc(JNIEnv* env, jobject thiz,jstring strYUV,jstring str264, int mode, int bitrate, int w, int h)
{
	  CX264Encoder e;
	
	 char *tmpYUVFilePath = (char*)(env)->GetStringUTFChars(strYUV,NULL);
	 char *tmp264FilePath = (char*)(env)->GetStringUTFChars(str264,NULL);
	
	LOGD("#############test log in JNI,TAG is libnav   %s", tmpYUVFilePath);

    set_default_cmd();    


    init_encoder( &e, mode, bitrate, w, h );

  encoder( &e, &gCmd, tmpYUVFilePath, tmp264FilePath);
  
  e.UnInit();
  
  	(env)->ReleaseStringUTFChars(strYUV,tmpYUVFilePath);
	(env)->ReleaseStringUTFChars(str264,tmp264FilePath);
	LOGD("#############test log in JNI,TAG is libnav2   mode  %d  bitrate  %d", mode, bitrate);
	
	return l_encTime;
	
 // exit(0); //tmp added by sensong 201404
}


void set_default_cmd(void)
{
	memset(&gCmd,0,sizeof(EncCMD_PARAM));
	strcpy(gCmd.profile,"BP");
  gCmd.cp = X264ENCPARAM::cp_fast;	
}



int verfy_cmd(void)
{
	struct ap_Option *pOption;
	int flag =0;
	pOption = g_cmd_enc_opts;
	
	
	if(gCmd.cp<X264ENCPARAM::cp_best || gCmd.cp>X264ENCPARAM::cp_fast)
	{
	  printf("set cmode %d\n",gCmd.cp);
		gCmd.cp=X264ENCPARAM::cp_fast;                  //set fast
	}
	
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
		   "-kbps    kilo-bits per second   \n"    \
			 "-cmode   0(best),1(normal),2(fast) \n" );    
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


JNIEXPORT jlong JNICALL Java_com_x264_VView_TestEnc1(JNIEnv* env, jobject thiz,jstring strYUV,jstring str264)
{	
	FILE *pinFile = NULL,*poutFile=NULL;
	int isize = IN_PIC_WIDTH*IN_PIC_HEIGHT*3/2;
	int readsize = 0;
	int ifile = 0;
	int i_frame_num = 0;
	int     i_frame, i_frame_total, i_frame_output;	
	int i_frame_size = 0;
	int rst;
	struct timeval t_start,t_end;
	long cost_time = 0;
	l_encTime = 0;
	
	//tmpYUVFilePath = (char*)GetStringUTFChars(env,strYUV,NULL);
	//tmp264FilePath = (char*)GetStringUTFChars(env,str264,NULL);
	const char *tmpYUVFilePath = (char*)(env)->GetStringUTFChars(strYUV,NULL);
	const char *tmp264FilePath = (char*)(env)->GetStringUTFChars(str264,NULL);
	
	LOGD("#############test log in JNI,TAG is libnav");
	
	pinFile = fopen(tmpYUVFilePath, "r+b");//fopen("r:\\qvga.yuv", "r+b");
	poutFile = fopen(tmp264FilePath, "w+b");//fopen("r:\\test.264", "w+b");
    //__android_log_print(ANDROID_LOG_INFO, "SanAngeles", "resize w=%d h=%d", w, h);
	LOGD( "[Enc]->yuv=%s,263=%s,file=0x%x,264F=0x%x.",
		tmpYUVFilePath,tmp264FilePath,pinFile,poutFile);
	(env)->ReleaseStringUTFChars(strYUV,tmpYUVFilePath);
	(env)->ReleaseStringUTFChars(str264,tmp264FilePath);
	LOGD("#############test log in JNI,TAG is libnav2");
	if(NULL==pinFile || NULL==poutFile)
	{
		goto END;
	}
	
		LOGD("#############test log in JNI,TAG is libnav2");

	rst = com_encoder_open();
	
	LOGD("#############test log in JNI,TAG is libnav1");
	if(rst < 0)    goto END;
		
		LOGD("#############test log in JNI,TAG is libnav11");

    i_frame_total = 300; //any numbers
	for( i_frame = 0; i_frame < i_frame_total; i_frame++)
	{		
		if(fread(indata, isize, 1, pinFile) <= 0)    break;           
		
		gettimeofday(&t_start, NULL);
		//
		
		LOGD("#############test log in JNI,TAG is libnav112");
		i_frame_size = com_encoder_encode(i_frame);

             LOGD("#############test log in JNI,TAG is libnav113");
		//
		gettimeofday(&t_end, NULL);
		cost_time=(t_end.tv_sec-t_start.tv_sec)*1000000+(t_end.tv_usec-t_start.tv_usec);//微秒		
		l_encTime += cost_time;	
		//
		if( i_frame_size )
		{
			fwrite(nal[0].p_payload, i_frame_size, 1, poutFile);
		}		
	}
	
END:
	com_encoder_close();

	LOGD( "Encode complete.\nAll：%d Frame.\n",i_frame_num);

	if(pinFile != NULL)
	{
		fclose(pinFile);
		pinFile = NULL;
	}
	if(poutFile != NULL)
	{
		fclose(poutFile);
		poutFile = NULL;
	}
	return l_encTime;//cost_time;
}
/*
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void *reserved)
{
	JNIEnv *env = NULL;
	if((*vm)->GetEnv(vm,(void**)&env,JNI_VERSION_1_4)!=JNI_OK)
	{
		return -1;
	}
	return JNI_VERSION_1_4;
}
*/

#ifdef __cplusplus
};
#endif
