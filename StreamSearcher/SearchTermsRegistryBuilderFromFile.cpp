#include "SearchTermsRegistryBuilderFromFile.h"

#include <fstream>
#include <iostream>

using namespace SearchTerms;
using namespace std;

SearchTermsRegistryBuilderFromFile::SearchTermsRegistryBuilderFromFile(const string& inputFile) :
	inputFile(inputFile)
{
}

void SearchTermsRegistryBuilderFromFile::Build(ISearchTermsRegistry& searchTerms) const
{
	const size_t searchTermMaxSize = 4096;
	char searchTerm[searchTermMaxSize];

	searchTerms.Clear();

	ifstream inputStream(this->inputFile);
	while (inputStream.getline(searchTerm, searchTermMaxSize))
	{
		searchTerms.Add(searchTerm);
	}
}