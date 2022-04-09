#include "JsonParser.h"
#include "../utils/Utils.h"

#include <fstream>
#include <sstream>

#include <string.h>
#include <arpa/inet.h>

#include <iostream>

JsonParser::JsonParser(const std::string &binaryOutPath, const std::string &jsonPath)
{
    parseJsonFile(jsonPath);
    exportJsonToBinary(binaryOutPath);
}

bool JsonParser::isNumber(const std::string &str)
{
    for (char const &c : str) {
        if (std::isdigit(c) == 0) {
            return false;
        }
    }

    return true;
}

void JsonParser::parseJsonFile(const std::string &jsonPath)
{
    if (!fileExists(jsonPath)) {
        std::cout << "ERROR: File does not exist!!!";
        return;
    }

    std::ifstream file(jsonPath);
    std::string line;
    int i = 0;

    while (std::getline(file, line)) {
        std::cout << "Line " << i << " read stream: " << line << std::endl;

        // Remove both {} symbols to parse the strings
        line = line.substr(1, line.length() - 2);
        std::istringstream lineStringStream(line);
        std::string jsonLine;

        while (getline(lineStringStream, jsonLine, ',')) {
            processJsonLine(jsonLine);
        }

        i++;
    }
}

void JsonParser::processJsonLine(const std::string &jsonLine)
{
    std::istringstream iss(jsonLine);
    std::string jsonElement;
    bool keyUsed = false;
    std::string key, value;
    while (getline(iss, jsonElement, ':')) {
        if (keyUsed) {
            value = jsonElement;
        } else {
            key = jsonElement;
            keyUsed = true;
        }
    }
    std::map<std::string, std::string> jsonPairMap;
    jsonPairMap[key] = value;
    if (isNumber(value)) {
        mJsonMap[jsonPairMap] = new Tlv(TlvType::Int, atoi(value.c_str()));
    } else if (value.compare("TRUE") == 0) {
        mJsonMap[jsonPairMap] = new Tlv(TlvType::Bool, true);
    } else if (value.compare("FALSE") == 0) {
        mJsonMap[jsonPairMap] = new Tlv(TlvType::Bool, false);
    } else {
        mJsonMap[jsonPairMap] = new Tlv(TlvType::String, value);
    }
}

void JsonParser::exportJsonToBinary(const std::string &binaryOutPath)
{
    if (binaryOutPath.empty() || mJsonMap.empty()) {
        return;
    }

    std::ofstream output(binaryOutPath, std::ios::out|std::ios::binary);
    // Output the TLV objects into a binary form
    for (auto const &dict : mJsonMap) {
        auto tlv = dict.second;
        int offset = 0;
        unsigned char *tlvValue = new unsigned char[sizeof(int) * 2 + tlv->GetLength()];
        int type = htonl(tlv->GetType());
        memcpy(tlvValue+offset, &type, sizeof(int));
        offset += sizeof(int);
        int length = tlv->GetLength();
        int nwlength = htonl(length);
        memcpy(tlvValue+offset, &nwlength, sizeof(int));
        offset += sizeof(int);
        memcpy(tlvValue+offset, tlv->GetValue(), length);
        offset += length;

        // Output to file after TLV encoding
        for (int c = 0; c < offset; c++) {
            output.write((char *) &tlvValue[c], offset);
        }
    }
}
