#ifndef DEFINES_H
#define DEFINES_H

#define MAX_STRING 255
#define MAX_NUMBER 30

// Enum of possible errors
enum eError {
    E_SUCCES, E_ALLOCATION_ERROR, E_INVALID_ARGS, E_INVALID_TYPE, E_EMPTY
};

// Enum of types
enum eType {
    MIN, T_DOUBLE, T_CHAR, T_INT, T_VOID_PTR, MAX
};

// Enum of tokens
enum eToken {
    O_UNKNOWN, O_MUL, O_SUB, O_ADD, O_DIV, O_EXP, O_OBRACK, O_CBRACK, O_COS,
    O_SIN, O_TAN, O_ACOS, O_ASIN, O_ATAN, O_SQRT, O_LN, O_LOG
};

#endif
