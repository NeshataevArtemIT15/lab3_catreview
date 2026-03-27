#pragma once

#include <string>
#include <unordered_map>
#include <vector>

/**
 * Класс FTelegraph отвечает за преобразование текстовых сообщений
 * в последовательность сигналов азбуки Морзе.
 */
class FTelegraph
{
public:
	FTelegraph();

	/** * Преобразует входную строку (кириллицу) в код Морзе.
	 * @param InputText - исходный текст на русском языке.
	 * @return Строка, состоящая из точек, тире и пробелов.
	 */
	std::string EncodeMessage(const std::string& InputText);

private:
	/** Словарь для хранения соответствия символа и кода Морзе */
	std::unordered_map<std::string, std::string> MorseAlphabet;

	/** Инициализация словаря русским алфавитом */
	void InitializeAlphabet();

	/** Приведение русской UTF-8 строки к верхнему регистру */
	std::string ToUpperCaseRussian(const std::string& InputText);

	/** Разрезает UTF-8 строку на отдельные символы (буквы) */
	std::vector<std::string> GetChars(const std::string& InputText);
};