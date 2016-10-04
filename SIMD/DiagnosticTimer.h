#pragma once
#include <ctime>

class DiagnosticTimer
{
public:
	DiagnosticTimer();

	void Start();
	double GetDuration();

	~DiagnosticTimer();

private:
	double m_Duration;
	std::clock_t m_Start;
};

