#ifndef PARSER_H
#define PARSER_H

#include <stdbool.h>

#include "defines.h"
#include "stack.h"
#include "stdint.h"

/**
@brief Функции для перевода выражений из инфиксной нотации в обратную польскую нотацию.
*/

/**
@brief Функция для получения токена из определенной лексемы или функции.
@detailed Данная функция является связкой is_operator_unar и is_function.
*/

enum eToken is_operator(const char** string);

/**
@brief Функция для получения приоритета лексемы по токену.
*/

uint8_t get_op_priority(const enum eToken tok);

/**
@brief Функция для записи числа в буфер.
@detailed Данная функция посимвольно записывает число в буфер и двигает указатель на следующую
позицию.
*/

enum eError write_number_in_buffer(const char** string, char* output_str, int* c);

/**
@brief Функция для записи символа в буфер.
@detailed Данная функция записывает символ в буфер и двигает указатель на следующую позицию.
*/

enum eError write_char_in_buffer(stack* st, char* output_str, int* c);

/**
@brief Функция для перевода строки из инфиксной нотации в обратную польскую нотацию.
@detailed Данная функция является связующей для всех остальных функций. Посимвольно проходится по
строке и в зависимости от символа передает в нужную функцию.
*/

enum eError parse_string(const char* string, const char** to_buffer, int* buf_pos);

#endif
