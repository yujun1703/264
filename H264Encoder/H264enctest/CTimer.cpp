/*
**文件名称：
          CTimer.h
**摘要：使用windows系统函数来进行计时

**当前版本:
          1.0
**作者:  
       宋森
*/

#include "CTimer.h"
CTimer::CTimer( void )
{
	QueryPerformanceFrequency( &m_Frequency );// 获得处理器频率
	m_Count=0u;                                // cpu周期数
}
void CTimer::Reset( void )
{
	m_Count=0;	// cpu周期数置零
	QueryPerformanceCounter(&m_StartCount);    // 重新开始计时

}
void CTimer::Restart(void)
{
	 QueryPerformanceCounter(&m_StartCount);    // 重新开始计时
}

void CTimer::Start(void)
{
	 QueryPerformanceCounter(&m_StartCount);    // 开始计时
}
 void CTimer::Stop( void)
 {
	 static __int64 nCurCount;
	 QueryPerformanceCounter( (PLARGE_INTEGER)&nCurCount );
	 m_Count+=nCurCount - ( *(__int64*)&m_StartCount );
 }

__int64 CTimer::getClock(void) // 获得经历cpu时钟数
 {
	 return m_Count;
 }
 double CTimer::getSecond(void) // 获得经历的秒数
 {
	 return m_Count/double( *(__int64*)&m_Frequency );
 }

 double CTimer::getMilliSecond(void) // 获得经历的毫秒数
 {
	 return m_Count/double( *(__int64*)&m_Frequency )*1000;
 }