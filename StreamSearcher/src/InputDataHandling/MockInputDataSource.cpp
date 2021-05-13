#include "MockInputDataSource.h"

#include <assert.h>
#include <sstream>

using namespace InputDataHandling;

bool MockInputDataSource::IsInputDataAvailable() const
{
	return !this->inputData.empty();
}

NamedInputStream MockInputDataSource::GetCurrentInputStreamAndMoveNext()
{
	assert(!this->inputData.empty());

	NamedInputStream inputDataStream
	{
		// The name of the input stream is the stored name of the data pair.
		this->inputData.front().first,

		// The input stream is constructed from the current input data.
		make_unique<istringstream>(this->inputData.front().second)
	};

	// Allow moving to the next input data/stream by removing the current one.
	this->inputData.pop();

	return inputDataStream;
}

MockInputDataSource& MockInputDataSource::operator<< (const pair<string, string>& inputData)
{
	this->inputData.push(inputData);

	return *this;
}