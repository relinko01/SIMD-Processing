#include "stdafx.h"
#include "InputDataStructure.h"

void PopulateWithRandomData(unsigned int maxContainerCount, unsigned int maxElementCount, double upperValueLimit,
	CollectionOfValueCollectionType& CollectionOfValueCollection)
{
	CollectionOfValueCollection.resize(maxContainerCount);

	for (unsigned int containerIndex = 0; containerIndex < maxContainerCount; ++containerIndex)
	{
		ValueCollectionType ValueCollection;
		ValueCollection.resize(maxElementCount);
		for (unsigned int elementIndex = 0; elementIndex < maxElementCount; ++elementIndex)
		{
			double randomValue = ((double)rand() / (RAND_MAX))*upperValueLimit;
			ValueCollection[elementIndex] = randomValue;
		}
		CollectionOfValueCollection[containerIndex] = ValueCollection;
	}
}

void PopulateWithOnes(unsigned int maxContainerCount, unsigned int maxElementCount, double upperValueLimit,
	CollectionOfValueCollectionType& CollectionOfValueCollection)
{
	CollectionOfValueCollection.resize(maxContainerCount);

	for (unsigned int containerIndex = 0; containerIndex < maxContainerCount; ++containerIndex)
	{
		ValueCollectionType ValueCollection;
		ValueCollection.resize(maxElementCount);
		for (unsigned int elementIndex = 0; elementIndex < maxElementCount; ++elementIndex)
		{
			ValueCollection[elementIndex] = 1.0;
		}
		CollectionOfValueCollection[containerIndex] = ValueCollection;
	}
}

void PopulateWithAlternatingOnesAndZeroes(unsigned int maxContainerCount, unsigned int maxElementCount, double upperValueLimit,
	CollectionOfValueCollectionType& CollectionOfValueCollection)
{
	CollectionOfValueCollection.resize(maxContainerCount);

	for (unsigned int containerIndex = 0; containerIndex < maxContainerCount; ++containerIndex)
	{
		ValueCollectionType ValueCollection;
		ValueCollection.resize(maxElementCount);
		for (unsigned int elementIndex = 0; elementIndex < maxElementCount; ++elementIndex)
		{
			if (containerIndex % 2 == 0)
			{
				ValueCollection[elementIndex] = 1.0;
			}
			else
			{
				ValueCollection[elementIndex] = 0.0;
			}
		}
		CollectionOfValueCollection[containerIndex] = ValueCollection;
	}
}

void PopulateWithElementIncrementByOne(unsigned int maxContainerCount, unsigned int maxElementCount, double upperValueLimit,
	CollectionOfValueCollectionType& CollectionOfValueCollection)
{
	CollectionOfValueCollection.resize(maxContainerCount);

	for (unsigned int containerIndex = 0; containerIndex < maxContainerCount; ++containerIndex)
	{
		ValueCollectionType ValueCollection;
		ValueCollection.resize(maxElementCount);
		for (unsigned int elementIndex = 0; elementIndex < maxElementCount; ++elementIndex)
		{
			ValueCollection[elementIndex] = elementIndex;
		}
		CollectionOfValueCollection[containerIndex] = ValueCollection;
	}
}


void InputDataStructure::SetFlattenedTransposedValueCollection()
{
	unsigned int totalCells = m_ContainerDimension * m_ElementDimension;
	m_FlattenedTransposedValueCollection.resize(totalCells);

	unsigned int containerIndex = 0;
	for (CollectionOfValueCollectionType::const_iterator ContainerIter(m_CollectionOfValueCollection.begin());
		ContainerIter != m_CollectionOfValueCollection.end();
		++ContainerIter, ++containerIndex)
	{
		unsigned int elementIndex = 0;
		ValueCollectionType CurrentContainer = *ContainerIter;
		for (ValueCollectionType::const_iterator ElementIter = CurrentContainer.begin();
			ElementIter != CurrentContainer.end();
			++ElementIter, ++elementIndex)
		{
			m_FlattenedTransposedValueCollection[((m_ContainerDimension * elementIndex) + containerIndex)] = *ElementIter;
		}
	}
}

InputDataStructure::InputDataStructure(unsigned int maxContainerCount, unsigned int maxElementCount, double upperValueLimit, int processCycles)
{
	m_ContainerDimension = maxContainerCount;
	m_ElementDimension = maxElementCount;
	m_ProcessCycles = processCycles;

	PopulateWithOnes(maxContainerCount, maxElementCount, upperValueLimit, m_CollectionOfValueCollection);
	SetFlattenedTransposedValueCollection();
}

const CollectionOfValueCollectionType& InputDataStructure::GetCollectionOfValueCollection() const
{
	return m_CollectionOfValueCollection;
}

const ValueCollectionType& InputDataStructure::GetFlattenedTransposedValueCollection() const
{
	return m_FlattenedTransposedValueCollection;
}

InputDataStructure::~InputDataStructure()
{
}
