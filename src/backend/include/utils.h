#ifndef UTILS_H
#define UTILS_H

#define DEBUG

#include <stdbool.h>
#include <string.h>

#include "defines.h"

/**
@brief Макрос для получения нужного спецификатора через тип.
@detailed Подставляет нужный спецификатор на этапе препроцессинга с помощью _Generic.
*/

#define type_finder_out(type)                                                                      \
    _Generic(type,  \
    char:           "%c",                   \
    int:            "%d",                   \
    float:          "%f",                   \
    double:         "%lf",                  \
    unsigned int:   "%u",                   \
    char*:          "%s",                   \
    void*:          "%p"                    \
)

/**
@brief Макрос для получения нужного названия переменной через тип.
@detailed Подставляет нужное название переменной на этапе препроцессинга с помощью _Generic.
*/

// Thanks @bgenia for the help with variadics
#define extract_type_as(union, type)                                                               \
    ({                                                                                             \
        type temp_type;                                                                            \
                                                                                                   \
        _Generic(temp_type,          \
    int:    union.var_i,       \
    double: union.var_d,       \
    char:   union.var_c,       \
    void*:  union.var_vp       \
  );                                                             \
    })

/**
@brief Макрос для сравневния строки через strcmp.
*/

#define STR_EQUAL(str, str2) strcmp(str, str2) == 0

/**
@brief Макрос для вывода элементов стека.
@detailed Вывод осуществляется через два выше описанных макроса. В цикле подставляется спецификатор
и название нужной переменной.
*/

#define PRINT_STACK(data, type)                                                                    \
    type temp_type;                                                                                \
    for (size_t i = 0; i < data.m_top; i++) {                                                      \
        printf(type_finder_out(temp_type), extract_type_as((data.m_data[i]), type));               \
        if (i != data.m_top - 1) {                                                                 \
            putc(' ', stdout);                                                                     \
        }                                                                                          \
    }

/**
@brief Макросы для вывода отладочной информации.
@detailed Работает только если задефайнить DEBUG.
*/

#ifdef DEBUG
#define LOGGER(...) fprintf(__VA_ARGS__);
#else
#define LOGGER(out, str, ...)
#endif

/**
@brief Функция для валидации скобок.
@detailed Валидирует скобки через стек. Нужно для обратки инфиксной нотации на предмет ошибок.
*/

bool validate_parentheses(const char* str);

#endif
