#pragma once

#include "ISearchTermsBuilder.h"

#include <set>
#include <string>

using namespace std;

namespace SearchTermsHandling
{
	class SearchTermsBuilderFromMockData: public ISearchTermsBuilder
	{
	private:
		set<string> searchTerms;

	public:
		set<string> Build() override;

		SearchTermsBuilderFromMockData& operator<< (const string& searchTerm);
	};
}

