#pragma once

#include "ISearchTermsRegistry.h"

#include <istream>
#include <vector>

using namespace SearchTerms;
using namespace std;

namespace StreamSearch
{
	class StreamSearcher
	{
	public:
		static vector<string> FindTermsInStream(const ISearchTermsRegistry& searchTermsRegistry, istream& inputStream);
	};
}

