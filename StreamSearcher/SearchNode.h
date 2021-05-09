#pragma once

#include <memory>
#include <string>
#include <vector>

using namespace std;

namespace StreamSearch
{
	class SearchNode : public std::enable_shared_from_this<SearchNode>
	{
	private:
		char character;
		weak_ptr<SearchNode> parent;
		vector<shared_ptr<SearchNode>> children;
		bool isSearchTermTerminator;

		SearchNode(const SearchNode&) = delete;
		SearchNode& operator= (const SearchNode&) = delete;

		shared_ptr<SearchNode> AddChildNode(const char c);

	public:
		SearchNode(const char character = 0, weak_ptr<SearchNode> parent = weak_ptr<SearchNode>());
		SearchNode(SearchNode&&) = default;

		bool IsLeaf() const;
		shared_ptr<SearchNode> GetChild(const char c) const;

		bool IsSearchTermTerminator() const;
		const string GetSearchTerm() const;
		void AddSearchTerm(const string& searchTerm, string::size_type searchTermCharIndex);

		void RemoveFromParent();

		SearchNode& operator= (SearchNode&&) = default;
		shared_ptr<SearchNode> operator[] (const char c) const;
	};
}