#pragma once

#include "ISearchTermsRegistry.h"
#include "ISearchTermsRegistryBuilder.h"


using namespace std;

namespace SearchTerms
{
	class SearchTermsRegistryBuilderFromFile : public ISearchTermsRegistryBuilder
	{
	private:
		const string inputFile;

		SearchTermsRegistryBuilderFromFile() = delete;
		SearchTermsRegistryBuilderFromFile(const SearchTermsRegistryBuilderFromFile&) = delete;
		SearchTermsRegistryBuilderFromFile(SearchTermsRegistryBuilderFromFile&&) = delete;

		SearchTermsRegistryBuilderFromFile& operator= (const SearchTermsRegistryBuilderFromFile&) = delete;
		SearchTermsRegistryBuilderFromFile& operator= (SearchTermsRegistryBuilderFromFile&&) = delete;

	public:
		SearchTermsRegistryBuilderFromFile(const string& inputFile);

		virtual ~SearchTermsRegistryBuilderFromFile() = default;

		virtual void Build(ISearchTermsRegistry& searchTerms) const;
	};
}

