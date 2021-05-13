#pragma once

#include "Logger.h"

#include <string>

using namespace std;

namespace Logging
{
	class ConsoleLogger: public Logger
	{
	private:
		ConsoleLogger() = delete;
		ConsoleLogger(MsgType logLevel, bool includeTimestamp = true, bool includeMessageType = true);
		ConsoleLogger(const ConsoleLogger& other) = delete;
		ConsoleLogger(ConsoleLogger&& other) = delete;
		virtual ~ConsoleLogger() = default;

		void LogMessage(const string& message) override;

		ConsoleLogger& operator= (const ConsoleLogger& other) = delete;
		ConsoleLogger& operator= (ConsoleLogger&& other) = delete;

	public:
		static void Init(MsgType logLevel = Logger::MsgType::Debug, bool includeTimestamp = true, bool includeMessageType = true);
	};
}

