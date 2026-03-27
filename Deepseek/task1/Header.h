#pragma once

#include <unordered_map>
#include <string>

class FTelegraph
{
public:
    FTelegraph();
    std::string EncodeMessage(const std::string& Input) const;

private:
    // Ключ — Unicode кодовая точка (например, 0x0410 для 'А')
    std::unordered_map<int, std::string> MorseMap;
    std::string EncodeWord(const std::string& Word) const;
    static std::vector<int> GetUnicodePoints(const std::string& Utf8Str);
};