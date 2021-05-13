#include "FileInputDataSource.h"

#include <assert.h>
#include <filesystem>
#include <fstream>

using namespace InputDataHandling;
using namespace std;

FileInputDataSource::FileInputDataSource(const vector<string> inputFiles):
	inputFiles(deque(begin(inputFiles), end(inputFiles)))
{
}

bool FileInputDataSource::IsInputDataAvailable() const
{
	return !this->inputFiles.empty();
}

NamedInputStream FileInputDataSource::GetCurrentInputStreamAndMoveNext()
{
	assert(!this->inputFiles.empty());

	NamedInputStream inputDataStream
	{
		// The name of the input stream is the short name (without the path) of the current input file.
		filesystem::path(this->inputFiles.front()).filename().string(),

		// The input stream is constructed from the current input file.
		make_unique<ifstream>(this->inputFiles.front())
	};

	// Allow moving to the next input file/stream by removing the current one.
	this->inputFiles.pop();

	return inputDataStream;
}
