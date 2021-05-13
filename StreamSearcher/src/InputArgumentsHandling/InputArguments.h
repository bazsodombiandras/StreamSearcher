#pragma once

#include <string>
#include <vector>

using namespace std;

namespace InputArgumentsHandling
{
	/// <summary>
	/// Represents the input arguments passed to the console application.
	/// </summary>
	class InputArguments
	{
	public:
		/// <summary>
		/// The input file containing the search terms.
		/// </summary>
		string searchTermsFile;

		/// <summary>
		/// The collection of data files containing the data to be searched.
		/// </summary>
		vector<string> dataFiles;
	};
}

