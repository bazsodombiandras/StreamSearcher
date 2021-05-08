#include "ArgumentProcessor.h"
#include "SearchTermsRegistryBuilderFromFile.h"
#include "VectorBasedSearchTermsRegistry.h"

#include <iostream>

using namespace InputDataHandling;
using namespace SearchTermsHandling;
using namespace std;

int main(int argc, char* argv[])
{
    try
    {
        InputData inputData = ArgumentProcessor::InterpretArguments(argc, argv);

        cout << "Search terms file: " << inputData.searchTermsFile << endl;
        cout << "Data files:" << endl;
        for (const string& dataFile : inputData.dataFiles)
        {
            cout << "  " << dataFile << endl;
        }
        cout << endl;

        VectorBasedSearchTermsRegistry searchTermsRegistry;
        SearchTermsRegistryBuilderFromFile searchTermsRegistryBuilder(inputData.searchTermsFile);
        searchTermsRegistryBuilder.Build(searchTermsRegistry);

        cout << "Search terms:" << endl;
        for (size_t searchTermIdx = 0; searchTermIdx < searchTermsRegistry.GetCount(); ++searchTermIdx)
        {
            cout << searchTermsRegistry[searchTermIdx] << endl;
        }
        cout << endl;
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
