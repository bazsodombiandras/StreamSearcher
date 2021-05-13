#pragma once

#include <set>
#include <string>

using namespace std;

namespace SearchTermsHandling
{
	class SearchTermsBuilderFromMockData
	{
	private:
		set<string> searchTerms;

	public:
		virtual set<string> Build();

		virtual SearchTermsBuilderFromMockData& operator<< (const string& searchTerm);
	};
}

