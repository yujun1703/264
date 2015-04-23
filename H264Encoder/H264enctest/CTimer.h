/*
**�ļ����ƣ�
          CTimer.cpp
**ժҪ��ʹ��windowsϵͳ���������м�ʱ

**��ǰ�汾:
          1.0
**����:  
       ��ɭ
*/
#ifndef __CTimer_H_
#define __CTimer_H_
#include <windows.h>
#include <stdio.h>


class CTimer
{
public:
       CTimer(void);
	   ~CTimer(){}
	   void Start(void);			// ��ʼ��ʱ
       void Reset(void);			// ʱ�ӹ���
	   void Restart(void);			// ���¼�ʱ
	   void Stop(void);				// ֹͣ��ʱ��
	   
	   __int64 getClock(void);		// ��þ���cpuʱ����
	   double getSecond(void);		// ��þ���������
	   double getMilliSecond(void); // ��þ����ĺ�����

private:
       LARGE_INTEGER m_Frequency;
       LARGE_INTEGER m_StartCount;
       __int64 m_Count;
};
#endif