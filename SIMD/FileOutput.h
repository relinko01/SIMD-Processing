#pragma once
#include <fstream>
class FileOutput
{
public:
	FileOutput(std::string FileName);
	void AppendLine(std::string TextLine, double value, std::string postFix);
	void AppendLine(std::string TextLine);
	void AppendLine(std::string TextLine, bool value);
	void Close();
	~FileOutput();

private:
	std::ofstream m_File;
};

