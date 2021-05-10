#pragma once

#include <memory>
#include <string>
#include <vector>
#include <set>

using namespace std;

namespace StreamSearch
{
	class SearchNode
	{
	private:
		char character;
		SearchNode* parent;
		vector<unique_ptr<SearchNode>> children;
		bool isSearchTermTerminator;

		SearchNode(const SearchNode&) = delete;
		SearchNode& operator= (const SearchNode&) = delete;

		SearchNode* AddChildNode(const char c);

	public:
		SearchNode(const char character = 0, SearchNode* parent = nullptr);
		SearchNode(SearchNode&&) = default;

		size_t GetNodeCount() const;
		bool IsLeaf() const;
		SearchNode* GetChild(const char c) const;

		bool IsSearchTermTerminator() const;
		const string GetSearchTerm() const;
		void AddSearchTerm(const string& searchTerm, string::size_type searchTermCharIndex);

		void EraseBranch(set<SearchNode*>* erasedNodes);

		SearchNode& operator= (SearchNode&&) = default;
		SearchNode* operator[] (const char c) const;
	};
}