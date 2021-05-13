#pragma once

#include "IInputDataSource.h"

#include <istream>
#include <set>

using namespace InputDataHandling;
using namespace std;

namespace StreamSearch
{
	class StreamSearcher
	{
	private:
		set<string> searchTerms;
		set<string> results;

		StreamSearcher() = delete;

		void SearchStream(istream& inputStream);

	public:
		static const size_t InputStreamBufferSize;

		StreamSearcher(const set<string>& searchTerms);

		StreamSearcher(const StreamSearcher&) = default;
		StreamSearcher(StreamSearcher&&) = default;

		const set<string>& GetResults() const;

		void SearchStream(IInputDataSource& inputDataSource);

		StreamSearcher& operator= (const StreamSearcher&) = default;
		StreamSearcher& operator= (StreamSearcher&&) = default;
	};
}

