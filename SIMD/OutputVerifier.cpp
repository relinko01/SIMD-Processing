#include "stdafx.h"
#include "OutputVerifier.h"
#include "InputDataStructure.h"


OutputVerifier::OutputVerifier(const ValueCollectionType& AMPOutput, const ValueCollectionType& NormalOutput) :
								m_AMPOutput(AMPOutput), m_NormalOutput(NormalOutput)
{
	m_isValid = true;
}

bool IsEqual(double x, double y)
{
	double diff = fabs(x - y);
	bool isEqual = diff < DBL_EPSILON;
	return isEqual;
}

void OutputVerifier::Run()
{
	for (unsigned int index = 0; index < m_NormalOutput.size(); ++index)
	{
		double normalOutputValue = m_NormalOutput[index];
		double ampOutputValue = m_AMPOutput[index];
		if (!IsEqual(normalOutputValue, ampOutputValue))
		{
			m_isValid = false;
			break;
		}
	}
}

bool OutputVerifier::IsValid()
{
	return m_isValid;
}



OutputVerifier::~OutputVerifier()
{
}
