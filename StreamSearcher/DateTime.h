#pragma once

#include <ctime>
#include <string>

using namespace std;

namespace Utils
{
	class DateTime
	{
	public:
		static string GetCurrent(string format = "%d-%m-%Y %H:%M:%S")
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
