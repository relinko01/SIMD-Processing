#include "stdafx.h"
#include "FileOutput.h"
#include <iostream>
#include <sstream>
using namespace std;


FileOutput::FileOutput(string FileName)
{
	m_File.open(FileName + ".txt", ios_base::app);
}

void FileOutput::AppendLine(string TextLine, double value, string postFix)
{
	if (m_File.is_open())
	{
		ostringstream stringValue;
		stringValue << value;
		string stringDoubleValue = stringValue.str();

		m_File << TextLine + stringDoubleValue + postFix + "\n";
	}
}

void FileOutput::AppendLine(string TextLine, bool value)
{
	if (m_File.is_open())
	{
		if (value)
		{
			m_File << TextLine + "SAME" + "\n";
		}
		else
		{
			m_File << TextLine + "DIFFERENT" + "\n";
		}

	}
}


void FileOutput::AppendLine(string TextLine)
{
	if (m_File.is_open())
	{
		m_File << TextLine + "\n";
	}
}

void FileOutput::Close()
{
	if (m_File.is_open())
	{
		m_File.close();
	}
}


FileOutput::~FileOutput()
{
}
