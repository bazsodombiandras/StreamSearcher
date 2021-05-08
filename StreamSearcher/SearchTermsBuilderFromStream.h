#pragma once

#include "ISearchTermsBuilder.h"
#include<set>


using namespace std;

namespace SearchTerms
{
	class SearchTermsBuilderFromStream : public ISearchTermsBuilder
	{
	private:
		static const size_t MaxSearchTermSize;

		istream& inputStream;

		SearchTermsBuilderFromStream() = delete;
		SearchTermsBuilderFromStream(const SearchTermsBuilderFromStream&) = delete;
		SearchTermsBuilderFromStream(SearchTermsBuilderFromStream&&) = delete;

		SearchTermsBuilderFromStream& operator= (const SearchTermsBuilderFromStream&) = delete;
		SearchTermsBuilderFromStream& operator= (SearchTermsBuilderFromStream&&) = delete;

	public:
		SearchTermsBuilderFromStream(istream& inputStream);

		virtual ~SearchTermsBuilderFromStream() = default;

		virtual void Build(set<string>& searchTerms);
	};
}

