#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <map>
#include <string>

#include "../tlv/Tlv.h"

class JsonParser
{
public:
    JsonParser(const std::string &, const std::string &);

private:
    bool isNumber(const std::string &);
    void parseJsonFile(const std::string &);
    void processJsonLine(const std::string &);
    void exportJsonToBinary(const std::string &);

    std::map< std::map<std::string, std::string>, Tlv *> mJsonMap;
};

#endif // JSONPARSER_H