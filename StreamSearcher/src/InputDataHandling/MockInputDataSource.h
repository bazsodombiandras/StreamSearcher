#pragma once

#include "IInputDataSource.h"
#include <queue>
#include <vector>

using namespace std;

namespace InputDataHandling
{
	/// <summary>
	/// Represents an input data source which allows working with mock data (eg. for tests).
	/// </summary>
	class MockInputDataSource: public IInputDataSource
	{
	private:
		// The input data pairs (name, data).
		queue<pair<string, string>> inputData;

	public:
		/// <summary>
		/// Checks whether input data is currently available in the input data source (or the input data source is empty).
		/// </summary>
		/// <returns>True if the input data source currently has available data.</returns>
		bool IsInputDataAvailable() const override;

		/// <summary>
		/// Gets the current input stream and advances the input data source to the next input stream.
		/// </summary>
		/// <returns>the current input stream.</returns>
		NamedInputStream GetCurrentInputStreamAndMoveNext() override;

		/// <summary>
		/// Adds a pair of input data (name, data) to this input data source.
		/// </summary>
		/// <param name="inputData">The pair of input data (name, data).</param>
		/// <returns>The current instance.</returns>
		MockInputDataSource& operator<< (const pair<string, string>& inputData);
	};
}

