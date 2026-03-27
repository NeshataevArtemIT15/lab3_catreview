// main.cpp
// Точка входа: чтение выражения из файла, построение дерева, преобразование и вывод указателя на корень
// Пример входного файла "filename":
//   * + 2 3 4
// Это выражение в префиксной форме: умножить результат сложения 2 и 3 на 4.
// Допустимые операнды: 0-9, операции: + - * /

#include "Header.h"
#include <fstream>
#include <iostream>
#include <string>

int main()
{
    // Имя файла задано в условии
    const std::string filename = "filename.txt";

    // Чтение содержимого файла
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error: cannot open file " << filename << std::endl;
        return 1;
    }

    std::string expression;
    std::getline(file, expression); // Предполагаем, что выражение в одной строке
    file.close();

    if (expression.empty())
    {
        std::cerr << "Error: file is empty" << std::endl;
        return 1;
    }

    // Создаём объект для работы с деревом
    FExpressionTree tree;

    // Строим дерево из строки
    FNode* root = tree.BuildTree(expression);
    if (!root)
    {
        std::cerr << "Error: failed to build tree from expression" << std::endl;
        return 1;
    }

    // Преобразуем дерево: удаляем + и -, заменяя на вычисленные значения
    root = tree.TransformTree(root);

    // Выводим указатель на корень итогового дерева
    std::cout << static_cast<void*>(root) << std::endl;

    // Очистка памяти (опционально)
    tree.DeleteTree(root);

    return 0;
}