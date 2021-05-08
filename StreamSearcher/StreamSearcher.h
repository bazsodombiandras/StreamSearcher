#pragma once

#include <istream>
#include <set>
#include <vector>

using namespace std;

namespace StreamSearch
{
	class StreamSearcher
	{
	public:
		static vector<string> FindTermsInStream(const set<string>& searchTerms, istream& inputStream);
	};
}

