#pragma once

#include <string>

using namespace std;

namespace Logging
{
	/// <summary>
	/// The base class for all loggers. Implements generic logging functionality, but delegates the details of actual logging to descendant classes.
	/// Also provides the mechanisms to log through a single logger instance which can be statically accessed.
	/// </summary>
	class Logger
	{
	public:
		/// <summary>
		/// Enumerates possible log message types.
		/// </summary>
		enum class MsgType
		{
			/// <summary>
			/// Error message.
			/// </summary>
			Error,

			/// <summary>
			/// Warning message.
			/// </summary>
			Warning,

			/// <summary>
			/// Information message.
			/// </summary>
			Info,

			/// <summary>
			/// Debug message.
			/// </summary>
			Debug
		};

	private:
		/// <summary>
		/// The maximum log level. Any message which has a level higher than this will be ommitted.
		/// </summary>
		MsgType logLevel;

		/// <summary>
		/// Specifies whether a timestamp should be included into the log messages.
		/// </summary>
		bool includeTimestamp;

		/// <summary>
		/// Specifies whether the message type should be included into the log messages.
		/// </summary>
		bool includeMessageType;

		/// <summary>
		/// Converts a log message type to the corresponding string representation.
		/// </summary>
		/// <param name="messageType">The message type.</param>
		/// <returns>The string representation corresponding tot he message type.</returns>
		static string MessageTypeToString(MsgType messageType);

		/// <summary>
		/// The default constructor is disabled because the single instance is initialized through a non-default constructor.
		/// </summary>
		Logger() = delete;

		/// <summary>
		/// The copy constructor is disabled because there's a single globally accessible instance.
		/// </summary>
		/// <param name="">The other instance to copy from.</param>
		Logger(const Logger&) = delete;

		/// <summary>
		/// The move constructor is disabled becaue there s a single globally accessible instance.
		/// </summary>
		/// <param name="">The other instance to move from.</param>
		Logger(Logger&&) = delete;

		/// <summary>
		/// The copy assignment operator is disabled because there is a single globally accessible instance.
		/// </summary>
		/// <param name="">The other instance to copy from.</param>
		/// <returns>The insatnce into which the data has been copied.</returns>
		Logger& operator= (const Logger&) = delete;

		/// <summary>
		/// The move assignment operator is disabled because there is a single globally accessible instance.
		/// </summary>
		/// <param name="">The other instance to move from.</param>
		/// <returns>The insatnce into which the data has been moved.</returns>
		Logger& operator= (Logger&&) = delete;

		/// <summary>
		/// Does the actual logging. The implementation is delegated to the descendant classes which know how to log exactly to the actual type of output medium.
		/// </summary>
		/// <param name="message">The log message.</param>
		virtual void LogMessage(const string& message) = 0;

	protected:
		//The single static globally accessible instance.
		static Logger* instance;

		/// <summary>
		/// Constructs an instance of this class based on a maximum log level and options to include a time stamp and the message type into the output.
		/// </summary>
		/// <param name="logLevel">The maximum log level. Any message which has a level higher than this will be ommitted.</param>
		/// <param name="includeTimestamp">Specifies whether a timestamp should be included into the log messages.</param>
		/// <param name="includeMessageType">Specifies whether the message type should be included into the log messages.</param>
		Logger(MsgType logLevel, bool includeTimestamp = true, bool includeMessageType = true);

	public:
		/// <summary>
		/// Default destructor. Nothing special to destroy.
		/// </summary>
		virtual ~Logger() = default;

		/// <summary>
		/// Log a message of a given type.
		/// </summary>
		/// <param name="message">The log message.</param>
		/// <param name="messageType">The type of the log message.</param>
		static void Message(const string& message, MsgType messageType);

		/// <summary>
		/// Log an error message.
		/// </summary>
		/// <param name="message">The error message.</param>
		static void Error(const string& message = "");

		/// <summary>
		/// Log a warning message.
		/// </summary>
		/// <param name="message">The warning message.</param>
		static void Warning(const string& message = "");

		/// <summary>
		/// Log an information message.
		/// </summary>
		/// <param name="message">The information message.</param>
		static void Info(const string& message = "");

		/// <summary>
		/// Log a debug message.
		/// </summary>
		/// <param name="message">The debug message.</param>
		static void Debug(const string& message = "");
	};
}