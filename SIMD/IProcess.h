#pragma once
#include "InputDataStructure.h"

class IProcess
{
public:
	IProcess();

	virtual void Run() = 0;
	virtual const ValueCollectionType& GetOutput() const = 0;

	virtual ~IProcess();
};

