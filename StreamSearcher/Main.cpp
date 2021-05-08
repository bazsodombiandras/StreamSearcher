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

        cout << "Search terms file: " << inputData.searchTermsFile << endl;
        cout << "Data files:" << endl;
        for (const string& dataFile : inputData.dataFiles)
        {
            cout << "  " << dataFile << endl;
        }
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

        for (string inputDataFile : inputData.dataFiles)
        {
            ifstream inputDataStream(inputDataFile);
            vector<string> foundSearchTerms = StreamSearcher::FindTermsInStream(searchTerms, inputDataStream);

            cout << std::filesystem::path(inputDataFile).filename().string() << ": ";
            for (auto itFoundSearchTerms = begin(foundSearchTerms); itFoundSearchTerms != end(foundSearchTerms); ++itFoundSearchTerms)
            {
                cout << *itFoundSearchTerms;
                if (itFoundSearchTerms < end(foundSearchTerms) - 1)
                {
                    cout << ", ";
                }
            }
            cout << endl << endl;
        }

        auto endTime = std::chrono::system_clock::now();
        auto elapsedTime = endTime - startTime;
        std::cout << "Elapsed time: " << chrono::duration_cast<chrono::milliseconds>(elapsedTime).count() << " ms." << endl;
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
