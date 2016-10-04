#include "stdafx.h"
#include "AMPProcess.h"
#include <amp.h>
using namespace concurrency;

AMPProcess::AMPProcess(InputDataStructure Input) : m_Input(Input)
{
}

void AMPProcess::Run()
{
	CollectionOfValueCollectionType InputCollection(m_Input.m_CollectionOfValueCollection);

	extent<1> elementE(m_Input.m_ElementDimension);

	ValueCollectionType OutputVector(m_Input.m_ElementDimension);
	
	array_view<double, 1> AmpOutput(elementE, OutputVector);
	AmpOutput.discard_data(); //we don't need this to be copied to accelerator

	for (unsigned int containerIndex = 0; containerIndex < m_Input.m_ContainerDimension; ++containerIndex)
	{
		array_view<const double, 1> ContainerInput(elementE, InputCollection[containerIndex]);
		parallel_for_each(elementE, [=](index<1> idx) restrict(amp)
		{
			AmpOutput(idx[0]) += ContainerInput(idx[0]);
		});
	}

	AmpOutput.synchronize(); //make sure the outputvector is up-to-date from accel

	m_Output.swap(OutputVector);
}

ValueCollectionType AMPProcess::GetOutput() const
{
	return m_Output;
}


AMPProcess::~AMPProcess()
{
}
