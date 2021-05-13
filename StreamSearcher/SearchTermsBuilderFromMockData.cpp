#include "SearchTermsBuilderFromMockData.h"

using namespace SearchTerms;

set<string> SearchTermsBuilderFromMockData::Build()
{
	return this->searchTerms;
}

SearchTermsBuilderFromMockData& SearchTermsBuilderFromMockData::operator<< (const string& searchTerm)
{
	this->searchTerms.insert(searchTerm);

	return *this;
}
