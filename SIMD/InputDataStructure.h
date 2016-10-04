#pragma once

#include <vector>

typedef std::vector<double> ValueCollectionType;
typedef std::vector<ValueCollectionType> CollectionOfValueCollectionType;

class InputDataStructure
{
public:
	InputDataStructure(unsigned int maxCountainerCount, unsigned int maxElementCount, double upperValueLimit, int processCycles);

	const CollectionOfValueCollectionType& InputDataStructure::GetCollectionOfValueCollection() const;
	const ValueCollectionType& InputDataStructure::GetFlattenedTransposedValueCollection() const;

	unsigned int m_ContainerDimension;
	unsigned int m_ElementDimension;
	int m_ProcessCycles;

	~InputDataStructure();

private:
	void SetFlattenedTransposedValueCollection();

	CollectionOfValueCollectionType m_CollectionOfValueCollection;
	ValueCollectionType m_FlattenedTransposedValueCollection;

};

