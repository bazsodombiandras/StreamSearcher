#include "ISearchTermsRegistry.h"

using namespace SearchTerms;

 void ISearchTermsRegistry::CopyFrom (const ISearchTermsRegistry& other)
{
	if (this != &other)
	{
		this->Clear();
		for (size_t idx = 0; idx < other.GetCount(); ++idx)
		{
			this->Add(other[idx]);
		}
	}
}