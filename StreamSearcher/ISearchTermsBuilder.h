#pragma once

#include<set>
#include<string>

using namespace std;

namespace SearchTerms
{
	class ISearchTermsBuilder
	{
	public:
		virtual set<string> Build() = 0;
	};
}