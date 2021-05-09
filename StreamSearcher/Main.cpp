#include "ArgumentProcessor.h"
#include "SearchTermsBuilderFromStream.h"
#include "StreamSearcher.h"

#include <chrono>
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

        set<string> searchTerms;
        ifstream inputDataFileStream(inputData.searchTermsFile);
        SearchTermsBuilderFromStream searchTermsRegistryBuilder(inputDataFileStream);
        searchTermsRegistryBuilder.Build(searchTerms);

        cout << "Search terms:" << endl;
        copy(begin(searchTerms), end(searchTerms), ostream_iterator<string>(cout, "\n"));
        cout << endl;

        cout << "------------------------------" << endl << endl;
        cout << "Searching for terms in data files..." << endl << endl;

        StreamSearcher streamSearcher(searchTerms);

        for (string inputDataFile : inputData.dataFiles)
        {
            ifstream inputDataStream(inputDataFile);
            streamSearcher.SearchStream(inputDataStream);
            set<string> foundSearchTerms = streamSearcher.GetResults();
            if (!foundSearchTerms.empty())
            {
                cout << filesystem::path(inputDataFile).filename().string() << ": " << endl;
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
