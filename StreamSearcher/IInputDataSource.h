#pragma once

#include "NamedStream.h"

#include <string>

using namespace std;

namespace InputDataHandling
{
	class IInputDataSource
	{
	public:
		virtual bool IsInputDataAvailable() const = 0;
		virtual NamedInputStream GetNextInputStream() = 0;

		virtual operator bool() { return this->IsInputDataAvailable(); }
	};
}