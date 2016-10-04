#include "stdafx.h"
#include "DiagnosticTimer.h"


DiagnosticTimer::DiagnosticTimer()
{
}

void DiagnosticTimer::Start()
{
	m_Start = std::clock();
}

double DiagnosticTimer::GetDuration()
{
	return (std::clock() - m_Start) / (double)CLOCKS_PER_SEC;
}


DiagnosticTimer::~DiagnosticTimer()
{

}
