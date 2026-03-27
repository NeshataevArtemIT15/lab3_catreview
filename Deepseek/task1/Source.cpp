#include "Header.h"
#include <vector>
#include <cstdint>

FTelegraph::FTelegraph()
{
    // Русские буквы в Unicode (заглавные)
    // А-Я: 0x0410-0x042F, Ё: 0x0401
    MorseMap = {
        { 0x0410, ".-" },    // А
        { 0x0411, "-..." },  // Б
        { 0x0412, ".--" },   // В
        { 0x0413, "--." },   // Г
        { 0x0414, "-.." },   // Д
        { 0x0415, "." },     // Е
        { 0x0401, "." },     // Ё
        { 0x0416, "...-" },  // Ж
        { 0x0417, "--.." },  // З
        { 0x0418, ".." },    // И
        { 0x0419, ".---" },  // Й
        { 0x041A, "-.-" },   // К
        { 0x041B, ".-.." },  // Л
        { 0x041C, "--" },    // М
        { 0x041D, "-." },    // Н
        { 0x041E, "---" },   // О
        { 0x041F, ".--." },  // П
        { 0x0420, ".-." },   // Р
        { 0x0421, "..." },   // С
        { 0x0422, "-" },     // Т
        { 0x0423, "..-" },   // У
        { 0x0424, "..-." },  // Ф
        { 0x0425, "...." },  // Х
        { 0x0426, "-.-." },  // Ц
        { 0x0427, "---." },  // Ч
        { 0x0428, "----" },  // Ш
        { 0x0429, "--.-" },  // Щ
        { 0x042A, "--.--" }, // Ъ
        { 0x042B, "-.--" },  // Ы
        { 0x042C, "-..-" },  // Ь
        { 0x042D, "..-.." }, // Э
        { 0x042E, "..--" },  // Ю
        { 0x042F, ".-.-" }   // Я
    };
}

std::vector<int> FTelegraph::GetUnicodePoints(const std::string& Utf8Str)
{
    std::vector<int> Points;
    size_t i = 0;
    while (i < Utf8Str.size())
    {
        unsigned char c = static_cast<unsigned char>(Utf8Str[i]);
        int codePoint = 0;
        size_t bytes = 0;

        if ((c & 0x80) == 0)  // 1-byte ASCII
        {
            codePoint = c;
            bytes = 1;
        }
        else if ((c & 0xE0) == 0xC0) // 2-byte
        {
            codePoint = c & 0x1F;
            bytes = 2;
        }
        else if ((c & 0xF0) == 0xE0) // 3-byte
        {
            codePoint = c & 0x0F;
            bytes = 3;
        }
        else if ((c & 0xF8) == 0xF0) // 4-byte
        {
            codePoint = c & 0x07;
            bytes = 4;
        }
        else
        {
            // Invalid UTF-8, skip
            Points.push_back('?');
            i++;
            continue;
        }

        for (size_t j = 1; j < bytes; ++j)
        {
            if (i + j >= Utf8Str.size()) break;
            unsigned char next = static_cast<unsigned char>(Utf8Str[i + j]);
            if ((next & 0xC0) != 0x80) break; // invalid continuation
            codePoint = (codePoint << 6) | (next & 0x3F);
        }
        Points.push_back(codePoint);
        i += bytes;
    }
    return Points;
}

std::string FTelegraph::EncodeWord(const std::string& Word) const
{
    std::vector<int> Points = GetUnicodePoints(Word);
    std::string Encoded;

    for (int Pt : Points)
    {
        // Приводим к верхнему регистру для русских букв
        int UpperPt = Pt;
        if (Pt >= 0x0430 && Pt <= 0x044F)      // строчные а-я
            UpperPt = Pt - 0x20;
        else if (Pt == 0x0451)                 // ё
            UpperPt = 0x0401;

        auto It = MorseMap.find(UpperPt);
        if (It != MorseMap.end())
        {
            if (!Encoded.empty())
                Encoded += ' ';
            Encoded += It->second;
        }
        else
        {
            if (!Encoded.empty())
                Encoded += ' ';
            Encoded += '?';
        }
    }
    return Encoded;
}

std::string FTelegraph::EncodeMessage(const std::string& Input) const
{
    std::vector<std::string> Words;
    std::string CurrentWord;

    for (char Ch : Input)
    {
        if (Ch == ' ')
        {
            if (!CurrentWord.empty())
            {
                Words.push_back(CurrentWord);
                CurrentWord.clear();
            }
        }
        else
        {
            CurrentWord += Ch;
        }
    }
    if (!CurrentWord.empty())
        Words.push_back(CurrentWord);

    std::string Result;
    for (size_t i = 0; i < Words.size(); ++i)
    {
        if (i > 0)
            Result += "  ";
        Result += EncodeWord(Words[i]);
    }
    return Result;
}