#pragma once

#include <chrono>

using namespace std;

namespace Utils
{
	class Timer
	{
	private:
		chrono::system_clock::time_point startTime;

	public:
		Timer();
		~Timer();

		void DisplayElapsedTime() const;
		void Reset();
	};
}

