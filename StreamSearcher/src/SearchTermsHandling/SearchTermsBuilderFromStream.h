#pragma once

#include "ISearchTermsBuilder.h"
#include<set>


using namespace std;

namespace SearchTermsHandling
{
	/// <summary>
	/// Represents a search terms builder which builds the collection of search terms from an input stream.
	/// </summary>
	class SearchTermsBuilderFromStream: public ISearchTermsBuilder
	{
	private:
		/// <summary>
		/// The maximum length that is allowed for a search term.
		/// </summary>
		static const size_t MaxSearchTermLength;

		/// <summary>
		/// The input stream from which the search terms are read.
		/// </summary>
		istream& inputStream;

		/// <summary>
		/// The default constructor is disabled because the input stream is always need as parameter to the constructor.
		/// </summary>
		SearchTermsBuilderFromStream() = delete;		

	public:
		/// <summary>
		/// Constructs an instance of this class based on an input stream.
		/// </summary>
		/// <param name="inputStream">The input stream.</param>
		SearchTermsBuilderFromStream(istream& inputStream);

		/// <summary>
		/// Allows copying the data of the search terms builder through the default copy constructor.
		/// </summary>
		/// <param name="">The other instance from which the data is copied.</param>
		SearchTermsBuilderFromStream(const SearchTermsBuilderFromStream&) = default;

		/// <summary>
		/// Allows moving the data of the search terms builder through the default move constructor.
		/// </summary>
		/// <param name="">The other instance from which the data is moved.</param>
		SearchTermsBuilderFromStream(SearchTermsBuilderFromStream&&) = default;

		/// <summary>
		/// Default destructor. Nothing special to destroy.
		/// </summary>
		virtual ~SearchTermsBuilderFromStream() = default;

		/// <summary>
		/// Builds the collection of search terms.
		/// </summary>
		/// <returns>the collection of search terms.</returns>
		set<string> Build() override;

		/// <summary>
		/// Allows copying the data of the search terms builder through the default copy assignment operator.
		/// </summary>
		/// <param name="">The other instance from which the data is copied.</param>
		/// <returns>The instance into which the data has been copied.</returns>
		virtual SearchTermsBuilderFromStream& operator= (const SearchTermsBuilderFromStream&) = default;

		/// <summary>
		/// Allows copying the data of the search terms builder through the default move assignment operator.
		/// </summary>
		/// <param name="">The other instance from which the data is moved.</param>
		/// <returns>The instance into which the data has been moved.</returns>
		virtual SearchTermsBuilderFromStream& operator= (SearchTermsBuilderFromStream&&) = default;
	};
}

