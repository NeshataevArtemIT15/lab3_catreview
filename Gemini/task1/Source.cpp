#include "Header.h"
#include <iostream>

FTelegraph::FTelegraph()
{
	InitializeAlphabet();
}

void FTelegraph::InitializeAlphabet()
{
	MorseAlphabet["А"] = ".-";    MorseAlphabet["Б"] = "-...";  MorseAlphabet["В"] = ".--";
	MorseAlphabet["Г"] = "--.";   MorseAlphabet["Д"] = "-..";   MorseAlphabet["Е"] = ".";
	MorseAlphabet["Ё"] = ".";     MorseAlphabet["Ж"] = "...-";  MorseAlphabet["З"] = "--..";
	MorseAlphabet["И"] = "..";    MorseAlphabet["Й"] = ".---";  MorseAlphabet["К"] = "-.-";
	MorseAlphabet["Л"] = ".-..";  MorseAlphabet["М"] = "--";    MorseAlphabet["Н"] = "-.";
	MorseAlphabet["О"] = "---";   MorseAlphabet["П"] = ".--.";  MorseAlphabet["Р"] = ".-.";
	MorseAlphabet["С"] = "...";   MorseAlphabet["Т"] = "-";     MorseAlphabet["У"] = "..-";
	MorseAlphabet["Ф"] = "..-.";  MorseAlphabet["Х"] = "....";  MorseAlphabet["Ц"] = "-.-.";
	MorseAlphabet["Ч"] = "---.";  MorseAlphabet["Ш"] = "----";  MorseAlphabet["Щ"] = "--.-";
	MorseAlphabet["Ъ"] = "--.--"; MorseAlphabet["Ы"] = "-.--";  MorseAlphabet["Ь"] = "-..-";
	MorseAlphabet["Э"] = "..-.."; MorseAlphabet["Ю"] = "..--";  MorseAlphabet["Я"] = ".-.-";
}

std::string FTelegraph::EncodeMessage(const std::string& InputText)
{
	std::string upperText = ToUpperCaseRussian(InputText);
	std::vector<std::string> characters = GetChars(upperText);
	std::string encodedResult = "";

	for (size_t i = 0; i < characters.size(); ++i)
	{
		const std::string& currentChar = characters[i];

		if (currentChar == " ")
		{
			encodedResult += "  "; // Двойной пробел между словами
			continue;
		}

		if (MorseAlphabet.count(currentChar))
		{
			encodedResult += MorseAlphabet[currentChar];
		}
		else if (currentChar != "\r" && currentChar != "\n")
		{
			encodedResult += "?"; // Если символ не найден
		}

		// Пробел между буквами внутри слова
		if (i + 1 < characters.size() && characters[i + 1] != " " && currentChar != " ")
		{
			encodedResult += " ";
		}
	}

	return encodedResult;
}

std::string FTelegraph::ToUpperCaseRussian(const std::string& InputText)
{
	std::string result = InputText;
	for (size_t i = 0; i < result.length(); ++i)
	{
		unsigned char c1 = static_cast<unsigned char>(result[i]);
		if (c1 == 0xD0 || c1 == 0xD1) // Префиксы UTF-8 для кириллицы
		{
			unsigned char c2 = static_cast<unsigned char>(result[i + 1]);
			// Если это маленькие буквы 'а'-'я' (D0 B0 - D1 8F)
			if (c1 == 0xD0 && c2 >= 0xB0 && c2 <= 0xBF)
			{
				result[i + 1] = c2 - 0x20;
			}
			else if (c1 == 0xD1 && c2 >= 0x80 && c2 <= 0x8F)
			{
				result[i] = 0xD0;
				result[i + 1] = c2 + 0x10;
			}
			// Отдельная обработка 'ё'
			else if (c1 == 0xD1 && c2 == 0x91)
			{
				result[i] = 0xD0;
				result[i + 1] = 0x81;
			}
			i++;
		}
	}
	return result;
}

std::vector<std::string> FTelegraph::GetChars(const std::string& InputText)
{
	std::vector<std::string> chars;
	for (size_t i = 0; i < InputText.length(); ++i)
	{
		unsigned char c = static_cast<unsigned char>(InputText[i]);
		if (c < 128)
		{
			chars.push_back(std::string(1, InputText[i]));
		}
		else if ((c & 0xE0) == 0xC0)
		{
			chars.push_back(InputText.substr(i, 2));
			i += 1;
		}
	}
	return chars;
}