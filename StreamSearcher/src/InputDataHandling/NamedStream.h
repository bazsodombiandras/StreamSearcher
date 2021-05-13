#pragma once

#include <memory>
#include <string>

using namespace std;

namespace InputDataHandling
{
	/// <summary>
	/// Represents a named input stream.
	/// </summary>
	class NamedInputStream
	{
	public:
		/// <summary>
		/// The name of the input stream.
		/// </summary>
		string name;

		/// <summary>
		/// Owned pointer to the input stream.
		/// </summary>
		unique_ptr<istream> stream;
	};
}
