#include "SearchItem.h"

#include <string>

using namespace StreamSearch;
using namespace std;

SearchItem::SearchItem(const string& searchTerm):
	searchTerm (searchTerm),
	currentIndex (0)
{
}

const string& SearchItem::GetSearchTerm() const
{
	return this->searchTerm;
}

bool SearchItem::IsFoundAfterCheckCharacter(const char c)
{
	if (this->searchTerm[this->currentIndex] == c)
	{
		++this->currentIndex;

		return this->currentIndex + 1 >= this->searchTerm.length();
	}
	else
	{
		this->currentIndex = 0;

		return false;
	}
}