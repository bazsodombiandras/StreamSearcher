#include "VectorBasedSearchTermsRegistry.h"

using namespace SearchTerms;
using namespace std;

VectorBasedSearchTermsRegistry::VectorBasedSearchTermsRegistry(const ISearchTermsRegistry& other)
{
	*this = other;
}

size_t VectorBasedSearchTermsRegistry::GetCount() const
{
	return this->searchTerms.size();
}

void VectorBasedSearchTermsRegistry::Clear()
{
	this->searchTerms.clear();
}

void VectorBasedSearchTermsRegistry::Add(string searchTerm)
{
	// We want to guarantee uniqueness because there's no point in keeping the same search term twice.
	// Executing a find on the vector for every add is slightly expensive, but the goal is to optimize for fast access
	// after the search term registry is completely built up and therefore vector is the best choice.
	if (find(begin(this->searchTerms), end(this->searchTerms), searchTerm) == this->searchTerms.end())
	{
		this->searchTerms.push_back(searchTerm);
	}
}

void VectorBasedSearchTermsRegistry::Remove(size_t idx)
{
	this->searchTerms.erase(begin(this->searchTerms) + idx);
}

VectorBasedSearchTermsRegistry& VectorBasedSearchTermsRegistry::operator= (const ISearchTermsRegistry& other)
{
	ISearchTermsRegistry::CopyFrom(other);

	return *this;
}

const string& VectorBasedSearchTermsRegistry::operator[] (size_t idx) const
{
	return this->searchTerms[idx];
}