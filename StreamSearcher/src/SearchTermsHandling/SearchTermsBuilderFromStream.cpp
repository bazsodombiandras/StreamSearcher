#include "SearchTermsBuilderFromStream.h"

#include <fstream>

using namespace SearchTermsHandling;
using namespace std;

// Let's assume that all search terms are not longer than the below number of characters.
// This limitation is imposed by the std::istream::geline() implementation.
const size_t SearchTermsBuilderFromStream::MaxSearchTermLength = 4096;

SearchTermsBuilderFromStream::SearchTermsBuilderFromStream(istream& inputStream):
	inputStream(inputStream)
{
}

set<string> SearchTermsBuilderFromStream::Build()
{
	set<string> searchTerms;

	// Read the search terms from the input streama nd add them to the search terms collection.
	char searchTerm[MaxSearchTermLength];
	while (this->inputStream.getline(searchTerm, MaxSearchTermLength))
	{
		searchTerms.insert(searchTerm);
	}

	return searchTerms;
}