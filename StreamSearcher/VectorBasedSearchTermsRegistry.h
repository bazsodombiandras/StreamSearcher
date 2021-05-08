#pragma once

#include "ISearchTermsRegistry.h"

#include <string>
#include <vector>

using namespace std;

class VectorBasedSearchTermsRegistry: public ISearchTermsRegistry
{
private:
	vector<string> searchTerms;

public:
	size_t GetCount() const;

	void Clear();
	void Add(string searchTerm);

	const string& operator[] (size_t idx) const;
};

