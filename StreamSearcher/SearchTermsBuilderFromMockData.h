#pragma once

#include "ISearchTermsBuilder.h"

#include <set>
#include <string>

using namespace std;

namespace SearchTermsHandling
{
	/// <summary>
	/// Represents a search terms builder which builds the collection of search terms from mock data (can be used for tests).
	/// </summary>
	class SearchTermsBuilderFromMockData: public ISearchTermsBuilder
	{
	private:
		/// <summary>
		/// The mock data search terms.
		/// </summary>
		set<string> searchTerms;

	public:
		/// <summary>
		/// Builds the collection of search terms.
		/// </summary>
		/// <returns>the collection of search terms.</returns>
		set<string> Build() override;

		/// <summary>
		/// Add a mock data search term to the search term builder.
		/// </summary>
		/// <param name="searchTerm">The search term.</param>
		/// <returns>The current instance.</returns>
		SearchTermsBuilderFromMockData& operator<< (const string& searchTerm);
	};
}

