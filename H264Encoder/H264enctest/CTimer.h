/*
**文件名称：
          CTimer.cpp
**摘要：使用windows系统函数来进行计时

**当前版本:
          1.0
**作者:  
       宋森
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
	   void Start(void);			// 开始计时
       void Reset(void);			// 时钟归零
	   void Restart(void);			// 重新计时
	   void Stop(void);				// 停止计时器
	   
	   __int64 getClock(void);		// 获得经历cpu时钟数
	   double getSecond(void);		// 获得经历的秒数
	   double getMilliSecond(void); // 获得经历的毫秒数

private:
       LARGE_INTEGER m_Frequency;
       LARGE_INTEGER m_StartCount;
       __int64 m_Count;
};
#endif