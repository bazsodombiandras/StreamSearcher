#pragma once

#include "InputArguments.h"

using namespace std;

namespace InputArgumentsHandling
{
	class ArgumentProcessor
	{
	private:
		static void DisplayUsage(const string& appName);

	public:
		static InputArguments InterpretArguments(int argc, char* argv[]);
	};
}