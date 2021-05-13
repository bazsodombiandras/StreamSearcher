#include "Timer.h"

#include <iostream>

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
	std::cout << "Elapsed time: " << chrono::duration_cast<chrono::milliseconds>(endTime - this->startTime).count() / 1000.0 << " seconds." << endl;
}

void Timer::Reset()
{
	this->startTime = std::chrono::system_clock::now();
}