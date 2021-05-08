#pragma once

#include "ISearchTermsRegistry.h"
#include "ISearchTermsRegistryBuilder.h"


using namespace std;

class SearchTermsRegistryBuilderFromFile : public ISearchTermsRegistryBuilder
{
private:
	const string inputFile;

	SearchTermsRegistryBuilderFromFile() = delete;
	SearchTermsRegistryBuilderFromFile(const SearchTermsRegistryBuilderFromFile&) = delete;
	SearchTermsRegistryBuilderFromFile(SearchTermsRegistryBuilderFromFile&&) = default;
	
	SearchTermsRegistryBuilderFromFile& operator= (const SearchTermsRegistryBuilderFromFile&) = delete;
	SearchTermsRegistryBuilderFromFile& operator= (SearchTermsRegistryBuilderFromFile&&) = delete;

public:
	SearchTermsRegistryBuilderFromFile(const string& inputFile);

	~SearchTermsRegistryBuilderFromFile() = default;

	void Build(ISearchTermsRegistry& searchTermsRegistry) const;
};

