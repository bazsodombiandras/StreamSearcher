#pragma once

#include "ISearchTermsRegistry.h"

namespace SearchTermsHandling
{
	class ISearchTermsRegistryBuilder
	{
	public:
		virtual void Build(ISearchTermsRegistry& searchTermsRegistry) const = 0;
	};
}