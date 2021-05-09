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

	for_each(
		istreambuf_iterator<char>(inputStream),
		istreambuf_iterator<char>(),
		[&searchItems, &results](char c)
		{
			remove_if(
				begin(searchItems),
				end(searchItems),
				[c, &results](SearchItem& searchItem)
				{
					if (searchItem.IsFoundAfterCheckCharacter(c))
					{
						results.insert(end(results), searchItem.GetSearchTerm());

						return true;
					}

					return false;
				}
			);
		}
	);

	return results;
}
