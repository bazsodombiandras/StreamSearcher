#include "Timer.h"
#include "../Logging/Logger.h"

using namespace Logging;
using namespace Utils;

Timer::Timer()
{
	this->Reset();
}

Timer::~Timer()
{
	this->DisplayElapsedTime();
}

void Timer::DisplayElapsedTime() const
{
	auto endTime = chrono::system_clock::now();
	Logger::Debug("Elapsed time: " + to_string(chrono::duration_cast<chrono::milliseconds>(endTime - this->startTime).count() / 1000.0) + " seconds.");
}

void Timer::Reset()
{
	this->startTime = std::chrono::system_clock::now();
}