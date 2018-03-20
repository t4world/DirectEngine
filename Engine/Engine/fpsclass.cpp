#include "fpsclass.h"


FpsClass::FpsClass()
{
	
}

FpsClass::FpsClass(const FpsClass &other)
{

}


FpsClass::~FpsClass()
{
}

void FpsClass::Initiazlize()
{
	m_count = 0;
	m_mfps = 0;
	m_startTime = timeGetTime();
}

void FpsClass::Frame()
{
	m_count++;
	if (timeGetTime() >= m_startTime + 1000)
	{
		m_mfps = m_count;
		m_count = 0;
		m_startTime = timeGetTime();
	}
}

int FpsClass::GetFPS()
{
	return m_mfps;
}
