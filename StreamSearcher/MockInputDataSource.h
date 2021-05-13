#pragma once

#include "IInputDataSource.h"
#include <queue>
#include <vector>

using namespace std;

namespace InputDataHandling
{
	class MockInputDataSource: public IInputDataSource
	{
	private:
		queue<pair<string, string>> inputData;

	public:
		bool IsInputDataAvailable() const override;
		NamedInputStream GetNextInputStream() override;

		MockInputDataSource& operator<< (const pair<string, string>& inputData);
	};
}

