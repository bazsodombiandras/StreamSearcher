#pragma once

#include <string>

using namespace std;

namespace Logging
{
	class Logger
	{
	public:
		enum class MsgType
		{
			Error,
			Warning,
			Info,
			Debug
		};

	private:
		MsgType logLevel;
		bool includeTimestamp;
		bool includeMessageType;

		static string MessageTypeToString(MsgType messageType);

		Logger() = delete;
		Logger(const Logger&) = delete;
		Logger(Logger&&) = delete;

		Logger& operator= (const Logger&) = delete;
		Logger& operator= (Logger&&) = delete;

		virtual void LogMessage(const string& message) = 0;

	protected:
		static Logger* instance;

		Logger(MsgType logLevel, bool includeTimestamp = true, bool includeMessageType = true);

	public:
		virtual ~Logger() = default;

		static void Message(const string& message, MsgType messageType);
		static void Error(const string& message = "");
		static void Warning(const string& message = "");
		static void Info(const string& message = "");
		static void Debug(const string& message = "");
	};
}