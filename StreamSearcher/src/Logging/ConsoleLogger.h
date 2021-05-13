#pragma once

#include "Logger.h"

#include <string>

using namespace std;

namespace Logging
{
	/// <summary>
	/// Specialized logger which logs to console.
	/// </summary>
	class ConsoleLogger: public Logger
	{
	private:
		/// <summary>
		/// The default constructor is disabled because the single globally accessible instance is initialized through a non-default constructor.
		/// </summary>
		ConsoleLogger() = delete;

		/// <summary>
		/// Constructs an instance of this class based on a maximum log level and options to include a time stamp and the message type into the output.
		/// </summary>
		/// <param name="logLevel">The maximum log level. Any message which has a level higher than this will be omitted.</param>
		/// <param name="includeTimestamp">Specifies whether a time stamp should be included into the log messages.</param>
		/// <param name="includeMessageType">Specifies whether the message type should be included into the log messages.</param>
		ConsoleLogger(MsgType logLevel, bool includeTimestamp = true, bool includeMessageType = true);

		/// <summary>
		/// The copy constructor is disabled because there's a single globally accessible instance.
		/// </summary>
		/// <param name="">The other instance to copy from.</param>
		ConsoleLogger(const ConsoleLogger& other) = delete;

		/// <summary>
		/// The move constructor is disabled because there s a single globally accessible instance.
		/// </summary>
		/// <param name="">The other instance to move from.</param>
		ConsoleLogger(ConsoleLogger&& other) = delete;

		/// <summary>
		/// Default destructor. Nothing special to destroy.
		/// </summary>
		virtual ~ConsoleLogger() = default;

		/// <summary>
		/// Logs a message to the output medium.
		/// </summary>
		/// <param name="message">The log message.</param>
		void LogMessage(const string& message) override;

		/// <summary>
		/// The copy assignment operator is disabled because there is a single globally accessible instance.
		/// </summary>
		/// <param name="">The other instance to copy from.</param>
		/// <returns>The instance into which the data has been copied.</returns>
		ConsoleLogger& operator= (const ConsoleLogger& other) = delete;

		/// <summary>
		/// The move assignment operator is disabled because there is a single globally accessible instance.
		/// </summary>
		/// <param name="">The other instance to move from.</param>
		/// <returns>The instance into which the data has been moved.</returns>
		ConsoleLogger& operator= (ConsoleLogger&& other) = delete;

	public:
		/// <summary>
		/// Initializes the single globally accessible static instance based on a maximum log level and options to include a time stamp and the message type into the output.
		/// </summary>
		/// <param name="logLevel">The maximum log level. Any message which has a level higher than this will be omitted.</param>
		/// <param name="includeTimestamp">Specifies whether a time stamp should be included into the log messages.</param>
		/// <param name="includeMessageType">Specifies whether the message type should be included into the log messages.</param>
		static void Init(MsgType logLevel = Logger::MsgType::Debug, bool includeTimestamp = true, bool includeMessageType = true);
	};
}

