#include "StreamSearcher.h"
#include "SearchItem.h"

#include<algorithm>

using namespace StreamSearch;
using namespace std;

vector<string> StreamSearcher::FindTermsInStream(const set<string>& searchTerms, istream& inputStream)
{
	vector<string> results;

	vector<SearchItem> searchItems;
	transform(begin(searchTerms), end(searchTerms), back_inserter(searchItems), [](const string& searchTerm) { return SearchItem(searchTerm); });

	const size_t readBufferLength = 4096;
	char readBuffer[readBufferLength];
	while (inputStream.read(readBuffer, readBufferLength).gcount() > 0)
	{
		streamsize charCount = inputStream.gcount();
		for (streamsize charIdx = 0; charIdx < charCount; ++charIdx)
		{
			char c = readBuffer[charIdx];
			for (auto itSearchItems = begin(searchItems); itSearchItems != end(searchItems);)
			{
				SearchItem& searchItem = *itSearchItems;
				if (searchItem.IsFoundAfterCheckCharacter(c))
				{
					results.push_back(searchItem.GetSearchTerm());
					itSearchItems = searchItems.erase(itSearchItems);
				}
				else
				{
					++itSearchItems;
				}
			}
		}
	}

	return results;
}
