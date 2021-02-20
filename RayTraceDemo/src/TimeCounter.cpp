#include "rtpch.h"
#include "TimeCounter.h"

TimeCounter::TimeCounter()
{
	std::cout << "--------------------- Timer Begin ---------------------\n";
	m_BeginTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
}

TimeCounter::~TimeCounter()
{
	auto currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());

	int timeCost = (currentTime - m_BeginTime).count();
	float sec = timeCost * 0.001f;

	printf("time spend : %.3fs\n", sec);
	std::cout << "--------------------- Timer End -----------------------\n";
}
