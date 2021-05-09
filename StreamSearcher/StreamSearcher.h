#pragma once

#include <istream>
#include <set>

using namespace std;

namespace StreamSearch
{
	class StreamSearcher
	{
	private:
		set<string> searchTerms;
		set<string> results;

		StreamSearcher() = delete;

	public:
		static const size_t InputStreamBufferSize;

		StreamSearcher(const set<string>& searchTerms);

		StreamSearcher(const StreamSearcher&) = default;
		StreamSearcher(StreamSearcher&&) = default;

		const set<string>& GetResults() const;

		void SearchStream(istream& inputStream);

		StreamSearcher& operator= (const StreamSearcher&) = default;
		StreamSearcher& operator= (StreamSearcher&&) = default;
	};
}

