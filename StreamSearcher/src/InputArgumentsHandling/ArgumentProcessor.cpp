#include "ArgumentProcessor.h"
#include "../Logging/Logger.h"

#include <filesystem>
#include <stdexcept>
#include <sstream>
#include <string>

using namespace InputArgumentsHandling;
using namespace Logging;
using namespace std;

void ArgumentProcessor::DisplayUsageInstructions(const string& appName)
{
	Logger::Info("Usage:");
	Logger::Info(appName + " " + "SearchTermsFile DataFile1 ... DataFileN");
}

InputArguments ArgumentProcessor::InterpretArguments(int argc, char* argv[])
{
	if (argc < 3)
	{
		DisplayUsageInstructions(filesystem::path(argv[0]).filename().string());
		throw std::invalid_argument("There should be at least 2 command line argument specified (one search terms file and at least one data file).");
	}

	InputArguments inputArgs
	{
		argv[1],
		vector<string>(argv + 2, argv + argc),
	};

	Logger::Debug("Input argument search terms file: \n" + inputArgs.searchTermsFile + "\n");
	Logger::Debug("Input argument data files: ");
	stringstream dataFilesListStream;
	copy(begin(inputArgs.dataFiles), end(inputArgs.dataFiles), ostream_iterator<string>(dataFilesListStream, " "));
	Logger::Debug(dataFilesListStream.str());

	return inputArgs;
}
