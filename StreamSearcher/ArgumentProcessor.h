#pragma once

#include "InputData.h"

using namespace std;

namespace InputDataHandling
{
	class ArgumentProcessor
	{
	private:
		static void DisplayUsage(const string& appName);

	public:
		static InputData InterpretArguments(int argc, char* argv[]);
	};
}