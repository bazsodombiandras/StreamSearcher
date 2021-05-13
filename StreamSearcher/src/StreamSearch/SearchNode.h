#pragma once

#include <memory>
#include <string>
#include <vector>
#include <set>

using namespace std;

namespace StreamSearch
{
	/// <summary>
	/// Represents a search node used in the stream search algorithm.
	/// A search node basically represents a character which exists in one or more of the search terms.
	/// Every search term generates a chain of earch nodes linked into a parent-child relationship.
	/// The search nodes forma  search tree which is iterated by the earch algorithm on multiple branches in parallel
	/// (multiple search terms are looked for simultaneously).
	/// A search is successful (a result is generated) if a search node is a search term terminator (includes the case whenit's a leaf node).
	/// A search fails if the search algorithm cannot advance a current (active) search from a search node to one of its children
	/// based on the current charcter read from the input stream.
	/// </summary>
	class SearchNode
	{
	private:
		/// <summary>
		/// The character represented by this search node.
		/// </summary>
		char character;

		/// <summary>
		/// The parent search node.
		/// </summary>
		SearchNode* parent;

		/// <summary>
		/// Owned collection of child nodes.
		/// </summary>
		unique_ptr<SearchNode> children[UCHAR_MAX];

		/// <summary>
		/// Is this search node a search term terminator?
		/// We need to keep track of this because a search term may end at a search node even if the node is not leaf.
		// Example: "app" is matched but there is a not yet macthed search term "apple" on the same branch in the search tree.
		/// </summary>
		bool isSearchTermTerminator;

		bool isEmpty;

		/// <summary>
		/// Search node copying through the copy constructor is disabled.
		/// </summary>
		/// <param name="">The other insatnce from which to copy the data.</param>
		SearchNode(const SearchNode&) = delete;

		/// <summary>
		/// Search node copying through the copy assignment operator is disabled.
		/// </summary>
		/// <param name="">The other insatnce from which to copy the data.</param>
		/// <returns>The instance into which the data has been copied.</returns>
		SearchNode& operator= (const SearchNode&) = delete;

		/// <summary>
		/// Add a child node to this search node.
		/// </summary>
		/// <param name="c">The data (character) of the child node.</param>
		/// <returns>The created and added child node.</returns>
		SearchNode* AddChildNode(const char c);

	public:
		/// <summary>
		/// Constructs a search node based on its data (character) and its parent node.
		/// </summary>
		/// <param name="character">The data (character) of the search node.</param>
		/// <param name="parent">The parent search node.</param>
		SearchNode(const char character = 0, SearchNode* parent = nullptr);

		/// <summary>
		/// Allows moving the data of the search node through the default move constructor.
		/// </summary>
		/// <param name="">The insatnce from which the data is moved.</param>
		SearchNode(SearchNode&&) = default;

		/// <summary>
		/// Gets the toal number of child nodes in the sub-tree of this search node.
		/// </summary>
		/// <returns>The total number of child nodes in the sub-tree of this search node.</returns>
		size_t GetNodeCount() const;

		/// <summary>
		/// Gets whether this search node is a leaf node or not.
		/// </summary>
		/// <returns>True if this search node is a leaf node, otherwise false.</returns>
		bool IsLeaf() const;

		/// <summary>
		/// Gets the child node of this search node which corresponds to the given character or null if there si no such child node.
		/// </summary>
		/// <param name="c">The character to find the child node by.</param>
		/// <returns>The child node corresponding to the character or null if there si no such child node.</returns>
		SearchNode* GetChild(const char c) const;

		/// <summary>
		/// Gets whether this seacrh node is a search term terminator (a search term ends at this node in the tree).
		/// </summary>
		/// <returns>True if this search node is a search term terminator, otherwise false.</returns>
		bool IsSearchTermTerminator() const;

		/// <summary>
		/// Gets the search term that ends at this search node in the tree.
		/// </summary>
		/// <returns>The search term that ends at this search node in the tree.</returns>
		const string GetSearchTerm() const;

		/// <summary>
		/// Creates and adds possibly multiple child nodes to this serach node as required by the given search term.
		/// In other words it makes sure that the search tree has a branch corrweposning to the given search term.
		/// </summary>
		/// <param name="searchTerm">the search term.</param>
		/// <param name="searchTermCharIndex">The current character index of the search term.</param>
		void AddSearchTerm(const string& searchTerm, string::size_type searchTermCharIndex);

		/// <summary>
		/// Reoves the branch of the search tree which ends at this search node and which has no other sub-branches.
		/// In other words it removes all the search nodes upwards from this search node which have no other child nodes.
		/// This is used to optimize the search by pruning branches of the search tree which have already genearted results.
		/// </summary>
		/// <param name="erasedNodes">Output parameter: the removed search nodes.</param>
		void EraseBranch(set<SearchNode*>* erasedNodes);

		/// <summary>
		/// Allows moving the data of the search node through the default move assignment operator.
		/// </summary>
		/// <param name="">The instance from which to move the data.</param>
		/// <returns>The insatnce into which the data has been moved.</returns>
		SearchNode& operator= (SearchNode&&) = default;

		/// <summary>
		/// Convenient short alias for the GetChild() method.
		/// </summary>
		/// <param name="c">The character to find the child node by.</param>
		/// <returns>The child node corresponding to the character or null if there si no such child node.</returns>
		SearchNode* operator[] (const char c) const;
	};
}