#pragma once

#include<set>
#include<string>

using namespace std;

namespace SearchTermsHandling
{
	/// <summary>
	/// The common interface that all search terms builders must satisfy.
	/// </summary>
	class ISearchTermsBuilder
	{
	public:
		/// <summary>
		/// Default destructor. Nothing special to destroy.
		/// </summary>
		virtual ~ISearchTermsBuilder() = default;

		/// <summary>
		/// Build the collection of search terms.
		/// The actual implementation is delegated to the descendant classes which have the data that allows building the collection of search terms.
		/// </summary>
		/// <returns>The collection of search terms.</returns>
		virtual set<string> Build() = 0;
	};
}