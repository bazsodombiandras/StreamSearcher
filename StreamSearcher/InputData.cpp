#include "ArgumentProcessor.h"

using namespace InputDataHandling;

const std::string& InputData::getDictionaryFile() const
{
	return this->dictionaryFile;
}

const std::vector<std::string>& InputData::getStreamFiles() const
{
	return this->streamFiles;
}