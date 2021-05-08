#pragma once

#include "ISearchTermsRegistry.h"

class ISearchTermsRegistryBuilder
{
public:
	virtual void Build(ISearchTermsRegistry& searchTermsRegistry) const = 0;
};