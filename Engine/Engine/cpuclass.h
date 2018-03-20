#ifndef _CPUCLASS_H_
#define _CPUCLASS_H_
#pragma comment(lib,"pdh.lib")

#include <pdh.h>
class Cpuclass
{
private:
	bool m_canReadCpu;
	HQUERY m_queryHandle;
	HCOUNTER m_counterHandle;
	unsigned long m_lastSampleTime;
	long m_cpuUsage;
public:
	Cpuclass();
	Cpuclass(const Cpuclass &other);
	~Cpuclass();

	void Intialize();
	void Shutdown();
	void Frame();
	int GetCpuPercentage();
};
#endif // !_CPUCLASS_H_

