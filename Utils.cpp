#include "Utils.h"

#include <fstream>

#include <cassert>

std::string DumpToString(const std::string& InputPath)
{
	//output to return
	std::string OutputString;

	if (std::ifstream InputFile{ InputPath, std::ios::in | std::ios::ate })
	{
		//This HAS TO BE TRUE or we crash (on purpose)
		assert(InputFile.is_open() && "File didn't open");

		// Get the current "GET" postiion to determine how big it is
		auto Size = InputFile.tellg();
		// Allocate a string that is the right size
		OutputString = std::string(Size, '\0');

		//Move the "GET" position back to the beginning
		InputFile.seekg(0);

		//Write input file to OutputString
		InputFile.read(&OutputString[0], Size);

		//Close the file
		InputFile.close();
	}

	return OutputString;
}