#include "StreamSearcher.h"
#include "../Logging/Logger.h"
#include "SearchNode.h"

#include <algorithm>
#include <assert.h>
#include <sstream>
#include <memory>

using namespace InputDataHandling;
using namespace Logging;
using namespace StreamSearch;
using namespace std;

void StreamSearcher::SearchStream(istream& inputStream)
{
	// Clear the results because a new search is starting.
	this->results.clear();

	// Build the tree of search nodes starting with a root node and creating child nodes as necessary based on the search terms.
	// The characters in the search terms determine which search nodes will be created because the actual search is ietarting over
	// the characters read from the input stream and looking for them in the search tree constructed from the search terms.
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
	Logger::Debug("Search nodes in the tree: " + to_string(rootSearchNode.GetNodeCount()));

	// During the search we maintain a collection of active search node pointers.
	// These are actually pointers to nodes of the search tree which keep track of parallel running searches of the input stream characters
	// along the branches of the search tree.
	// Each input stream character starts a new search (and creates a new active search node pointer to keep track of it).
	// As long as next input characters are matched to child nodes in the search tree, the active search node pointer is advanced deper into the search tree.
	// There can be two outcomes which eliminates an active search node pointer:
	// 1. The next input character is not matched to a child node in the search tree but the active search node pointer has not reached a leaf node in the search tree.
	//    This means that not the entire search term was matched, so there is no result generated.
	// 2. When the next input charcter is macthed to a leaf node in the search tree it means that the complete search term was matched, so that search term is a result.
	vector<SearchNode*> activeSearchNodePtrs;

	// Iterate over the characters of the input stream...
	for_each
	(
		istreambuf_iterator<char>(inputStream),
		istreambuf_iterator<char>(),
		[this, &rootSearchNode, &activeSearchNodePtrs](const char c)
		{
			// For each input stream character create a new active search node pointer starting at the root of the search tree
			// because the root node is where all search term branches start in the tree.
			activeSearchNodePtrs.push_back(&rootSearchNode);

			// Advance all the active search node pointers deeper into the search tree.
			// If a given active earch node pointer cannot be advanced deeper because the current input stream character cannot be macthed,
			// then after this step that active searchnode pointer will be null.
			transform
			(
				begin(activeSearchNodePtrs),
				end(activeSearchNodePtrs),
				begin(activeSearchNodePtrs),
				[c](const auto& activeSearchNodePtr)
				{
					return (*activeSearchNodePtr)[c];
				}
			);

			// Gather all the active search node pointers which have reached a leaf in the search tree.
			// We collect them because we want to eliminate their branches from the search tree.
			// This results ina  smaller search tree every time a result is found and leads to more optimal performance.
			// In other words every time a search term is found, we eliminate the corresponding branch from the search tree
			// because if  it has been found there si no point in looking for it again.
			vector<SearchNode*> reachedLeafSearchNodes;

			// Get rid of all the active search nodes which have either become null because the current input stream chaarcter could not be matched (dead end)
			// or which have reached a leaf node in the serach tree, meaning that they cannot advance any deeper and they have produced a result.
			activeSearchNodePtrs.erase
			(
				remove_if
				(
					begin(activeSearchNodePtrs),
					end(activeSearchNodePtrs),
					[this, &reachedLeafSearchNodes](auto& activeSearchNodePtr)
					{
						if (activeSearchNodePtr != nullptr)
						{
							if (activeSearchNodePtr->IsSearchTermTerminator())
							{
								// A search term might have been completely found even if the corresponding active search node pointer has not yet reached a leaf node
								// Example: "app" is matched but there is a not yet macthed search term "apple" on the same branch in the search tree.
								this->results.insert(activeSearchNodePtr->GetSearchTerm());

								if (activeSearchNodePtr->IsLeaf())
								{
									// Collect the active search node pointers which have reached leaves in the search tree.
									reachedLeafSearchNodes.push_back(activeSearchNodePtr);

									// Eliminate the active search node pointers which have recahed leaves in the search tree.
									return true;
								}
							}
						}
						else
						{
							// Eliminate the active search node pointers which have become null (the dead ends).
							return true;
						}

						// Keep all the active search node pointers which have been macthed using the current input stream character and are still in the middle of the tree
						// (they represent searches in progress).
						return false;
					}
				),
				end(activeSearchNodePtrs)
			);

			// We eliminate from the search tree entire branches starting from reached leaf nodes and going upwards in the tree
			// as long as each parent node has no other children. This is for optimization reasons, we want to keep making the search tree smaller and smaller,
			// so that subsequent searches become faster and faster.
			// We collect all these eliminated nodes because we also need to get rid of the active search node pointers that point to them,
			// otherwise we could end up with active search node pointers pointing to destroyed data.
			set<SearchNode*> erasedSearchNodes;

			// Eliminate the search tree branches of reached leaf nodes (results have been geneartd from them, they are n longer needed).
			for_each
			(
				begin(reachedLeafSearchNodes),
				end(reachedLeafSearchNodes),
				[&erasedSearchNodes](auto& leafSearchNodePtr)
				{
					leafSearchNodePtr->EraseBranch(&erasedSearchNodes);
				}
			);

			// Get rid of the active search nodes which corrspond to eliminated search tree nodes, so that we don't end up with
			// active search node pointers that point to destroyed data.
			activeSearchNodePtrs.erase
			(
				remove_if
				(
					begin(activeSearchNodePtrs),
					end(activeSearchNodePtrs),
					[&erasedSearchNodes](auto& activeSearchNodePtr)
					{
						return erasedSearchNodes.find(activeSearchNodePtr) != erasedSearchNodes.end();
					}
				),
				end(activeSearchNodePtrs)
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

void StreamSearcher::SearchInputData(IInputDataSource& inputDataSource)
{
	Logger::Info("Searching for terms in input data streams...");

	// Do a search for each of the input data streams
	while (inputDataSource)
	{
		NamedInputStream inputDataStream = inputDataSource.GetCurrentInputStreamAndMoveNext();

		assert(inputDataStream.stream != nullptr);
		this->SearchStream(*inputDataStream.stream);

		// Log the results of the current stream search.
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