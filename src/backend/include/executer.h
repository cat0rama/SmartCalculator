#ifndef EXECUTER_H
#define EXECUTER_H

#include "defines.h"
#include "stack.h"

/**
@brief Функции для обработки и подсчета выражений из обратной польской нотации.
*/

/**
@brief Функция для подсчета функций и операторов из стека.
@detailed Данная функция достает числа из стека и в соответствии с оператором считает выражение.
*/
enum eError calc_operator(const char op, stack* st);

/**
@brief Функция для обработки обратной польской нотации.
@detailed Данная функция проходит строку с обратной польской нотации и вызывает нужные функции в
соответствии с лексемой.
*/

enum eError calc_expression(const char* string, double* out_value, double x, int str_end);

#endif
