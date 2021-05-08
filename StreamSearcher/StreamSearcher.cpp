#include "StreamSearcher.h"
#include "VectorBasedSearchTermsRegistry.h"

#include<algorithm>

using namespace SearchTerms;
using namespace StreamSearch;
using namespace std;

vector<string> StreamSearcher::FindTermsInStream(const ISearchTermsRegistry& searchTerms, istream& inputStream)
{
	vector<string> results;

	vector<pair<string, size_t>> notFoundSearchTermsWithCurrentIndex;
	size_t searchTermIdx = 0;
	generate_n(back_inserter(notFoundSearchTermsWithCurrentIndex), searchTerms.GetCount(), [&searchTerms, &searchTermIdx]() { return make_pair(searchTerms[searchTermIdx++], 0); });

	const size_t readBufferLength = 4096;
	char readBuffer[readBufferLength];
	while (inputStream.read(readBuffer, readBufferLength).gcount() > 0)
	{
		streamsize charCount = inputStream.gcount();
		for (streamsize charIdx = 0; charIdx < charCount; ++charIdx)
		{
			char c = readBuffer[charIdx];
			for (auto itNotFoundSearchTermWithCurrentIndex = begin(notFoundSearchTermsWithCurrentIndex); itNotFoundSearchTermWithCurrentIndex != end(notFoundSearchTermsWithCurrentIndex);)
			{
				bool searchTermFound = false;

				auto& notFoundSearchTermWithCurrentIndex = *itNotFoundSearchTermWithCurrentIndex;
				if (notFoundSearchTermWithCurrentIndex.first[notFoundSearchTermWithCurrentIndex.second] == c)
				{
					++notFoundSearchTermWithCurrentIndex.second;
					if (notFoundSearchTermWithCurrentIndex.second >= notFoundSearchTermWithCurrentIndex.first.length())
					{
						searchTermFound = true;
					}
				}
				else
				{
					notFoundSearchTermWithCurrentIndex.second = 0;
				}

				if (searchTermFound)
				{
					results.push_back(notFoundSearchTermWithCurrentIndex.first);
					itNotFoundSearchTermWithCurrentIndex = notFoundSearchTermsWithCurrentIndex.erase(itNotFoundSearchTermWithCurrentIndex);
				}
				else
				{
					++itNotFoundSearchTermWithCurrentIndex;
				}
			}
		}
	}

	return results;
}
