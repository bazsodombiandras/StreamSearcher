#pragma once

#include <string>
#include <vector>

using namespace std;

namespace InputDataHandling
{
	class InputData
	{
	public:
		string searchTermsFile;
		vector<string> dataFiles;
	};
}

