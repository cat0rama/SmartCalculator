#include "include/utils.h"

#include <stdio.h>

enum eToken is_operator(const char sym) {
    switch (sym)
    {
    case '+':
        return O_ADD;
    case '-':
        return O_SUB;
    case '/':
        return O_DIV;
    case '*':
        return O_MUL;
    case '^':
        return O_EXP;
    }

    return O_UNKNOWN;
}

enum eToken is_function(const char* string) {
    // доделать(Сагьрай лезгияр)

    return O_UNKNOWN;
}
