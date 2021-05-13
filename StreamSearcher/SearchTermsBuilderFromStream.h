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

	public:
		SearchTermsBuilderFromStream(istream& inputStream);

		SearchTermsBuilderFromStream(const SearchTermsBuilderFromStream&) = default;
		SearchTermsBuilderFromStream(SearchTermsBuilderFromStream&&) = default;

		virtual ~SearchTermsBuilderFromStream() = default;

		virtual set<string> Build();

		virtual SearchTermsBuilderFromStream& operator= (const SearchTermsBuilderFromStream&) = default;
		virtual SearchTermsBuilderFromStream& operator= (SearchTermsBuilderFromStream&&) = default;
	};
}

