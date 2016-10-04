#pragma once
#include <vector>

class OutputVerifier
{
public:
	OutputVerifier(const std::vector<double>& AMPOutput, const std::vector<double>& NormalOutput);

	void Run();
	bool IsValid();

	~OutputVerifier();
private:
	std::vector<double> m_AMPOutput;
	std::vector<double> m_NormalOutput;
	bool m_isValid;
};

