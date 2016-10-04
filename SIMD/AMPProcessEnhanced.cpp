#include "stdafx.h"
#include "AMPProcessEnhanced.h"
#include <amp.h>
using namespace concurrency;

AMPProcessEnhanced::AMPProcessEnhanced(InputDataStructure& Input) : m_Input(Input)
{
}

void AMPProcessEnhanced::Run()
{
	unsigned int totalMatrixCells = m_Input.m_ContainerDimension*m_Input.m_ElementDimension;
	const ValueCollectionType& FlattenedInputCollection(m_Input.GetFlattenedTransposedValueCollection());

	extent<1> elementE(m_Input.m_ElementDimension);
	extent<1> containerE(m_Input.m_ContainerDimension);
	extent<1> matrixE(totalMatrixCells);

	ValueCollectionType OutputVector(m_Input.m_ElementDimension);

	extent<1> dimensionE(1);

	std::vector<unsigned int> ContainerDimensionCollection{ m_Input.m_ContainerDimension };
	std::vector<unsigned int> ElementDimensionCollection{ m_Input.m_ElementDimension };

	array_view<const unsigned int, 1> ContainerDimension(dimensionE, ContainerDimensionCollection);
	array_view<const unsigned int, 1> ElementDimension(dimensionE, ElementDimensionCollection);

	array_view<const double, 1> AmpInput(matrixE, FlattenedInputCollection);
	array_view<double, 1> AmpOutput(elementE, OutputVector);
	AmpOutput.discard_data(); //we don't need this to be copied to accelerator
	AmpOutput.refresh();
	
	parallel_for_each(elementE, [=](index<1> idx) restrict(amp)
	{
		const unsigned int containerElementStartIndex = idx[0] * ContainerDimension[0];
		const unsigned int containerElementEndIndex = (ContainerDimension[0]) + containerElementStartIndex;

		for (unsigned int elementIndex = containerElementStartIndex;
			elementIndex < containerElementEndIndex;
			++elementIndex)
		{
			AmpOutput(idx[0]) += AmpInput[elementIndex];
		}
	});

	AmpOutput.synchronize(); //make sure the outputvector is up-to-date from accel

	m_Output.swap(OutputVector);
}

const ValueCollectionType& AMPProcessEnhanced::GetOutput() const
{
	return m_Output;
}


AMPProcessEnhanced::~AMPProcessEnhanced()
{
}
