#pragma once

#include "InputData.h"

using namespace std;

namespace InputDataHandling
{
	class ArgumentProcessor
	{
	private:
		static void DisplayUsage(const wstring& appName);

	public:
		static InputData InterpretArguments(int argc, wchar_t* argv[]);
	};
}