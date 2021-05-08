#include <filesystem>
#include <iostream>
#include <stdexcept>
#include <string>

#include "ArgumentProcessor.h"

using namespace std;
using namespace InputDataHandling;

void ArgumentProcessor::DisplayUsage(const wstring& appName)
{
	wcout << "Usage:" << endl;
	wcout << appName << " " << "DictionaryFile DataFile1 ... DataFileN" << endl;
	wcout << endl;
}

InputData ArgumentProcessor::InterpretArguments(int argc, wchar_t* argv[])
{
	if (argc < 3)
	{
		DisplayUsage(std::filesystem::path(argv[0]).filename());
		throw std::invalid_argument("There should be at least 2 command line argument specified (one dictionary file and at least one data file).");
	}

	return InputData
	{
		argv[1],
		vector<wstring>(argv + 2, argv + argc),
	};
}
