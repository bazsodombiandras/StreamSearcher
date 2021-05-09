#include "SearchNode.h"

using namespace StreamSearch;
using namespace std;

#include <algorithm>
#include <climits>
#include <iterator>

SearchNode::SearchNode(char character, SearchNode* parent) :
	character (character),
	parent(parent),
	children(),
	isSearchTermTerminator(false)
{
}

SearchNode& SearchNode::AddChildNode(const char c)
{
	if (this->children.empty())
	{
		this->children.resize(UCHAR_MAX);
		fill(begin(this->children), end(this->children), nullptr);
	}

	this->children[static_cast<unsigned char>(c)] = make_unique<SearchNode>(c, this);

	return *this->children[static_cast<unsigned char>(c)];
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
	if (this->parent == nullptr)
	{
		return "";
	}
	else
	{
		return this->parent->GetSearchTerm() + this->character;
	}
}

void SearchNode::AddSearchTerm(const string& searchTerm, string::size_type searchTermCharIndex)
{
	if (searchTermCharIndex < searchTerm.length())
	{
		const char c = searchTerm[searchTermCharIndex];
		SearchNode* childNode = GetChild(c);
		if (childNode == nullptr)
		{
			childNode = &AddChildNode(c);
		}

		childNode->AddSearchTerm(searchTerm, searchTermCharIndex + 1);
	}
	else
	{
		this->isSearchTermTerminator = true;
	}
}

void SearchNode::RemoveFromParent()
{
	if (this->parent != nullptr)
	{
		SearchNode* parentNode = this->parent;
		parentNode->children[static_cast<unsigned char>(this->character)] = nullptr;
		if (all_of(begin(parentNode->children), end(parentNode->children), [](const unique_ptr<SearchNode>& childNodePtr) { return !childNodePtr; }))
		{
			parentNode->RemoveFromParent();
		}
	}
}

SearchNode* SearchNode::operator[] (const char c) const
{
	return GetChild(c);
}