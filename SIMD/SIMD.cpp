// SIMD.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

#include "InputDataStructure.h"
#include "NormalProcess.h"
#include "AMPProcessEnhanced.h"
#include "OutputVerifier.h"
#include "DiagnosticTimer.h"
#include "FileOutput.h"

//https://msdn.microsoft.com/en-us/magazine/hh882446.aspx
//https://blogs.msdn.microsoft.com/nativeconcurrency/2011/12/09/passing-pointers-through-c-amp/
//http://www.drdobbs.com/windows/microsofts-c-amp-unveiled/231600761
int main()
{
	unsigned int containers = 100000;
	unsigned int elementsPerContainer = 100;
	int maxValue = 1000000;
	int processCycles = 100;
	InputDataStructure NewData(containers, elementsPerContainer, maxValue, processCycles);

	AMPProcessEnhanced AMPEnhanced(NewData);
	NormalProcess Normal(NewData);

	DiagnosticTimer Timer;
	
	double ampEnhancedDuration = 0.0;
	double normalDuration = 0.0;

	bool AreResultsSame = true;
	for (int cycle = 0; cycle < processCycles; ++cycle)
	{
		Timer.Start();
		AMPEnhanced.Run();
		ampEnhancedDuration += Timer.GetDuration();

		Timer.Start();
		Normal.Run();
		normalDuration += Timer.GetDuration();

		OutputVerifier AMPToNormalVerifier(AMPEnhanced.GetOutput(), Normal.GetOutput());

		AMPToNormalVerifier.Run();

		if (!AMPToNormalVerifier.IsValid())
		{
			AreResultsSame = false;
			break;
		}
	}

	FileOutput File("AMP_Performance");
	
	double ampMultiplier = normalDuration / ampEnhancedDuration;
	long totalProcessed = containers * elementsPerContainer * processCycles;
	File.AppendLine("---------------------------------------");
	File.AppendLine("Containers Processed: ", containers, "");
	File.AppendLine("Elements Per Container Processed: ", elementsPerContainer, "");
	File.AppendLine("Value Range: 0-", maxValue, "");
	File.AppendLine("Process Cycles: ", processCycles, "x");
	File.AppendLine("Total Values Processed: ", totalProcessed, "");
;	File.AppendLine("Normal Run: ", normalDuration, "s");
	File.AppendLine("AMP Run: ", ampEnhancedDuration, "s");
	File.AppendLine("AMP Increased Performance: ", ampMultiplier, "x");
	File.AppendLine("Values Are ", AreResultsSame);
	File.AppendLine("---------------------------------------");

    return 0;
}

