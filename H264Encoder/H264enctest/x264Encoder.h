#ifndef _X264ENCODER_H
#define _X264ENCODER_H

#ifdef WIN32
#ifndef ENC_API
#define ENC_API __declspec( dllimport )
#endif
#include <windows.h>
#else
#define ENC_API
#define HRESULT int
#define S_OK true
#define E_FAIL false
#define E_INVALIDARG false
#define S_FALSE false
#endif
#define NULL 0

#define VQQLONG     long
#define VQQUCHAR    unsigned char
#define VQQINT      int



typedef struct tagx264EncParam
{
    int iWidth;
    int iHeight;
    int iGOP;
    int iBitrate;
    int iFPS;
    int igfGOP;
    int ispGOP;

    // added by timlong
    int iThreads;
    int iMinQP;
    int iMaxQP;
    // end

    enum enumProfileLevel
    {
        emProfileLevel_Base,
        emProfileLevel_Main,
        emProfileLevel_High,
    };
    enum enumProfileLevel eProfileLevel;
    
    enum enumComplexity
    {
        cp_best = 0,
        cp_normal,
        cp_fast
    };
    enum enumComplexity cp;
    
    enum enumEncMode
    {
        emMode_Normal = 0,
        emMode_Dsktop = 1,
        emMode_Normal_abr = 2,
    };
    enum enumEncMode mode;
    //fred temp for cmd param
    void* usr_ptr;
    //int max_drop_num;

    tagx264EncParam()
    {
        iWidth = 0;
        iHeight = 0;
        iBitrate = 0;
        iFPS = 0;
        iGOP = 0;
        igfGOP = 0;
        ispGOP = 0;

        iMinQP = 0;
        iMaxQP = 51;
        iThreads = 1;

        cp = cp_best;
        eProfileLevel = emProfileLevel_High;
        mode = emMode_Normal;
        usr_ptr = NULL;
    }
} X264ENCPARAM;

typedef enum
{
	emType_IDR = 0,
	emType_GF 			= 1,
	emType_SP				= 2,
	emType_PwithSP	= 3,
	emType_PnoSP		= 4
} EmFrameType;

class ENC_API CX264Encoder
{
public:
    CX264Encoder();
    virtual ~CX264Encoder();
    HRESULT Init(X264ENCPARAM);
    HRESULT UnInit();
    HRESULT Encode(VQQUCHAR*, VQQLONG, VQQUCHAR**, VQQLONG*, EmFrameType);
    HRESULT SetParam(int, int);
    HRESULT GetFrameAvgQP( float* );//added by fred
    void SetPeriod(int, int, int);
    int release_enc_com_data();
    int init_enc_com_data();
	  void ResetRCBuffer();
    void SetDelayTime(int sec);
    void ResetEncoder(int, int);

private:
    X264ENCPARAM m_stEncParam;
    void* m_px264Handle;
    void* m_pPic;
   // VQQUCHAR* m_pcOut;
    unsigned char m_level[5];//[ level_0 ][ level_1 ][ level_2 ]

    void ConfigParam(void*);
    int SetFrameRefInfo( void *pic, EmFrameType FrameType );
    void UpdateRefStatus( EmFrameType FrameType );
};

#endif /* _X264ENCODER_H */
