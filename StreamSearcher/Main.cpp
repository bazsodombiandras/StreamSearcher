#include "ArgumentProcessor.h"
#include "FileInputDataSource.h"
#include "MockInputDataSource.h"
#include "SearchTermsBuilderFromMockData.h"
#include "SearchTermsBuilderFromStream.h"
#include "StreamSearcher.h"
#include "Timer.h"

#include <fstream>
#include <iostream>

using namespace InputArgumentsHandling;
using namespace SearchTermsHandling;
using namespace StreamSearch;
using namespace Utils;
using namespace std;

#define MOCKDATA

int main(int argc, char* argv[])
{
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

        cout << "Search terms:" << endl;
        copy(begin(searchTerms), end(searchTerms), ostream_iterator<string>(cout, "\n"));
        cout << endl;

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
        cerr << "Error: " << ex.what() << endl;
        return 1;
    }
    catch (...)
    {
        cerr << "Error: Unexpected eception encountered." << endl;
        return 2;
    }

    return 0;
}
