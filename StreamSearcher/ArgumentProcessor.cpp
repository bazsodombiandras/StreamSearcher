#include "ArgumentProcessor.h"

#include <filesystem>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace InputArgumentsHandling;
using namespace std;

void ArgumentProcessor::DisplayUsage(const string& appName)
{
	cout << "Usage:" << endl;
	cout << appName << " " << "SearchTermsFile DataFile1 ... DataFileN" << endl;
	cout << endl;
}

InputArguments ArgumentProcessor::InterpretArguments(int argc, char* argv[])
{
	if (argc < 3)
	{
		DisplayUsage(filesystem::path(argv[0]).filename().string());
		throw std::invalid_argument("There should be at least 2 command line argument specified (one search terms file and at least one data file).");
	}

	InputArguments inputArgs
	{
		argv[1],
		vector<string>(argv + 2, argv + argc),
	};

	cout << "Input argument search terms file: " << endl << inputArgs.searchTermsFile << endl << endl;
	cout << "Input argument data files: " << endl;
	copy(begin(inputArgs.dataFiles), end(inputArgs.dataFiles), ostream_iterator<string>(cout, "\n"));
	cout << endl;

	return inputArgs;
}
