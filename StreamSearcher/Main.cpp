#include "ArgumentProcessor.h"
#include "FileInputDataSource.h"
#include "ConsoleLogger.h"
#include "MockInputDataSource.h"
#include "SearchTermsBuilderFromMockData.h"
#include "SearchTermsBuilderFromStream.h"
#include "StreamSearcher.h"
#include "Timer.h"

using namespace InputArgumentsHandling;
using namespace Logging;
using namespace SearchTermsHandling;
using namespace StreamSearch;
using namespace Utils;
using namespace std;

#define MOCKDATA

int main(int argc, char* argv[])
{
    ConsoleLogger::Init(Logger::MsgType::Debug, true, true);

    try
    {
        InputArguments inputArgs = ArgumentProcessor::InterpretArguments(argc, argv);        

#if defined MOCKDATA
        SearchTermsBuilderFromMockData searchTermsRegistryBuilder;
        searchTermsRegistryBuilder << "apple" << "orange" << "bear";
#else
        ifstream inputDataFileStream(inputArgs.searchTermsFile);
        SearchTermsBuilderFromStream searchTermsRegistryBuilder(inputDataFileStream);
#endif

        set<string> searchTerms = searchTermsRegistryBuilder.Build();

        Logger::Debug("Search terms:");
        for_each(begin(searchTerms), end(searchTerms), [](const string& searchTerm) { Logger::Debug(searchTerm); });

#if defined MOCKDATA
        MockInputDataSource inputDataSource;
        inputDataSource << make_pair("MockData-1", "The pineapple is tasty. This burden is unbearable.");
#else
        FileInputDataSource inputDataSource(inputArgs.dataFiles);
#endif

        {
            Timer t;
            StreamSearcher streamSearcher(searchTerms);
            streamSearcher.SearchStream(inputDataSource);
        }
    }
    catch (exception ex)
    {
        Logger::Error(ex.what());
        return 1;
    }
    catch (...)
    {
        Logger::Error("Unexpected eception encountered.");
        return 2;
    }

    return 0;
}
