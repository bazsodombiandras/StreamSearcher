#pragma once

#include "IInputDataSource.h"
#include <queue>
#include <vector>

using namespace std;

namespace InputDataHandling
{
	/// <summary>
	/// Represents an input data source which takes its data from files.
	/// </summary>
	class FileInputDataSource: public IInputDataSource
	{
	private:
		/// <summary>
		/// The input files.
		/// </summary>
		queue<string> inputFiles;

	public:
		/// <summary>
		/// Default constructor.
		/// </summary>
		FileInputDataSource() = default;

		/// <summary>
		/// Constructs an instance of the class based on a collection of input files.
		/// </summary>
		/// <param name="inputFiles">The input files.</param>
		FileInputDataSource(const vector<string> inputFiles);

		/// <summary>
		/// Allow copying through the default copy constructor.
		/// </summary>
		/// <param name=""></param>
		FileInputDataSource(const FileInputDataSource&) = default;

		/// <summary>
		/// Allow moving through the default move constructor.
		/// </summary>
		/// <param name=""></param>
		FileInputDataSource(FileInputDataSource&&) = default;

		/// <summary>
		/// Default destructor (nothing special to destroy).
		/// </summary>
		virtual ~FileInputDataSource() = default;

		/// <summary>
		/// Checks whether input data is currently available in the input data source (or the input data source is empty).
		/// </summary>
		/// <returns>True if the input data source currently has available data.</returns>
		bool IsInputDataAvailable() const override;

		/// <summary>
		/// Gets the current input stream and advances the input data souurce to the next input stream.
		/// </summary>
		/// <returns>the current input stream.</returns>
		NamedInputStream GetCurrentInputStreamAndMoveNext() override;

		/// <summary>
		/// Allow copying through the default copy assignment operator.
		/// </summary>
		/// <param name="">The other instance to copy from.</param>
		/// <returns>The instance into which the data has been copied.</returns>
		FileInputDataSource& operator= (const FileInputDataSource&) = default;

		/// <summary>
		/// Allow moving through the default move assignment operator.
		/// </summary>
		/// <param name="">The other instance to move from.</param>
		/// <returns>The instance into which the data has been moved.</returns>
		FileInputDataSource& operator= (FileInputDataSource&&) = default;
	};
}