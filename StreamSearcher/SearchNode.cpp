#include "SearchNode.h"

#include <algorithm>
#include <climits>
#include <iterator>
#include <numeric>

using namespace StreamSearch;
using namespace std;

SearchNode::SearchNode(const char character, SearchNode* parent) :
	character (character),
	parent(parent),
	children(),
	isSearchTermTerminator(false)
{
}

SearchNode* SearchNode::AddChildNode(const char c)
{
	if (this->children.empty())
	{
		this->children.resize(UCHAR_MAX);
		fill(begin(this->children), end(this->children), nullptr);
	}

	this->children[static_cast<unsigned char>(c)] = make_unique<SearchNode>(c, this);

	return this->children[static_cast<unsigned char>(c)].get();
}

size_t SearchNode::GetNodeCount() const
{
	return this->children.empty()
		? 1
		: accumulate
		(
			begin(this->children),
			end(this->children),
			static_cast<size_t>(1),
			[](size_t nodeCount, const auto& childNodePtr)
			{
				return nodeCount + (childNodePtr ? childNodePtr->GetNodeCount() : 0);
			}
		);
}

bool SearchNode::IsLeaf() const
{
	return this->children.empty();
}

SearchNode* SearchNode::GetChild(const char c) const
{
	return this->children.empty() ? nullptr : this->children.at(static_cast<unsigned char>(c)).get();
}

bool SearchNode::IsSearchTermTerminator() const
{
	return this->isSearchTermTerminator;
}

const string SearchNode::GetSearchTerm() const
{
	return this->parent == nullptr ? "" : this->parent->GetSearchTerm() + this->character;
}

void SearchNode::AddSearchTerm(const string& searchTerm, string::size_type searchTermCharIndex)
{
	if (searchTermCharIndex < searchTerm.length())
	{
		const char c = searchTerm[searchTermCharIndex];
		SearchNode* childNode = GetChild(c);
		if (childNode == nullptr)
		{
			childNode = AddChildNode(c);
		}

		childNode->AddSearchTerm(searchTerm, searchTermCharIndex + 1);
	}
	else
	{
		this->isSearchTermTerminator = true;
	}
}

void SearchNode::EraseBranch(set<SearchNode*>* erasedNodes)
{
	if (this->parent != nullptr)
	{
		SearchNode* parentPtr = this->parent;
		parentPtr->children[static_cast<unsigned char>(this->character)] = nullptr;
		if (all_of(begin(parentPtr->children), end(parentPtr->children), [](const auto& childNodePtr) { return !childNodePtr; }))
		{
			parentPtr->EraseBranch(erasedNodes);
		}

		if (erasedNodes != nullptr)
		{
			erasedNodes->insert(this);
		}
	}
}

SearchNode* SearchNode::operator[] (const char c) const
{
	return GetChild(c);
}