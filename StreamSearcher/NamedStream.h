#pragma once

#include <memory>
#include <string>

using namespace std;

namespace InputDataHandling
{
	class NamedInputStream
	{
	public:
		string name;
		unique_ptr<istream> stream;
	};
}
