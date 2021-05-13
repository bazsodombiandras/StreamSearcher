#pragma once

#include<set>
#include<string>

using namespace std;

namespace SearchTermsHandling
{
	class ISearchTermsBuilder
	{
	public:
		virtual set<string> Build() = 0;
	};
}