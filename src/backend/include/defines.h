#ifndef DEFINES_H
#define DEFINES_H

#define MAX_STRING 255
#define MAX_NUMBER 30
#define MAX_FUNC_NAME 10
#define MAX_OUTPUT_LEN 564

#include <stddef.h>
#include <stdio.h>

/**
@brief Перечисление для описания ошибок.
*/

enum eError {
    E_UNKNOWN_ERROR = 0,
    E_ALLOCATION_ERROR = -1,
    E_INVALID_ARGS = -2,
    E_INVALID_TYPE = -3,
    E_EMPTY = -4,
    E_CALC_ERROR = -5,
    E_SUCCES = 1,
    E_INVALID_EXPR = -6,
    E_INVALID_DATA = -7
};

/**
@brief Перечисление для описания типов.
*/

enum eType { MIN, T_DOUBLE, T_CHAR, T_INT, T_VOID_PTR, MAX };

/**
@brief Перечисление для описания токенов.
*/

enum eToken {
    O_UNKNOWN,
    O_MUL = '*',
    O_SUB = '-',
    O_ADD = '+',
    O_DIV = '/',
    O_EXP = '^',
    O_OBRACK = '(',
    O_CBRACK = ')',
    O_COS = 'c',
    O_SIN = 's',
    O_TAN = 't',
    O_ACOS = 'C',
    O_ASIN = 'S',
    O_ATAN = 'T',
    O_SQRT = 'Q',
    O_LN = 'l',
    O_LOG = 'L',
    O_MOD = 'm',
    O_U_MINUS = '~',
    O_U_PLUS = '&'
};

#endif
