#include "FileInputDataSource.h"

#include <assert.h>
#include <filesystem>
#include <fstream>
#include <iostream>

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

NamedInputStream FileInputDataSource::GetNextInputStream()
{
	assert(!this->inputFiles.empty());

	NamedInputStream inputDataStream
	{
		filesystem::path(this->inputFiles.front()).filename().string(),
		make_unique<ifstream>(this->inputFiles.front())
	};

	this->inputFiles.pop();

	return inputDataStream;
}
