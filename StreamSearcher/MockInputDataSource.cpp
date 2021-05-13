#include "MockInputDataSource.h"

#include <assert.h>
#include <sstream>

using namespace InputDataHandling;

bool MockInputDataSource::IsInputDataAvailable() const
{
	return !this->inputData.empty();
}

NamedInputStream MockInputDataSource::GetNextInputStream()
{
	assert(!this->inputData.empty());

	NamedInputStream inputDataStream
	{
		this->inputData.front().first,
		make_unique<istringstream>(this->inputData.front().second)
	};

	this->inputData.pop();

	return inputDataStream;
}

MockInputDataSource& MockInputDataSource::operator<< (const pair<string, string>& inputData)
{
	this->inputData.push(inputData);

	return *this;
}