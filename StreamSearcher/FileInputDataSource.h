#pragma once

#include "IInputDataSource.h"
#include <queue>
#include <vector>

using namespace std;

namespace InputDataHandling
{
	class FileInputDataSource : public IInputDataSource
	{
	private:
		queue<string> inputFiles;

	public:
		FileInputDataSource() = default;

		FileInputDataSource(const vector<string> inputFiles);
		FileInputDataSource(const FileInputDataSource&) = default;
		FileInputDataSource(FileInputDataSource&&) = default;
		virtual ~FileInputDataSource() = default;

		bool IsInputDataAvailable() const override;
		NamedInputStream GetNextInputStream() override;

		FileInputDataSource& operator= (const FileInputDataSource&) = default;
		FileInputDataSource& operator= (FileInputDataSource&&) = default;
	};
}