#include "ConsoleLogger.h"

#include <assert.h>
#include <iostream>

using namespace Logging;

ConsoleLogger::ConsoleLogger(MsgType logLevel, bool includeTimestamp, bool includeMessageType):
	Logger(logLevel, includeTimestamp, includeMessageType)
{
}

void ConsoleLogger::LogMessage(const string& message)
{
	cout << message;
}

void ConsoleLogger::Init(MsgType logLevel, bool includeTimestamp, bool includeMessageType)
{
	assert(Logger::instance == nullptr);

	delete Logger::instance;
	Logger::instance = new ConsoleLogger(logLevel, includeTimestamp, includeMessageType);
}