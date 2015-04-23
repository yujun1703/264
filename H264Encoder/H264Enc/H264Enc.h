#ifndef __H264ENC_H__
#define __H264ENC_H__

#include "../../include/VCodec.h"
#include "x264Encoder.h"

#ifdef WIN32
#include <windows.h>
#ifndef ENC_API
#define ENC_API __declspec( dllimport )
#endif
#endif

class  H264Enc : public VCodec
{
public:
    H264Enc();
    virtual ~H264Enc();

public:
    virtual int Init(VIDEOENCLEVEL stCodecInfo);
    virtual int UnInit();
    virtual int GetVersion(int *m_nversion);
    virtual int SetCodecCallBack(void * pObj,  ICodecCallback pICodecCallback);
    virtual int GetAbility(VIDEOABILITYINFO **stAbilityInfo);
    virtual int DoCodec(unsigned char *pcInBuf, int nInLen, int nFrameIndex, int flag=0);
    virtual int CallMethod(int nMethodType, unsigned char * pParam, int *pnParamLen);
  
protected:
    X264ENCPARAM     m_stEncParam;
    //H264ENCPARAM    m_stEncParam;
    int                            m_bIsInit;
    int                       m_nFrameType;
    ICodecCallback         m_ICodecCallback;
    void                          *m_pObj;
    int                           m_nFrameIndex;
    int                           m_nFrameSkiped;
#ifndef _SIMULATOR_ 
    CX264Encoder         m_x264Enc;
#endif
};


class CX264Enc : public XVCodec
{
public:
    CX264Enc();
    virtual ~CX264Enc();

public:
    virtual int Init(VIDEOCODECINFO stCodecInfo);
    virtual int UnInit();
    virtual int DoCodec(unsigned char *pcInBuf, int nInLen, unsigned char **ppcOutBuf, int *pnOutLen);
    virtual int CallMethod(int nMethodType, unsigned char *pParam, int *pnParamLen);

protected:
#ifndef _SIMULATOR_ 
    CX264Encoder         m_x264Enc;
#endif
    X264ENCPARAM     m_stEncParam;
    int            m_nFrameType;
    bool            m_bIsInit;
    int            m_nActiveFPS;    //µ±Ç°Ö¡ÂÊ
};


#endif//#define __VP8ENC_H__
