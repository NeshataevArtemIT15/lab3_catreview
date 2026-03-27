// Source.cpp
// Реализация методов класса FExpressionTree

#include "Header.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <cctype>
#include <cstdlib>

// Вспомогательная функция: разбиение строки на токены по пробелам
static std::vector<std::string> Tokenize(const std::string& str)
{
    std::vector<std::string> tokens;
    std::istringstream iss(str);
    std::string token;
    while (iss >> token)
    {
        tokens.push_back(token);
    }
    return tokens;
}

// Рекурсивное построение дерева из списка токенов
// tokens - вектор токенов, index - текущая позиция (передаётся по ссылке)
static FNode* BuildFromTokens(const std::vector<std::string>& tokens, size_t& index)
{
    if (index >= tokens.size())
        return nullptr;

    const std::string& token = tokens[index++];

    // Если токен - число (от 0 до 9), создаём лист
    if (token.size() == 1 && std::isdigit(token[0]))
    {
        int val = std::stoi(token);
        return new FNode(val);
    }

    // Иначе это оператор
    int opCode;
    if (token == "+") opCode = -1;
    else if (token == "-") opCode = -2;
    else if (token == "*") opCode = -3;
    else if (token == "/") opCode = -4;
    else
    {
        // Неизвестный токен (ошибка) – возвращаем nullptr
        return nullptr;
    }

    // Рекурсивно строим левое и правое поддеревья
    FNode* left = BuildFromTokens(tokens, index);
    FNode* right = BuildFromTokens(tokens, index);
    return new FNode(opCode, left, right);
}

// Реализация построения дерева из строки
FNode* FExpressionTree::BuildTree(const std::string& Expression)
{
    std::vector<std::string> tokens = Tokenize(Expression);
    size_t index = 0;
    FNode* root = BuildFromTokens(tokens, index);
    return root;
}

// Вычисление значения поддерева (рекурсивно)
int FExpressionTree::EvaluateSubtree(FNode* Node)
{
    if (!Node)
        return 0;

    // Если узел - число
    if (Node->Value >= 0)
        return Node->Value;

    // Иначе операция
    int leftVal = EvaluateSubtree(Node->Left);
    int rightVal = EvaluateSubtree(Node->Right);

    switch (Node->Value)
    {
    case -1: return leftVal + rightVal;   // +
    case -2: return leftVal - rightVal;   // -
    case -3: return leftVal * rightVal;   // *
    case -4:
        if (rightVal == 0)
        {
            // Обработка деления на ноль: выводим предупреждение, возвращаем 0
            std::cerr << "Warning: division by zero, result set to 0\n";
            return 0;
        }
        return leftVal / rightVal;        // целочисленное деление
    default:
        return 0;
    }
}

// Преобразование дерева: удаление + и -
FNode* FExpressionTree::TransformTree(FNode* Node)
{
    if (!Node)
        return nullptr;

    // Если узел - число, возвращаем его без изменений
    if (Node->Value >= 0)
        return Node;

    // Если узел - операция сложения или вычитания
    if (Node->Value == -1 || Node->Value == -2)
    {
        // Вычисляем значение поддерева
        int result = EvaluateSubtree(Node);
        // Удаляем всё поддерево (текущий узел и потомков)
        DeleteTree(Node);
        // Возвращаем новый узел-число с вычисленным значением
        return new FNode(result);
    }

    // Иначе (умножение или деление) – рекурсивно преобразуем потомков
    Node->Left = TransformTree(Node->Left);
    Node->Right = TransformTree(Node->Right);
    return Node;
}

// Рекурсивное удаление всех узлов поддерева
void FExpressionTree::DeleteTree(FNode* Node)
{
    if (!Node)
        return;
    DeleteTree(Node->Left);
    DeleteTree(Node->Right);
    delete Node;
}