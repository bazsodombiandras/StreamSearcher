#pragma once

#include "ISearchTermsRegistry.h"

#include <string>
#include <vector>

using namespace std;

namespace SearchTerms
{
	class VectorBasedSearchTermsRegistry : public ISearchTermsRegistry
	{
	private:
		vector<string> searchTerms;

	public:
		VectorBasedSearchTermsRegistry() = default;
		VectorBasedSearchTermsRegistry(const ISearchTermsRegistry& other);
		VectorBasedSearchTermsRegistry(const VectorBasedSearchTermsRegistry& other) = default;
		VectorBasedSearchTermsRegistry(VectorBasedSearchTermsRegistry&& other) = default;
		virtual ~VectorBasedSearchTermsRegistry() = default;

		virtual size_t GetCount() const;

		virtual void Clear();
		virtual void Add(string searchTerm);
		virtual void Remove(size_t idx);

		VectorBasedSearchTermsRegistry& operator= (const ISearchTermsRegistry& other);
		VectorBasedSearchTermsRegistry& operator= (const VectorBasedSearchTermsRegistry& other) = default;
		VectorBasedSearchTermsRegistry& operator= (VectorBasedSearchTermsRegistry&& other) = default;
		
		virtual const string& operator[] (size_t idx) const;
	};
}

