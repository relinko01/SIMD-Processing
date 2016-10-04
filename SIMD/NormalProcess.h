#pragma once

#include "IProcess.h"
#include "InputDataStructure.h"

class NormalProcess : IProcess
{
public:
	NormalProcess(InputDataStructure& Input);

	void Run();
	const ValueCollectionType& GetOutput() const;

	~NormalProcess();

private:
	InputDataStructure& m_Input;
	std::vector<double> m_Output;

};

