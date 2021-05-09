#include "SearchNode.h"

using namespace StreamSearch;
using namespace std;

#include <algorithm>
#include <climits>
#include <iterator>

SearchNode::SearchNode(const char character, weak_ptr<SearchNode> parent) :
	character (character),
	parent(parent),
	children(),
	isSearchTermTerminator(false)
{
}

shared_ptr<SearchNode> SearchNode::AddChildNode(const char c)
{
	if (this->children.empty())
	{
		this->children.resize(UCHAR_MAX);
		fill(begin(this->children), end(this->children), nullptr);
	}

	this->children[static_cast<unsigned char>(c)] = make_shared<SearchNode>(c, shared_from_this());

	return this->children[static_cast<unsigned char>(c)];
}

bool SearchNode::IsLeaf() const
{
	return this->children.empty();
}

shared_ptr<SearchNode> SearchNode::GetChild(const char c) const
{
	return this->children.empty() ? nullptr : this->children.at(static_cast<unsigned char>(c));
}

bool SearchNode::IsSearchTermTerminator() const
{
	return this->isSearchTermTerminator;
}

const string SearchNode::GetSearchTerm() const
{
	return this->parent.expired() ? "" : this->parent.lock()->GetSearchTerm() + this->character;
}

void SearchNode::AddSearchTerm(const string& searchTerm, string::size_type searchTermCharIndex)
{
	if (searchTermCharIndex < searchTerm.length())
	{
		const char c = searchTerm[searchTermCharIndex];
		shared_ptr<SearchNode> childNode = GetChild(c);
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

void SearchNode::RemoveFromParent()
{
	if (!this->parent.expired())
	{
		shared_ptr<SearchNode> parentPtr = this->parent.lock();
		parentPtr->children[static_cast<unsigned char>(this->character)] = nullptr;
		if (all_of(begin(parentPtr->children), end(parentPtr->children), [](const auto& childNodePtr) { return !childNodePtr; }))
		{
			parentPtr->RemoveFromParent();
		}
		this->parent.reset();
	}
}

shared_ptr<SearchNode> SearchNode::operator[] (const char c) const
{
	return GetChild(c);
}