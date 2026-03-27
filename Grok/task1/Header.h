#ifndef HEADER_H
#define HEADER_H

#include <unordered_map>
#include <string>

class FTelegraph
{
private:
    std::unordered_map<wchar_t, std::string> MorseDictionary;

public:
    FTelegraph();
    std::string EncodeMessage(const std::wstring& Input);
};

#endif