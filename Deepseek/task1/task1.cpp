#include "Header.h"
#include <iostream>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

/*
Пример ввода/вывода:
Введите строку на русском языке: Привет мир
Результат: .--. .-. .. .-- . -   -- .. .-.
(буквы разделены одинарными пробелами, слова — двойными)
*/

int main()
{
    setlocale(LC_ALL, "Russian");
    // Настройка консоли для работы с UTF-8
#ifdef _WIN32
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
#endif

    FTelegraph Telegraph;

    std::cout << "Введите строку на русском языке: ";
    std::string Input;
    std::getline(std::cin, Input);

    std::string Encoded = Telegraph.EncodeMessage(Input);
    std::cout << "Результат: " << Encoded << std::endl;

    return 0;
}