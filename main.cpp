#include <iostream>

#include "utils/Utils.h"
#include "json/JsonParser.h"

using namespace std;

int main()
{
    string binaryOutputPath;
    cout << "Hello and welcome to json-packer! Where should the binary output be dumped to? Enter full path (filename included): ";
    getline(cin, binaryOutputPath);
    if (binaryOutputPath.empty()) {
        cout << "WARNING! TLV binary won't be exported (no path given)" << endl;
    }

    string jsonPath;
    cout << "There's a sample JSON tests/sample.json which can be used for this application.\nIf you wish to use your custom JSON, please enter the full path to it: ";
    getline(cin, jsonPath);
    if (jsonPath.empty() || !fileExists(jsonPath)) {
        jsonPath = "tests/sample.json";
    }

    JsonParser jp(binaryOutputPath, jsonPath);

    return 0;
}
