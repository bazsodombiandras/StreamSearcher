#pragma once

#include "NamedStream.h"

#include <string>

using namespace std;

namespace InputDataHandling
{
	/// <summary>
	/// The common interface that all input data sources must satisfy.
	/// </summary>
	class IInputDataSource
	{
	public:
		/// <summary>
		/// Default destructor (nothing special to destroy).
		/// </summary>
		virtual ~IInputDataSource() = default;

		/// <summary>
		/// Checks whether input data is currently available in the input data source (or the input data source is empty).
		/// The actual implementation is delegated to the descendant classes.
		/// </summary>
		/// <returns>True if the input data source currently has available data.</returns>
		virtual bool IsInputDataAvailable() const = 0;

		/// <summary>
		/// Gets the current input stream and advances the input data source to the next input stream.
		/// The actual implementation is delegated to the descendant classes.
		/// </summary>
		/// <returns>the current input stream.</returns>
		virtual NamedInputStream GetCurrentInputStreamAndMoveNext() = 0;

		/// <summary>
		/// Checks whether input data is currently available in the input data source (or the input data source is empty).
		/// </summary>
		virtual operator bool() { return this->IsInputDataAvailable(); }
	};
}