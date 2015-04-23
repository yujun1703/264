#include "H264Enc.h"
#include "x264Encoder.h"
#include <memory.h>
#include <stdlib.h>
#if defined (TARGET_OS_IPHONE)
//#include "LogWriter.h"
#endif
#ifndef WIN32
#include <dirent.h>
#include <stdio.h>
#include <dlfcn.h>
#include <string>
#define LOG_TAG "H264Enc"
#ifdef ANDROID
#include <android/log.h>
#define LOGD(fmt, args...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG,  fmt,##args)
#endif
#define DLLEX __attribute__ ((visibility ("default")))
#define NULL 0

#else
#define DLLEX __declspec(dllexport)
#endif


#if defined (TARGET_OS_IPHONE)
#include "iOSDevInfo.h"
#endif

#if !(TARGET_OS_IPHONE)
extern "C"
{
    void DLLEX create(VCodec **pVEA)
    {
        H264Enc* pVE = new H264Enc;
        *pVEA = reinterpret_cast<VCodec*>(pVE);
    }
  
    void DLLEX release(VCodec *pVEA)
    {
        delete pVEA;
    }
}
#endif

//#define OUTBUF_SIZE   (512 * 1024)  // 512KB
#ifndef ANDROID
#define LOG       //printf
#endif //

#if (!defined WIN32) && (!defined TARGET_OS_IPHONE)
//swp half thumb fastmult vfp edsp neon vfpv3 tls
//example:
// bool fhasneon = hasFeature("neon");
static int cpu_sort (const struct dirent ** d1, const struct dirent ** d2) {
	return alphasort(d1,d2);
}
static int  cpu_filter(const  struct  dirent *dir)
{
	if (strncmp(dir->d_name, "cpu", 3) != 0)
		return 0;
       const char *p;
	char c;
	p = dir->d_name+3;
	while( ( c=*p++ )!='\0' ){
		printf(" c:%c - %c",c,*p);
		if( !(c>='0'&&c<='9') )
			return 0;
	}
	return 1;
}
int GetCpuCount()
{
    struct dirent **namelist;
	int cpu_count;
    int n;
	n = scandir("/sys/devices/system/cpu", &namelist, cpu_filter,cpu_sort);
    if (n < 0){
		return 0;
	}
    else {
		cpu_count = n;
        while (n--) {
            printf("%s\n", namelist[n]->d_name);
            free(namelist[n]);
        }
        free(namelist);
    }
    return cpu_count;
}

bool hasFeature(const char* pstrfeature){
   if(pstrfeature == NULL){
       return false;
   }

     FILE* fd = fopen("/proc/cpuinfo","r");
     bool fret = false;
     char buff[256];
     memset(buff,0,sizeof(buff));
     if(fd){
    	 while(!feof(fd)){
    		 memset(buff,0,sizeof(buff));
    		 if(fgets(buff,250,fd)){
   			 if(strstr(buff,pstrfeature)){
                            fret = true;
    			    break;
    			 }				 
    		 }//end of if(fgets(buff,250,fd))
    	 }
    	 fclose(fd);
     }
     return fret;
}

int  GetCpuFreq(){
    int m_nFreq;
    FILE* fd = fopen("/sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_max_freq","r");
    char buff[256];
    std::string  mCpuFreq;
     if(fd){
    	 while(!feof(fd)){
    		 memset(buff,0,sizeof(buff));
    		 if(fgets(buff,250,fd)){    
			 if(mCpuFreq.size() ==0 ){
				 //set mips
				 char* pstart = buff;
				 if(pstart){
					 mCpuFreq.append((const char*)pstart);
				 }
			 }
    		 }
    	 }
    	 fclose(fd);
     }
     sscanf((const char*)mCpuFreq.c_str(), "%llu", &m_nFreq);
     return m_nFreq/1000;
}
#endif //


H264Enc::H264Enc()
: m_bIsInit(false)
, m_nFrameType(def_FrameType_I)
, m_pObj(NULL)
, m_nFrameSkiped(0)
,m_nFrameIndex(0)
{ 
#ifndef _SIMULATOR_  
#ifndef WIN32
static bool gH264Enc = false;
if(gH264Enc == false)
{
   m_x264Enc.init_enc_com_data();
   gH264Enc = true;
}
#endif
#endif    

    m_ICodecCallback.pCodecDoneCB = NULL;
    m_ICodecCallback.pGetOutputBufCB = NULL;   
}

H264Enc::~H264Enc()
{
    UnInit();
    m_bIsInit = false;
}

#if defined(ANDROID)
static void GetEncCfgFromTxt(int* Cmplx)
{	   

	char line_name[40];
	char *config_sign = "=";
	char *leave_line;
	FILE *pfile = fopen("/system/aEncCfg.txt","r");
	if(pfile != NULL)
	{
		fseek(pfile,0,SEEK_SET);
		char config_linebuf[256];
		while(fgets(config_linebuf, 256, pfile) != NULL)
		{
			if(strlen(config_linebuf) < 3)  //is it NULL line
			{
				continue;
			}
			char exchange_buf[256];
			char config_buff[256];
			if (config_linebuf[strlen(config_linebuf)-1] == 10) //the last bit is \n 
			{
				memset(exchange_buf,0,sizeof(exchange_buf));
				strncpy(exchange_buf,config_linebuf,strlen(config_linebuf)-1);
				memset(config_linebuf,0,sizeof(config_linebuf));
				strcpy(config_linebuf,exchange_buf);
			}
			memset(line_name,0,sizeof(line_name));
			memset(config_buff,0,sizeof(config_buff));
			leave_line = strstr(config_linebuf,config_sign);
			if(leave_line == NULL) 
			{
				continue;
			}
			int leave_num = leave_line - config_linebuf;
			strncpy(line_name,config_linebuf,leave_num);

			if(strcmp(line_name,"Cmplx") ==0)
			{
				strncpy(config_buff,config_linebuf+(leave_num+1),strlen(config_linebuf)-leave_num-1);
				*Cmplx = atoi(config_buff);
			}

			if(fgetc(pfile)==EOF)
			{
				break;
			}
			fseek(pfile,-1,SEEK_CUR);
			memset(config_linebuf,0,sizeof(config_linebuf));
		}
		fclose(pfile); 
	}
}
#endif


int H264Enc::Init(VIDEOENCLEVEL stCodecInfo)
{
    if(m_bIsInit)
        return true;
    
#ifndef _SIMULATOR_
    m_stEncParam.iWidth = stCodecInfo.nWidth;
    m_stEncParam.iHeight = stCodecInfo.nHeight;
    m_stEncParam.iFPS    = stCodecInfo.nFPS;
    m_stEncParam.iBitrate= stCodecInfo.nBitrate;  //kbps
    m_stEncParam.iMaxQP = stCodecInfo.nMaxQp;
    m_stEncParam.iMinQP = stCodecInfo.nMinQp;
    m_stEncParam.iGOP = stCodecInfo.nIGop;
    m_stEncParam.igfGOP = stCodecInfo.nGfGop;
    m_stEncParam.ispGOP = stCodecInfo.nSpGop;

#ifdef WIN32
	switch (stCodecInfo.nEncMode)
	{
	case def_EncMode_Dsk:
		m_stEncParam.mode = X264ENCPARAM::emMode_Dsktop;
		break;

	case def_EncMode_Normal_abr:
		m_stEncParam.mode = X264ENCPARAM::emMode_Normal_abr;
		break;

	case def_EncMode_Normal:
	default:
		m_stEncParam.mode = X264ENCPARAM::emMode_Normal;
		break;
	}

	switch (stCodecInfo.nComplexity)
	{
	case def_Complexity_Best:
		m_stEncParam.cp = X264ENCPARAM::cp_best;
		break;

	case def_Complexity_Fast:
		m_stEncParam.cp = X264ENCPARAM::cp_fast;
		break;

	case def_Complexity_Normal:
	default:
		m_stEncParam.cp = X264ENCPARAM::cp_normal;
		break;
	}
#else	
    m_stEncParam.mode = X264ENCPARAM::emMode_Normal;
    m_stEncParam.cp = X264ENCPARAM::cp_normal;
#endif

    switch (stCodecInfo.nCodecType)
    {
    case def_CodecType_H264HighProfile:
        m_stEncParam.eProfileLevel = X264ENCPARAM::emProfileLevel_High;
        break;

    case def_CodecType_H264MainProfile:
        m_stEncParam.eProfileLevel = X264ENCPARAM::emProfileLevel_Main;
        break;

    case def_CodecType_H264Baseline:
    default:
        m_stEncParam.eProfileLevel = X264ENCPARAM::emProfileLevel_Base;
        break;
    }

    //turn off this mode for new ratecontrol
    //use complexmode and size is less than 320x240, change ana_cap_inter

#if defined(ANDROID)
    int nCpuCount = GetCpuCount();
	int nCpuFreq = GetCpuFreq();
    if ( nCpuCount == 1 )
    {
		if ( m_stEncParam.iWidth >= 320 )
		{
			m_stEncParam.cp = X264ENCPARAM::cp_fast;
		}
    }
    else if ( nCpuCount == 2 && nCpuFreq <= 1500000)
    {
		if ( m_stEncParam.iWidth >= 320 ) 
		{
			m_stEncParam.cp = X264ENCPARAM::cp_fast;
		}
    }	
	else if ( nCpuCount >= 4 && nCpuFreq >= 1700000 && m_stEncParam.iWidth == 320 
		|| m_stEncParam.iWidth < 320 )
	{
		m_stEncParam.cp = X264ENCPARAM::cp_best;
	}
	int cmplx = 0;
	GetEncCfgFromTxt(&cmplx);
	switch (cmplx)
	{
	case 0:
		m_stEncParam.cp = X264ENCPARAM::cp_fast;
		break;
	case 2:
		m_stEncParam.cp = X264ENCPARAM::cp_best;
		break;
	case 1:
	default:
		m_stEncParam.cp = X264ENCPARAM::cp_normal;
		break;
	}

#endif

#if defined(TARGET_OS_IPHONE)
    CiOSDevInfo appleDev;
    IOSDEV_DEVICE devCapa;
    if (appleDev.getCurrentAbility(devCapa))
    {
        if ( devCapa.type == iOSDev_iPhone4 )
        {
			if ( m_stEncParam.iWidth >= 320 )
			{
				m_stEncParam.cp = X264ENCPARAM::cp_fast;
			}
        }
		else if ( devCapa.type == iOSDev_iPhone5S && m_stEncParam.iWidth == 320 
			|| m_stEncParam.iWidth < 320 )
		{
			m_stEncParam.cp = X264ENCPARAM::cp_best;
		}
    }
#endif

	m_x264Enc.Init(m_stEncParam);

#endif

    m_bIsInit = true;
    return true;
}


int H264Enc::UnInit()
{ 
#ifndef _SIMULATOR_  
    if ( m_bIsInit ){
        m_x264Enc.UnInit();
        m_bIsInit = false;
    }
#endif
    return true;
}


int H264Enc::GetVersion(int *m_nversion)
{
    *m_nversion = 11;
    return true;
}

int H264Enc::GetAbility(VIDEOABILITYINFO** stAbilityInfo)
{ 
#if (!defined WIN32) && (!defined TARGET_OS_IPHONE)
    bool hasNeon = hasFeature("neon");
    int m_nCpuFreq = GetCpuFreq();
#endif

#if (defined WIN32)	
    (*stAbilityInfo)->nMaxWidth = 1920;
    (*stAbilityInfo)->nMaxHeight = 1200;
#else
      (*stAbilityInfo)->nMaxWidth = 320;
      (*stAbilityInfo)->nMaxHeight = 240;	
#endif //


#if defined(TARGET_OS_IPHONE)
    CiOSDevInfo appleDev;
    IOSDEV_DEVICE devCapa;
    if (appleDev.getCurrentAbility(devCapa))
    {

        if(devCapa.type  == iOSDev_iPhone4 )
        {
            (*stAbilityInfo)->nMaxFps = 10;
        }
        else if(devCapa.type  == iOSDev_iPhone4S )
        {
            (*stAbilityInfo)->nMaxFps = 15;
        }
        else
        {
            (*stAbilityInfo)->nMaxFps = 15;
        }
    }
    else
        (*stAbilityInfo)->nMaxFps = 10;
#else
    (*stAbilityInfo)->nMaxFps = 15;
#endif    
    (*stAbilityInfo)->nMaxMBPS = (*stAbilityInfo)->nMaxWidth * (*stAbilityInfo)->nMaxHeight * (*stAbilityInfo)->nMaxFps /256;
    (*stAbilityInfo)->nIsEncode = 1;
    (*stAbilityInfo)->nCodecType = def_CodecType_H264HighProfile;
    (*stAbilityInfo)->nSupportedInputType = 1;
    (*stAbilityInfo)->nInputType[0] = def_InputType_I420;   
    return true;
}

int H264Enc::SetCodecCallBack(void * pObjCall,  ICodecCallback pICodecCallback)
{
    m_pObj = pObjCall;
    m_ICodecCallback.pCodecDoneCB = pICodecCallback.pCodecDoneCB;
    //m_ICodecCallback.pGetOutputBufCB = pICodecCallback.pGetOutputBufCB;
    return true;
}

int H264Enc::DoCodec(unsigned char  *pIn, int nInLen,  int nFrameIndex, int flag)
{
#ifndef _SIMULATOR_  
    if ( !m_bIsInit ){
        //LOGE("H264Enc::DoCodec not init!");
        return false;
    }
    m_nFrameSkiped = 0;
    m_nFrameIndex = nFrameIndex;

    if ( !pIn || nInLen == 0)
    {
        return false;
    }

    int nPixelSize = m_stEncParam.iWidth * m_stEncParam.iHeight;
    int nFrameSize = nPixelSize * 3 / 2;
    if ( nInLen < nFrameSize )
    {
        return false;
    }    

    EmFrameType eFrameType; 
    if ( m_nFrameType == def_FrameType_I )
        eFrameType = emType_IDR;
    else if ( m_nFrameType == def_FrameType_P )
        eFrameType = emType_PnoSP;    
    else if ( m_nFrameType == def_FrameType_SP )
        eFrameType = emType_SP;
    else if ( m_nFrameType == def_FrameType_P_WITHSP )
        eFrameType = emType_PwithSP;
    else if ( m_nFrameType == def_FrameType_GF)
        eFrameType = emType_GF;
    else
        return false;

    int out_buf_size = nPixelSize;
    unsigned char* m_pcOut = NULL;


    m_x264Enc.Encode(pIn, nInLen, &m_pcOut, (long*)&out_buf_size, eFrameType);

    //encoder drop this frame for bitrate control
    if(out_buf_size == 0)
    {   
        m_nFrameSkiped = 1;
    }
    else
    {    
          float avgqp =  0;
          m_x264Enc.GetFrameAvgQP( &avgqp);
    m_ICodecCallback.pCodecDoneCB(m_pObj, m_pcOut, out_buf_size, m_nFrameIndex, avgqp);
    }
#endif
    return true;
}


int H264Enc::CallMethod(int nMethodType, unsigned char  *pParam, int *pnParamLen)
{
 #ifndef _SIMULATOR_    
    switch ( nMethodType )
    {
        case def_Method_SetBitrate:
        { 
            int m_bitrate = *(int*)pParam;
            if ( m_stEncParam.iBitrate != m_bitrate)
           {
              m_stEncParam.iBitrate = m_bitrate;
              m_x264Enc.SetParam(m_stEncParam.iBitrate, m_stEncParam.iFPS);
        }
        }
        break;
        case def_Method_SetFrameType:
        { 
          m_nFrameType = *(int*)pParam;
        }
        break;
          
        case def_Method_SetFps:
        { 
             int m_fps = *(int*)pParam;
            if(m_stEncParam.iFPS != m_fps)
            {
                m_stEncParam.iFPS = m_fps;
                m_x264Enc.SetParam(m_stEncParam.iBitrate, m_stEncParam.iFPS);
        }
        }
        break;
          
        case def_Method_SetIGop:
        {
             int m_iGop = *(int*)pParam;
            if(m_stEncParam.iGOP != m_iGop)
        {
                m_stEncParam.iGOP = m_iGop;
                m_x264Enc.SetPeriod(m_stEncParam.iGOP, m_stEncParam.igfGOP , m_stEncParam.ispGOP );
            }
        }
        break;
      
         case def_Method_SetGfGop:
        {
             int m_gfGop = *(int*)pParam;
            if(m_stEncParam.igfGOP != m_gfGop)
        {
                m_stEncParam.igfGOP = m_gfGop;
                m_x264Enc.SetPeriod(m_stEncParam.iGOP, m_stEncParam.igfGOP , m_stEncParam.ispGOP );
            }
        }
        break;
      
         case def_Method_SetSpGop:
        {
             int m_spGop = *(int*)pParam;
            if(m_stEncParam.ispGOP != m_spGop)
        {
                m_stEncParam.ispGOP = m_spGop;
                m_x264Enc.SetPeriod(m_stEncParam.iGOP, m_stEncParam.igfGOP , m_stEncParam.ispGOP );
            }
        }
        break;
      
        case def_Method_GetEncFps:
        {
          *pParam = m_stEncParam.iFPS;
        }
        break;
      
        case def_Method_GetEncBitrate:
        {
          *(int*)pParam = m_stEncParam.iBitrate;
        }
        break;

        case def_Method_GetEncWidth:
        {
          *(int*)pParam = m_stEncParam.iWidth;
        }
        break;

        case def_Method_GetEncHeight:
        {
          *(int*)pParam = m_stEncParam.iHeight;
        }
        break;
    
        case def_Method_GetSkipFrame:
        {
          *(int*)pParam = m_nFrameSkiped;
        }
        break;

		case def_Method_ResetBuffer:
			{
				m_x264Enc.ResetRCBuffer();
			}
		break;

        default:
          return false;
    }
#endif
    return true;
}

#if !(TARGET_OS_IPHONE)
extern "C"
{
    void DLLEX createX(XVCodec **pVEA)
    {
        CX264Enc* pVE = new CX264Enc;
        *pVEA = reinterpret_cast<XVCodec*>(pVE);
    }
  
    void DLLEX releaseX(XVCodec *pVEA)
    {
        delete pVEA;
    }
}
#endif

CX264Enc::CX264Enc()
{
    //memset(&m_stEncParam, 0, sizeof(m_stEncParam));///fredzhao : zero is not acceptable
    m_nFrameType        = def_FrameType_I;
    m_bIsInit            = false;
    m_nActiveFPS         = 0;
}

CX264Enc::~CX264Enc()
{
    if ( m_bIsInit )
    {
        UnInit();
    }
    m_bIsInit = false;
}

int CX264Enc::Init(VIDEOCODECINFO stCodecInfo)
{
#ifndef _SIMULATOR_    
    m_stEncParam.iWidth = stCodecInfo.nMaxWidth;
    m_stEncParam.iHeight = stCodecInfo.nMaxHeight;
    m_stEncParam.iFPS= 15;
    m_stEncParam.iBitrate= 200;  //kbps	
	m_stEncParam.iMaxQP = stCodecInfo.nMaxQp;
	m_stEncParam.iMinQP = stCodecInfo.nMinQp;

    m_stEncParam.iGOP = m_stEncParam.iFPS;
    m_stEncParam.igfGOP = 0;
    m_stEncParam.ispGOP = 0;
	
	switch (stCodecInfo.nEncMode)
    {
	case def_EncMode_Dsk:
		m_stEncParam.mode = X264ENCPARAM::emMode_Dsktop;
        break;

	case def_EncMode_Normal_abr:
		m_stEncParam.mode = X264ENCPARAM::emMode_Normal_abr;
        break;

	case def_EncMode_Normal:
    default:
		m_stEncParam.mode = X264ENCPARAM::emMode_Normal;
        break;
    }

#ifdef WIN32
	switch (stCodecInfo.nComplexity)
	{
	case def_Complexity_Best:
		m_stEncParam.cp = X264ENCPARAM::cp_best;
		break;

	case def_Complexity_Fast:
		m_stEncParam.cp = X264ENCPARAM::cp_fast;
		break;

	case def_Complexity_Normal:
	default:
		m_stEncParam.cp = X264ENCPARAM::cp_normal;
		break;
	}
#else   
    m_stEncParam.cp = X264ENCPARAM::cp_normal;
#endif

#if defined(ANDROID)
    int nCpuCount = GetCpuCount();
	int nCpuFreq = GetCpuFreq();
    if ( nCpuCount == 1 )
    {
		if ( m_stEncParam.iWidth >= 320 )
		{
			m_stEncParam.cp = X264ENCPARAM::cp_fast;
		}
    }
    else if ( nCpuCount == 2 && nCpuFreq <= 1500000)
    {
		if ( m_stEncParam.iWidth >= 320 )
		{
			m_stEncParam.cp = X264ENCPARAM::cp_fast;
		}
    }
	else if ( nCpuCount >= 4 && nCpuFreq >= 1700000 && m_stEncParam.iWidth == 320
             || m_stEncParam.iWidth < 320 )
	{
		m_stEncParam.cp = X264ENCPARAM::cp_best;
	}
	int cmplx = 0;
	GetEncCfgFromTxt(&cmplx);
	switch (cmplx)
	{
        case 0:
            m_stEncParam.cp = X264ENCPARAM::cp_fast;
            break;
        case 2:
            m_stEncParam.cp = X264ENCPARAM::cp_best;
            break;
        case 1:
        default:
            m_stEncParam.cp = X264ENCPARAM::cp_normal;
            break;
	}
    
#endif
    
#if defined(TARGET_OS_IPHONE)
    CiOSDevInfo appleDev;
    IOSDEV_DEVICE devCapa;
    if (appleDev.getCurrentAbility(devCapa))
    {
        if ( devCapa.type == iOSDev_iPhone4 )
        {
			if ( m_stEncParam.iWidth >= 320 )
			{
				m_stEncParam.cp = X264ENCPARAM::cp_fast;
			}
        }
		else if ( devCapa.type == iOSDev_iPhone5S && m_stEncParam.iWidth == 320
                 || m_stEncParam.iWidth < 320 )
		{
			m_stEncParam.cp = X264ENCPARAM::cp_best;
		}
    }
#endif
    
    switch (stCodecInfo.nCodecType)
    {
    case def_CodecType_H264HighProfile:
        m_stEncParam.eProfileLevel = X264ENCPARAM::emProfileLevel_High;
        break;

    case def_CodecType_H264MainProfile:
        m_stEncParam.eProfileLevel = X264ENCPARAM::emProfileLevel_Main;
        break;

    case def_CodecType_H264Baseline:
    default:
        m_stEncParam.eProfileLevel = X264ENCPARAM::emProfileLevel_Base;
        break;
    }
   
    m_x264Enc.Init(m_stEncParam);
    m_bIsInit = true;

#endif
    return m_bIsInit;
}

int CX264Enc::UnInit()
{
#ifndef _SIMULATOR_    
    if ( m_bIsInit ){
        m_bIsInit = false;
    }
    
    m_x264Enc.UnInit();

#endif
    return true;
}

int CX264Enc::DoCodec(unsigned char *pcInBuf, int nInLen, unsigned char **ppcOutBuf, int *pnOutLen)
{
#ifndef _SIMULATOR_ 
    if ( !m_bIsInit )
    {
        return false;
    }

    int nPixelSize = m_stEncParam.iWidth * m_stEncParam.iHeight;
    int nFrameSize = nPixelSize * 3 / 2;
    if ( nInLen < nFrameSize )
    {
        return false;
    }    

    EmFrameType eFrameType; 
    if ( m_nFrameType == def_FrameType_I )
        eFrameType = emType_IDR;
    else if ( m_nFrameType == def_FrameType_P )
        eFrameType = emType_PnoSP;    
    else if ( m_nFrameType == def_FrameType_SP )
        eFrameType = emType_SP;
    else if ( m_nFrameType == def_FrameType_P_WITHSP )
        eFrameType = emType_PwithSP;
    else if ( m_nFrameType == def_FrameType_GF)
        eFrameType = emType_GF;
    else
        return false;

    int out_buf_size = nPixelSize;
    unsigned char* m_pcOut = NULL;

    m_x264Enc.Encode(pcInBuf, nInLen, &m_pcOut, (long*)&out_buf_size, eFrameType);

    *ppcOutBuf = m_pcOut;
    *pnOutLen = out_buf_size;
#endif
    return true;
}

int CX264Enc::CallMethod(int nMethodType, unsigned char *pParam, int *pnParamLen)
{
#ifndef _SIMULATOR_     
    switch ( nMethodType )
    {
    case def_Method_SetBitrate:
        { 
            m_stEncParam.iBitrate = *(int*)pParam;
            m_x264Enc.SetParam(m_stEncParam.iBitrate, m_stEncParam.iFPS);
        }
        break;
    case def_Method_SetFrameType:
        { 
            m_nFrameType = *(int*)pParam;
        }
        break;
          
    case def_Method_SetFps:
        { 
            m_stEncParam.iFPS = *(int*)pParam;
            m_x264Enc.SetParam(m_stEncParam.iBitrate, m_stEncParam.iFPS);
        }
        break;

    case def_Method_SetIGop:
        {
            m_stEncParam.iGOP = *(int*)pParam;
            m_x264Enc.SetPeriod(m_stEncParam.iGOP, m_stEncParam.igfGOP , m_stEncParam.ispGOP );
        }
        break;

     case def_Method_SetGfGop:
        {
            m_stEncParam.igfGOP = *(int*)pParam;
            m_x264Enc.SetPeriod(m_stEncParam.iGOP, m_stEncParam.igfGOP , m_stEncParam.ispGOP );
        }
        break;    

     case def_Method_SetSpGop:
        {
            m_stEncParam.ispGOP = *(int*)pParam;
            m_x264Enc.SetPeriod(m_stEncParam.iGOP, m_stEncParam.igfGOP , m_stEncParam.ispGOP );
        }
        break;

    case def_Method_GetEncFps:
        {
            *pParam = m_stEncParam.iFPS;
        }
        break;

    case def_Method_GetEncBitrate:
    {
            *(int*)pParam = m_stEncParam.iBitrate;
    }
			break;

    case def_Method_GetEncWidth:
    {
            *(int*)pParam = m_stEncParam.iWidth;
    }
			break;

    case def_Method_GetEncHeight:
    {
            *(int*)pParam = m_stEncParam.iHeight;
    }
			break;

    case def_Method_ResetBuffer:
        {
            m_x264Enc.ResetRCBuffer();
        }
        break;

    case def_Method_SetSize:
        {
            int size = *(int*)pParam;
            int width = size&0xff;
            int height = size >> 16;
            m_x264Enc.ResetEncoder(width, height);
        }
        break;
    default:
        return false;
    }
#endif
    return true;
}


