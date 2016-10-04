#pragma once
#include "IProcess.h"
#include "InputDataStructure.h"

class AMPProcessEnhanced : IProcess
{
public:
	AMPProcessEnhanced(InputDataStructure& Input);

	void Run();
	const ValueCollectionType& GetOutput() const;

	~AMPProcessEnhanced();

private:
	InputDataStructure& m_Input;
	ValueCollectionType m_Output;

};

