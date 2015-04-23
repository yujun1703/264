/*
**�ļ����ƣ�
          CTimer.h
**ժҪ��ʹ��windowsϵͳ���������м�ʱ

**��ǰ�汾:
          1.0
**����:  
       ��ɭ
*/

#include "CTimer.h"
CTimer::CTimer( void )
{
	QueryPerformanceFrequency( &m_Frequency );// ��ô�����Ƶ��
	m_Count=0u;                                // cpu������
}
void CTimer::Reset( void )
{
	m_Count=0;	// cpu����������
	QueryPerformanceCounter(&m_StartCount);    // ���¿�ʼ��ʱ

}
void CTimer::Restart(void)
{
	 QueryPerformanceCounter(&m_StartCount);    // ���¿�ʼ��ʱ
}

void CTimer::Start(void)
{
	 QueryPerformanceCounter(&m_StartCount);    // ��ʼ��ʱ
}
 void CTimer::Stop( void)
 {
	 static __int64 nCurCount;
	 QueryPerformanceCounter( (PLARGE_INTEGER)&nCurCount );
	 m_Count+=nCurCount - ( *(__int64*)&m_StartCount );
 }

__int64 CTimer::getClock(void) // ��þ���cpuʱ����
 {
	 return m_Count;
 }
 double CTimer::getSecond(void) // ��þ���������
 {
	 return m_Count/double( *(__int64*)&m_Frequency );
 }

 double CTimer::getMilliSecond(void) // ��þ����ĺ�����
 {
	 return m_Count/double( *(__int64*)&m_Frequency )*1000;
 }