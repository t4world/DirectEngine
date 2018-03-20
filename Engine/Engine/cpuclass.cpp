#include "cpuclass.h"


Cpuclass::Cpuclass()
{
}

Cpuclass::Cpuclass(const Cpuclass &other)
{

}


Cpuclass::~Cpuclass()
{
}

void Cpuclass::Intialize()
{
	PDH_STATUS state;
	m_canReadCpu = true;
	state = PdhOpenQuery(NULL, 0, &m_queryHandle);
	if (state != ERROR_SUCCESS)
	{
		m_canReadCpu = false;
	}
	state = PdhAddCounter(m_queryHandle, TEXT("\\Processor(_Total)\\% processor time"), 0, &m_counterHandle);
	if (state != ERROR_SUCCESS)
	{
		m_canReadCpu = false;
	}
	m_lastSampleTime = GetTickCount();
	m_cpuUsage = 0;
}

void Cpuclass::Shutdown()
{
	if (m_canReadCpu)
	{
		PdhCloseQuery(m_queryHandle);
	}
}

void Cpuclass::Frame()
{
	PDH_FMT_COUNTERVALUE value;
	if (m_canReadCpu)
	{
		if (GetTickCount() >= m_lastSampleTime + 1000)
		{
			m_lastSampleTime = GetTickCount();
			PdhCollectQueryData(m_queryHandle);
			PdhGetFormattedCounterValue(m_counterHandle, PDH_FMT_LONG, NULL, &value);
			m_cpuUsage = value.longValue;
		}
	}
}

int Cpuclass::GetCpuPercentage()
{
	int usege;
	if (m_canReadCpu)
	{
		usege = (int)m_cpuUsage;
	}
	else
	{
		usege = 0;
	}
	return usege;
}
