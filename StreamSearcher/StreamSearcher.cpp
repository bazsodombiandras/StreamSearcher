#include "StreamSearcher.h"
#include "SearchNode.h"

#include<algorithm>
#include <memory>

using namespace StreamSearch;
using namespace std;

StreamSearcher::StreamSearcher(const set<string>& searchTerms) :
	searchTerms(searchTerms),
	results()
{
}

const set<string>& StreamSearcher::GetResults() const
{
	return this->results;
}

void StreamSearcher::SearchStream(istream& inputStream)
{
	this->results.clear();

	shared_ptr<SearchNode> rootSearchNode = make_shared<SearchNode>();
	for_each(begin(this->searchTerms), end(this->searchTerms), [&rootSearchNode](const string& searchTerm) { rootSearchNode->AddSearchTerm(searchTerm, 0); });

	vector<shared_ptr<SearchNode>> activeSearchNodes;

	for_each(
		istreambuf_iterator<char>(inputStream),
		istreambuf_iterator<char>(),
		[this, &rootSearchNode, &activeSearchNodes](const char c)
		{
			activeSearchNodes.push_back(rootSearchNode);

			transform(
				begin(activeSearchNodes),
				end(activeSearchNodes),
				begin(activeSearchNodes),
				[c](const auto& activeSearchNodePtr)
				{
					return (*activeSearchNodePtr)[c];
				}
			);

			auto newEnd = remove_if(
				begin(activeSearchNodes),
				end(activeSearchNodes),
				[this](auto& activeSearchNodePtr)
				{
					if (activeSearchNodePtr != nullptr)
					{
						if (activeSearchNodePtr->IsSearchTermTerminator())
						{
							this->results.insert(activeSearchNodePtr->GetSearchTerm());

							if (activeSearchNodePtr->IsLeaf())
							{
								activeSearchNodePtr->RemoveFromParent();

								return true;
							}
						}
					}
					else
					{
						return true;
					}

					return false;
				}
			);

			activeSearchNodes.erase(newEnd,	end(activeSearchNodes));
		}
	);
}
