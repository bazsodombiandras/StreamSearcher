#include "ArgumentProcessor.h"
#include "SearchTermsRegistryBuilderFromFile.h"
#include "StreamSearcher.h"
#include "VectorBasedSearchTermsRegistry.h"

#include <filesystem>
#include <fstream>
#include <iostream>

using namespace InputDataHandling;
using namespace SearchTerms;
using namespace StreamSearch;
using namespace std;

int main(int argc, char* argv[])
{
    try
    {
        auto startTime = std::chrono::system_clock::now();

        InputData inputData = ArgumentProcessor::InterpretArguments(argc, argv);

        cout << "Search terms file: " << endl << inputData.searchTermsFile << endl << endl;
        cout << "Data files: " << endl;
        copy(begin(inputData.dataFiles), end(inputData.dataFiles), ostream_iterator<string>(cout, "\n"));
        cout << endl;

        VectorBasedSearchTermsRegistry searchTerms;
        SearchTermsRegistryBuilderFromFile searchTermsRegistryBuilder(inputData.searchTermsFile);
        searchTermsRegistryBuilder.Build(searchTerms);

        cout << "Search terms:" << endl;
        for (size_t searchTermIdx = 0; searchTermIdx < searchTerms.GetCount(); ++searchTermIdx)
        {
            cout << searchTerms[searchTermIdx] << endl;
        }
        cout << endl;

        cout << "------------------------------" << endl << endl << "Found search terms in data files:" << endl << endl;
        for (string inputDataFile : inputData.dataFiles)
        {
            ifstream inputDataStream(inputDataFile);
            vector<string> foundSearchTerms = StreamSearcher::FindTermsInStream(searchTerms, inputDataStream);
            if (!foundSearchTerms.empty())
            {
                cout << std::filesystem::path(inputDataFile).filename().string() << ": " << endl;
                copy(begin(foundSearchTerms), end(foundSearchTerms), ostream_iterator<string>(cout, "\n"));
                cout << endl;
            }
        }

        auto endTime = std::chrono::system_clock::now();
        auto elapsedTime = endTime - startTime;
        std::cout << "Elapsed time: " << chrono::duration_cast<chrono::milliseconds>(elapsedTime).count() / 1000.0 << " seconds." << endl;
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
