#pragma once

#include "ISearchTermsRegistry.h"

namespace SearchTerms
{
	class ISearchTermsRegistryBuilder
	{
	public:
		virtual void Build(ISearchTermsRegistry& searchTerms) const = 0;
	};
}