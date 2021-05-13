#include "SearchTermsBuilderFromStream.h"

#include <fstream>

using namespace SearchTermsHandling;
using namespace std;

const size_t SearchTermsBuilderFromStream::MaxSearchTermSize = 4096;

SearchTermsBuilderFromStream::SearchTermsBuilderFromStream(istream& inputStream):
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