#pragma once

#include "InputArguments.h"

using namespace std;

namespace InputArgumentsHandling
{
	/// <summary>
	/// Utility class which handles interpreting the command line arguments and displaying usage instructions.
	/// </summary>
	class ArgumentProcessor
	{
	private:
		/// <summary>
		/// Displays usage instructions for the console application.
		/// </summary>
		/// <param name="appName">The name of the console application.</param>
		static void DisplayUsageInstructions(const string& appName);

	public:
		/// <summary>
		/// Interprets the arguments passed to the console application.
		/// </summary>
		/// <param name="argc">The number of passed arguments.</param>
		/// <param name="argv">The arguments passed to the console application.</param>
		/// <returns>The interpreted input arguments.</returns>
		/// <exception cref="invalid_argument">Thrown when the input arguments are invalid.</exception>
		static InputArguments InterpretArguments(int argc, char* argv[]);
	};
}