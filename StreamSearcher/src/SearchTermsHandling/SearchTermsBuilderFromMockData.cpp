#include "SearchTermsBuilderFromMockData.h"

using namespace SearchTermsHandling;

set<string> SearchTermsBuilderFromMockData::Build()
{
	return this->searchTerms;
}

SearchTermsBuilderFromMockData& SearchTermsBuilderFromMockData::operator<< (const string& searchTerm)
{
	this->searchTerms.insert(searchTerm);

	return *this;
}
