#include "SearchTermsBuilderFromFile.h"

#include <fstream>
#include <iostream>

using namespace SearchTerms;
using namespace std;

SearchTermsBuilderFromFile::SearchTermsBuilderFromFile(const string& inputFile) :
	inputFile(inputFile)
{
}

void SearchTermsBuilderFromFile::Build(set<string>& searchTerms) const
{
	const size_t searchTermMaxSize = 4096;
	char searchTerm[searchTermMaxSize];

	searchTerms.clear();

	ifstream inputStream(this->inputFile);
	while (inputStream.getline(searchTerm, searchTermMaxSize))
	{
		searchTerms.insert(searchTerm);
	}
}