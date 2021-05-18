#include "../src/InputArgumentsHandling/ArgumentProcessor.h"
#include "../src/InputDataHandling/FileInputDataSource.h"
#include "../src/InputDataHandling/MockInputDataSource.h"
#include "../src/Logging/ConsoleLogger.h"
#include "../src/SearchTermsHandling/SearchTermsBuilderFromMockData.h"
#include "../src/SearchTermsHandling/SearchTermsBuilderFromStream.h"
#include "../src/StreamSearch/StreamSearcher.h"
#include "../src/Utils/Timer.h"

#include <fstream>
#include <set>
#include <sstream>
#include <string>

using namespace InputArgumentsHandling;
using namespace Logging;
using namespace SearchTermsHandling;
using namespace StreamSearch;
using namespace Utils;
using namespace std;

//#define MOCKDATA

int main(int argc, char* argv[])
{
    // Initialize the globally available static instance of the logger as a console logger.
    // This mans that everything will be logged to the console. In theory a file logger could be used too.
    ConsoleLogger::Init(Logger::MsgType::Debug, true, true);

    try
    {
        // Check and interpret the command line input arguments.
        InputArguments inputArgs = ArgumentProcessor::InterpretArguments(argc, argv);        

        // Build up a registry of search terms from some input data.
#if defined MOCKDATA
        SearchTermsBuilderFromMockData searchTermsRegistryBuilder;
        searchTermsRegistryBuilder << "apple" << "orange" << "bear";
#else
        ifstream inputDataFileStream(inputArgs.searchTermsFile);
        SearchTermsBuilderFromStream searchTermsRegistryBuilder(inputDataFileStream);
#endif
        set<string> searchTerms = searchTermsRegistryBuilder.Build();

        // Log the search terms.
        Logger::Debug("Search terms:");
        stringstream searchTermsListStream;
        copy(begin(searchTerms), end(searchTerms), ostream_iterator<string>(searchTermsListStream, " "));
        Logger::Debug(searchTermsListStream.str());

        // Initialize the input data source.
#if defined MOCKDATA
        MockInputDataSource inputDataSource;
        inputDataSource << make_pair("MockData-1", "The pineapple is tasty. This burden is unbearable.");
#else
        FileInputDataSource inputDataSource(inputArgs.dataFiles);
#endif

        // Search for the search terms in all the input data and measure and log the elapsed time.
        {
            Timer t;
            StreamSearcher streamSearcher(searchTerms);
            streamSearcher.SearchInputData(inputDataSource);
        }
    }
    catch (exception ex)
    {
        Logger::Error(ex.what());
        return 1;
    }
    catch (...)
    {
        Logger::Error("Unexpected exception encountered.");
        return 2;
    }

    return 0;
}
