#pragma once

#include <ctime>
#include <string>

using namespace std;

namespace Utils
{
	/// <summary>
	/// Utilities related to date and time.
	/// </summary>
	class DateTime
	{
	public:
		/// <summary>
		/// Gets the current date and time as a string formatted according to a given pattern.
		/// </summary>
		/// <param name="format">The format pattern.</param>
		/// <returns>the current date and time formatted according to the specified pattern.</returns>
		static string GetCurrentAsString(string format = "%d-%m-%Y %H:%M:%S")
		{
			time_t rawTime;
			struct tm timeInfo;

			time(&rawTime);
			localtime_s(&timeInfo, &rawTime);

			char buf[80];
			strftime(buf, sizeof(buf), format.c_str(), &timeInfo);

			return std::string(buf);
		}
	};
}
