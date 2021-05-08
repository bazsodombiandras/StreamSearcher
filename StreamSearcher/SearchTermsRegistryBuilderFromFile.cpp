#include "SearchTermsRegistryBuilderFromFile.h"

#include <fstream>
#include <iostream>

using namespace SearchTermsHandling;
using namespace std;

SearchTermsRegistryBuilderFromFile::SearchTermsRegistryBuilderFromFile(const string& inputFile) :
	inputFile(inputFile)
{
}

void SearchTermsRegistryBuilderFromFile::Build(ISearchTermsRegistry& searchTermsRegistry) const
{
	const size_t searchTermMaxSize = 4096;
	char searchTerm[searchTermMaxSize];

	searchTermsRegistry.Clear();

	ifstream inputStream(this->inputFile);
	while (inputStream.getline(searchTerm, searchTermMaxSize))
	{
		searchTermsRegistry.Add(searchTerm);
	}
}