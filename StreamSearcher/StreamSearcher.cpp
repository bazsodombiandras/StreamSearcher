#include "StreamSearcher.h"
#include "SearchItem.h"

#include<algorithm>

using namespace StreamSearch;
using namespace std;

const size_t StreamSearcher::InputStreamBufferSize = 4096;

vector<string> StreamSearcher::FindTermsInStream(const set<string>& searchTerms, istream& inputStream)
{
	vector<string> results;

	vector<SearchItem> searchItems;
	transform(begin(searchTerms), end(searchTerms), back_inserter(searchItems), [](const string& searchTerm) { return SearchItem(searchTerm); });

	char inputStreamBuffer[InputStreamBufferSize];
	streamsize readCharCount = 0;
	while ((readCharCount = inputStream.read(inputStreamBuffer, InputStreamBufferSize).gcount()) > 0)
	{
		for (streamsize charIdx = 0; charIdx < readCharCount; ++charIdx)
		{
			char c = inputStreamBuffer[charIdx];
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
