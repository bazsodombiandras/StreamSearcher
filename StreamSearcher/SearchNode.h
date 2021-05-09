#pragma once

#include <memory>
#include <string>
#include <vector>

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

		SearchNode& AddChildNode(const char c);

	public:
		SearchNode(char character = 0, SearchNode* parent = nullptr);
		SearchNode(SearchNode&&) = default;

		bool IsLeaf() const;
		SearchNode* GetChild(const char c) const;

		bool IsSearchTermTerminator() const;
		const string GetSearchTerm() const;
		void AddSearchTerm(const string& searchTerm, string::size_type searchTermCharIndex);

		void RemoveFromParent();

		SearchNode& operator= (SearchNode&&) = default;
		SearchNode* operator[] (const char c) const;
	};
}