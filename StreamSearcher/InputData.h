#pragma once

#include <string>
#include <vector>

using namespace std;

namespace InputDataHandling
{
	class InputData
	{
	public:
		wstring dictionaryFile;
		vector<wstring> dataFiles;
	};
}

