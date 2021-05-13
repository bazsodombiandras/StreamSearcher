#include "SearchTermsBuilderFromStream.h"

#include <fstream>
#include <iostream>

using namespace SearchTerms;
using namespace std;

const size_t SearchTermsBuilderFromStream::MaxSearchTermSize = 4096;

SearchTermsBuilderFromStream::SearchTermsBuilderFromStream(istream& inputStream) :
	inputStream(inputStream)
{
}

set<string> SearchTermsBuilderFromStream::Build()
{
	set<string> searchTerms;

	char searchTerm[MaxSearchTermSize];
	while (this->inputStream.getline(searchTerm, MaxSearchTermSize))
	{
		searchTerms.insert(searchTerm);
	}

	return searchTerms;
}