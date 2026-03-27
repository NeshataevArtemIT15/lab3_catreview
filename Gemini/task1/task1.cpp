#include <iostream>
#include <string>
#include "Header.h"

#ifdef _WIN32
#include <windows.h>
#endif

int main()
{
	setlocale(LC_ALL, "Russian");
#ifdef _WIN32
	// Устанавливаем кодировку UTF-8 для ввода и вывода консоли Windows
	SetConsoleCP(65001);
	SetConsoleOutputCP(65001);
#endif

	FTelegraph MorseTelegraph;

	std::cout << "=== Программа Телеграф (Морзе) ===" << std::endl;
	std::cout << "Введите сообщение (русскими буквами): ";

	std::string userInput;
	std::getline(std::cin, userInput);

	std::string result = MorseTelegraph.EncodeMessage(userInput);

	std::cout << "Результат:" << std::endl;
	std::cout << result << std::endl;

	return 0;
}