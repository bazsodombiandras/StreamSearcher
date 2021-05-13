#pragma once

#include <chrono>

using namespace std;

namespace Utils
{
	/// <summary>
	/// Utility class which encapsulates a timer.
	/// The timer is started when the instance is initialized and stopped and logged when the instance is destroyed.
	/// It is also possible to start/stop the timer manually.
	/// </summary>
	class Timer
	{
	private:
		/// <summary>
		/// The starting time point.
		/// </summary>
		chrono::system_clock::time_point startTime;

		/// <summary>
		/// The timer should not be copy constructed.
		/// </summary>
		/// <param name="">The other instance to copy from.</param>
		Timer(const Timer&) = delete;

		/// <summary>
		/// The timer should not be copied.
		/// </summary>
		/// <param name="">The other instance to copy from.</param>
		/// <returns>The instance into which the data has been copied.</returns>
		Timer& operator= (const Timer&) = delete;

	public:
		/// <summary>
		/// The default constructor starts the timer.
		/// </summary>
		Timer();

		/// <summary>
		/// The move constructor allows moving the timer's data.
		/// </summary>
		/// <param name="">The other instance to move the data from.</param>
		Timer(Timer&&) = default;

		/// <summary>
		/// The destructor stops the timer and logs the elapsed time.
		/// </summary>
		~Timer();

		void DisplayElapsedTime() const;
		void Reset();

		/// <summary>
		/// The move assignment operator allows moving the timer's data.
		/// </summary>
		/// <param name="">The other instance to move the data from.</param>
		/// <returns>The instance into which the data has beenn moved.</returns>
		Timer& operator= (Timer&&) = default;
	};
}

