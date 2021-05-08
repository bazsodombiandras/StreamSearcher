#pragma once

#include<set>
#include<string>

using namespace std;

namespace SearchTerms
{
	class ISearchTermsBuilder
	{
	public:
		virtual void Build(set<string>& searchTerms) = 0;
	};
}