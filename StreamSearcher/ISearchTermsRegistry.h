#pragma once

#include <iterator>
#include <string>

using namespace std;

namespace SearchTerms
{
	class ISearchTermsRegistry
	{
	public:
		virtual size_t GetCount() const = 0;

		virtual void Clear() = 0;
		virtual void Add(string searchTerm) = 0;
		virtual void Remove(size_t idx) = 0;
		virtual void CopyFrom(const ISearchTermsRegistry& other);

		virtual const string& operator[] (size_t idx) const = 0;
	};
}

