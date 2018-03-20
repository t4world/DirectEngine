#ifndef _TIMECLASS_H_
#define _TIMECLASS_H_

#include <windows.h>
class TimerClass
{
private: 
	INT64 m_frequency;
	float m_ticksPerMs;
	INT64 m_startTime;
	float m_frameTime;
public:
	TimerClass();
	TimerClass(const TimerClass &other);
	~TimerClass();

	bool Initialize();
	void Frame();
	float GetTime();
};
#endif

