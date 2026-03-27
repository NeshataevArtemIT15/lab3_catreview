// Header.h
// Объявление структуры узла дерева и класса для работы с префиксным выражением

#pragma once

#include <string>

// Структура узла дерева
struct FNode
{
    int Value;      // Значение: число (0-9) или код операции (-1..-4)
    FNode* Left;    // Указатель на левое поддерево
    FNode* Right;   // Указатель на правое поддерево

    // Конструктор для листа (числа)
    FNode(int val) : Value(val), Left(nullptr), Right(nullptr) {}

    // Конструктор для узла-операции
    FNode(int val, FNode* left, FNode* right) : Value(val), Left(left), Right(right) {}
};

// Класс для работы с деревом выражения
class FExpressionTree
{
public:
    // Построение дерева из строки с префиксным выражением
    FNode* BuildTree(const std::string& Expression);

    // Вычисление значения поддерева (рекурсивно)
    int EvaluateSubtree(FNode* Node);

    // Преобразование дерева: удаление + и -, замена на вычисленное значение
    FNode* TransformTree(FNode* Node);

    // Освобождение памяти (рекурсивное удаление всех узлов)
    void DeleteTree(FNode* Node);
};