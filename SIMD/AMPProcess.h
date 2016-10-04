#pragma once

#include "IProcess.h"
#include "InputDataStructure.h"

class AMPProcess : IProcess
{
public:
	AMPProcess(InputDataStructure Input);

	void Run();
	std::vector<double> GetOutput() const;

	~AMPProcess();

private:
	double m_Duration;
	InputDataStructure m_Input;
	std::vector<double> m_Output;

};

