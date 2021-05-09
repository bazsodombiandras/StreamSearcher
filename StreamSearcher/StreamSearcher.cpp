#include "StreamSearcher.h"
#include "SearchNode.h"

#include<algorithm>

using namespace StreamSearch;
using namespace std;

StreamSearcher::StreamSearcher(const set<string>& searchTerms) :
	searchTerms(searchTerms),
	results()
{
}

const vector<string>& StreamSearcher::GetResults() const
{
	return this->results;
}

void StreamSearcher::SearchStream(istream& inputStream)
{
	this->results.clear();

	SearchNode rootNode;
	for_each(begin(this->searchTerms), end(this->searchTerms), [&rootNode](const string& searchTerm) { rootNode.AddSearchTerm(searchTerm, 0); });

	vector<SearchNode*> activeSearchNodes;

	for_each(
		istreambuf_iterator<char>(inputStream),
		istreambuf_iterator<char>(),
		[this, &rootNode, &activeSearchNodes](const char c)
		{
			activeSearchNodes.push_back(&rootNode);

			transform(
				begin(activeSearchNodes),
				end(activeSearchNodes),
				begin(activeSearchNodes),
				[c](const SearchNode* activeSearchNode)
				{
					return (*activeSearchNode)[c];
				}
			);

			activeSearchNodes.erase(
				remove_if(
					begin(activeSearchNodes),
					end(activeSearchNodes),
					[this](SearchNode* activeSearchNode)
					{
						if (activeSearchNode != nullptr)
						{
							if (activeSearchNode->IsLeaf())
							{
								this->results.push_back(activeSearchNode->GetSearchTerm());
								activeSearchNode->RemoveFromParent();

								return true;
							}
						}
						else
						{
							return true;
						}

						return false;
					}
				),
				end(activeSearchNodes)
			);
		}
	);
}
