#include "Header.h"
#include <iostream>
#include <string>
#include <clocale>

#ifdef _WIN32
#include <windows.h>
#endif

#ifdef _WIN32
// Конвертация UTF-8 std::string -> std::wstring (только для Windows)
static std::wstring Utf8ToWide(const std::string& Utf8)
{
    if (Utf8.empty())
    {
        return {};
    }

    const int Size = MultiByteToWideChar(
        CP_UTF8, 0,
        Utf8.data(), static_cast<int>(Utf8.size()),
        nullptr, 0
    );

    std::wstring Wide(Size, L'\0');
    MultiByteToWideChar(
        CP_UTF8, 0,
        Utf8.data(), static_cast<int>(Utf8.size()),
        Wide.data(), Size
    );

    return Wide;
}
#endif

int main()
{
#ifdef _WIN32
    setlocale(LC_ALL, "Russian");
    // UTF-8 в консоли Windows — наиболее совместимый вариант
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    std::cout << "Введите сообщение на русском языке: ";

    std::string RawInput;
    std::getline(std::cin, RawInput);

    std::wstring Input = Utf8ToWide(RawInput);
#else
    // Linux / macOS: стандартный путь через wcin
    std::setlocale(LC_ALL, "");
    std::locale::global(std::locale(""));
    std::wcin.imbue(std::locale());
    std::wcout.imbue(std::locale());

    std::wcout << L"Введите сообщение на русском языке: ";

    std::wstring Input;
    std::getline(std::wcin, Input);
#endif

    FTelegraph Telegraph;
    const std::string MorseCode = Telegraph.EncodeMessage(Input);

    std::cout << "Код Морзе: " << MorseCode << std::endl;

    return 0;
}