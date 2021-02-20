#pragma once

#include <chrono>

class TimeCounter
{
public:
	TimeCounter();
	~TimeCounter();

private:
	std::chrono::milliseconds m_BeginTime;
};