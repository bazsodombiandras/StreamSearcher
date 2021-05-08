#pragma once

#include <string>

using namespace std;

namespace SearchTermsHandling
{
	class ISearchTermsRegistry
	{
	public:
		virtual size_t GetCount() const = 0;

		virtual void Clear() = 0;
		virtual void Add(string searchTerm) = 0;

		virtual const string& operator[] (size_t idx) const = 0;
	};
}

