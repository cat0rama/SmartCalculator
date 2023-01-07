#ifndef UTILS_H
#define UTILS_H

#define DEBUG

#include "defines.h"

#include <stdio.h>

#define type_finder_out(type) _Generic(type,  \
    char:           "%c",                   \
    int:            "%d",                   \
    float:          "%f",                   \
    double:         "%lf",                  \
    unsigned int:   "%u",                   \
    char*:          "%s",                   \
    void*:          "%p"                    \
)

#define extract_as(union, type) ({ \
  type temp_type;              \
                               \
  _Generic(temp_type,          \
    int:    union.var_i,       \
    double: union.var_d        \
    char:   union.var_c,       \
    void*:  union.var_vp       \
  );                           \
})

// Only for my realization of stack!
#define print_stack(data, type)                             \
    type temp_type;                                         \
    for (int i = 0; i < data.m_top; i++) {                  \
        printf(type_finder_out(temp_type), extract_as((data.m_data[i]), type));   \
        if (i != data.m_top - 1) { putc(' ', stdout); }     \
}

#ifdef DEBUG
    #define LOGGER(...) fprintf(__VA_ARGS__);
#else
    #define LOGGER(out, str, ...)
#endif

enum eToken is_operator(const char sym);

enum eToken is_function(const char* string);

#endif
