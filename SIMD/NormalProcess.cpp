#include "stdafx.h"
#include "NormalProcess.h"
#include <amp.h>
using namespace concurrency;

NormalProcess::NormalProcess(InputDataStructure& Input) : m_Input(Input)
{
}

void NormalProcess::Run()
{
	const CollectionOfValueCollectionType& InputCollection(m_Input.GetCollectionOfValueCollection());
	
	extent<1> elementE(m_Input.m_ElementDimension);

	ValueCollectionType OutputVector(m_Input.m_ElementDimension);

	array_view<double, 1> AmpOutput(elementE, OutputVector);

	for (unsigned int containerIndex = 0; containerIndex < m_Input.m_ContainerDimension; ++containerIndex)
	{
		index<1> idx(0);
		array_view<const double, 1> ContainerInput(elementE, InputCollection[containerIndex]);
		//Element Traversal
		for (idx[0] = 0; idx[0] < elementE[0]; ++idx[0])
		{
			AmpOutput(idx[0]) += (ContainerInput(idx[0]));
		}
	}

	AmpOutput.synchronize(); //make sure the outputvector is up-to-date from accel

	m_Output.swap(OutputVector);
}

const ValueCollectionType& NormalProcess::GetOutput() const
{
	return m_Output;
}


NormalProcess::~NormalProcess()
{
}
