#pragma once

#include "../InputDataHandling/IInputDataSource.h"

#include <istream>
#include <set>

using namespace InputDataHandling;
using namespace std;

namespace StreamSearch
{
	/// <summary>
	/// Searches streams of data for multiple search terms.
	/// </summary>
	class StreamSearcher
	{
	private:
		/// <summary>
		/// The search terms.
		/// </summary>
		set<string> searchTerms;

		/// <summary>
		/// The results (found search terms in the data streams).
		/// </summary>
		set<string> results;

		/// <summary>
		/// The default constructor si disabled because the search terms are always needed to construct an instance (makes no sense to search for nothing).
		/// </summary>
		StreamSearcher() = delete;

		/// <summary>
		/// Search a single input data stream for the search terms.
		/// </summary>
		/// <param name="inputStream">the input data stream.</param>
		void SearchStream(istream& inputStream);

	public:
		/// <summary>
		/// Constructs an insatnce of ths class based on a collection of search terms.
		/// </summary>
		/// <param name="searchTerms">The search terms.</param>
		StreamSearcher(const set<string>& searchTerms);

		/// <summary>
		/// Allows copying the data of the stream searcher through the default copy constructor.
		/// </summary>
		/// <param name="">The instance to copy the data from.</param>
		StreamSearcher(const StreamSearcher&) = default;

		/// <summary>
		/// Allows moving the data of the stream searcher through the default move constructor.
		/// </summary>
		/// <param name="">The instance to move the data from.</param>
		StreamSearcher(StreamSearcher&&) = default;

		/// <summary>
		/// Gets the results of the last search.
		/// </summary>
		/// <returns>The results.</returns>
		const set<string>& GetResults() const;

		/// <summary>
		/// SEarches all the input data for the search terms.
		/// </summary>
		/// <param name="inputDataSource">The input data source.</param>
		void SearchInputData(IInputDataSource& inputDataSource);

		/// <summary>
		/// Allows copying the data of the stream searcher through the default copy assignment operator.
		/// </summary>
		/// <param name="">The instance to copy the data from.</param>
		/// <returns>The instance into which the data has been copied.</returns>
		StreamSearcher& operator= (const StreamSearcher&) = default;

		/// <summary>
		/// Allows moving the data of the stream searcher through the default move assignment operator.
		/// </summary>
		/// <param name="">The instance to move the data from.</param>
		/// <returns>The instance into which the data has been moved.</returns>
		StreamSearcher& operator= (StreamSearcher&&) = default;
	};
}

