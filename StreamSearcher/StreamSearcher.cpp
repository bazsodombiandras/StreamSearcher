#include "StreamSearcher.h"
#include "Logger.h"
#include "SearchNode.h"

#include <algorithm>
#include <sstream>
#include <memory>

using namespace InputDataHandling;
using namespace Logging;
using namespace StreamSearch;
using namespace std;

void StreamSearcher::SearchStream(istream& inputStream)
{
	this->results.clear();

	SearchNode rootSearchNode;
	for_each
	(
		begin(this->searchTerms),
		end(this->searchTerms),
		[&rootSearchNode](const string& searchTerm)
		{
			rootSearchNode.AddSearchTerm(searchTerm, 0);
		}
	);

	vector<SearchNode*> activeSearchNodes;

	for_each
	(
		istreambuf_iterator<char>(inputStream),
		istreambuf_iterator<char>(),
		[this, &rootSearchNode, &activeSearchNodes](const char c)
		{
			activeSearchNodes.push_back(&rootSearchNode);

			transform
			(
				begin(activeSearchNodes),
				end(activeSearchNodes),
				begin(activeSearchNodes),
				[c](const auto& activeSearchNodePtr)
				{
					return (*activeSearchNodePtr)[c];
				}
			);

			vector<SearchNode*> reachedLeafSearchNodes;

			activeSearchNodes.erase
			(
				remove_if
				(
					begin(activeSearchNodes),
					end(activeSearchNodes),
					[this, &reachedLeafSearchNodes](auto& activeSearchNodePtr)
					{
						if (activeSearchNodePtr != nullptr)
						{
							if (activeSearchNodePtr->IsSearchTermTerminator())
							{
								this->results.insert(activeSearchNodePtr->GetSearchTerm());

								if (activeSearchNodePtr->IsLeaf())
								{
									reachedLeafSearchNodes.push_back(activeSearchNodePtr);

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
				),
				end(activeSearchNodes)
						);

			set<SearchNode*> erasedSearchNodes;

			for_each
			(
				begin(reachedLeafSearchNodes),
				end(reachedLeafSearchNodes),
				[&erasedSearchNodes](auto& leafSearchNodePtr)
				{
					leafSearchNodePtr->EraseBranch(&erasedSearchNodes);
				}
			);

			activeSearchNodes.erase
			(
				remove_if
				(
					begin(activeSearchNodes),
					end(activeSearchNodes),
					[&erasedSearchNodes](auto& activeSearchNodePtr)
					{
						return erasedSearchNodes.find(activeSearchNodePtr) != erasedSearchNodes.end();
					}
				),
				end(activeSearchNodes)
						);
		}
	);
}

StreamSearcher::StreamSearcher(const set<string>& searchTerms):
	searchTerms(searchTerms),
	results()
{
}

const set<string>& StreamSearcher::GetResults() const
{
	return this->results;
}

void StreamSearcher::SearchStream(IInputDataSource& inputDataSource)
{
	Logger::Info("Searching for terms in input data streams...");

	while (inputDataSource)
	{
		NamedInputStream inputDataStream = inputDataSource.GetNextInputStream();
		this->SearchStream(*inputDataStream.stream);

		set<string> foundSearchTerms = this->GetResults();
		if (!foundSearchTerms.empty())
		{
			Logger::Info(inputDataStream.name + ": ");
			stringstream foundSearchTermsListStream;
			copy(begin(foundSearchTerms), end(foundSearchTerms), ostream_iterator<string>(foundSearchTermsListStream, " "));
			Logger::Info(foundSearchTermsListStream.str());
		}
	}
}