#include <iostream>

#include "ArgumentProcessor.h"

using namespace std;
using namespace InputDataHandling;

int wmain(int argc, wchar_t* argv[])
{
    try
    {
        InputData inputData = ArgumentProcessor::InterpretArguments(argc, argv);

        wcout << inputData.dictionaryFile << endl;
        for (const wstring& dataFile : inputData.dataFiles)
        {
            wcout << dataFile << " ";
        }
        wcout << endl;
    }
    catch (exception ex)
    {
        wcerr << "Error: " << ex.what() << endl;
        return 1;
    }
    catch (...)
    {
        wcerr << "Error: Unexpected eception encountered." << endl;
        return 2;
    }

    return 0;
}
