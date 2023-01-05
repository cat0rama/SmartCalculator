#ifndef UTILS_H
#define UTILS_H

#include "defines.h"

#include <stdio.h>

#define type_finder_out(type) _Generic((type),    \
        char:           "%c\n",                   \
        int:            "%d\n",                   \
        float:          "%f\n",                   \
        double:         "%lf\n",                  \
        unsigned int:   "%u\n",                   \
        char*:          "%s\n",                   \
        void*:          "%p\n"                    \
)

#define print_data(data, n)                       \
for (int i = 0; i < n; i++) {                     \
    printf(type_finder_out(*data), data[i]);      \
    if (i != n - 1) { printf(" "); }              \
}

#endif
