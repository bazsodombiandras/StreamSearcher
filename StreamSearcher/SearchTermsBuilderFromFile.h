#pragma once

#include "ISearchTermsBuilder.h"
#include<set>


using namespace std;

namespace SearchTerms
{
	class SearchTermsBuilderFromFile : public ISearchTermsBuilder
	{
	private:
		const string inputFile;

		SearchTermsBuilderFromFile() = delete;
		SearchTermsBuilderFromFile(const SearchTermsBuilderFromFile&) = delete;
		SearchTermsBuilderFromFile(SearchTermsBuilderFromFile&&) = delete;

		SearchTermsBuilderFromFile& operator= (const SearchTermsBuilderFromFile&) = delete;
		SearchTermsBuilderFromFile& operator= (SearchTermsBuilderFromFile&&) = delete;

	public:
		SearchTermsBuilderFromFile(const string& inputFile);

		virtual ~SearchTermsBuilderFromFile() = default;

		virtual void Build(set<string>& searchTerms) const;
	};
}

