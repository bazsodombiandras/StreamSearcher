#include "Logger.h"
#include "../Utils/DateTime.h"

#include <assert.h>
#include <sstream>

using namespace Logging;
using namespace Utils;

Logger* Logger::instance = nullptr;

string Logger::MessageTypeToString(MsgType messageType)
{
	switch (messageType)
	{
		case MsgType::Error: return "ERR";
		case MsgType::Warning: return "WRN";
		case MsgType::Info: return "INF";
		case MsgType::Debug: return "DBG";
		default: return "";
	}
}

Logger::Logger(MsgType logLevel, bool includeTimestamp, bool includeMessageType):
	logLevel(logLevel),
	includeTimestamp(includeTimestamp),
	includeMessageType(includeMessageType)
{
}

void Logger::Message(const string& message, MsgType messageType)
{
	if (instance != nullptr)
	{
		if (messageType <= instance->logLevel)
		{
			stringstream msgStream;

			if (instance->includeTimestamp)
			{
				msgStream << "[" << DateTime::GetCurrentAsString() << "] ";
			}

			if (instance->includeMessageType)
			{
				msgStream << "[" << MessageTypeToString(messageType) << "] ";
			}

			msgStream << message << endl;

			instance->LogMessage(msgStream.str());
		}
	}
}

void Logger::Error(const string& message)
{
	Message(message, MsgType::Error);
}

void Logger::Warning(const string& message)
{
	Message(message, MsgType::Warning);
}

void Logger::Info(const string& message)
{
	Message(message, MsgType::Info);
}

void Logger::Debug(const string& message)
{
	Message(message, MsgType::Debug);
}