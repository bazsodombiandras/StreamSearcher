#pragma once

#include <string>

using namespace std;

namespace StreamSearch
{
	class SearchItem
	{
	private:
		string searchTerm;
		string::size_type currentIndex;

	public:
		SearchItem(const string& searchTerm);
		SearchItem(const SearchItem& other) = default;
		SearchItem(SearchItem&& other) = default;
		~SearchItem() = default;

		const string& GetSearchTerm() const;

		bool IsFoundAfterCheckCharacter(const char c);

		SearchItem& operator= (const SearchItem& other) = default;
		SearchItem& operator= (SearchItem&& other) = default;
	};
}