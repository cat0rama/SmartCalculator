#include "include/parser.h"
#include "include/utils.h"
#include "include/stack.h"

#include <ctype.h>
#include <stdlib.h>

enum eError parse_string(const char* string) {
    if (!string) {
        LOGGER(stderr, "invalid args provided(parse_string)\n");
        return E_INVALID_ARGS;
    }
    
    stack numbers;
    stack operators;

    create_stack(&numbers, 10, T_DOUBLE);
    create_stack(&operators, 10, T_INT);

    while (*string) {
        if (isdigit(*string)) {
            push_stack(&numbers, get_number(&string));
        } else if (is_operator(*string) || is_function(string)) {
            push_stack(&operators, *string);
        }

        if (*string == '\0') {
            break;
        } else {
            string++;
        }
    }

    print_stack(numbers, double);

    // Free data
    destroy_stack(&numbers);
    destroy_stack(&operators);

    return E_SUCCES;
}

double get_number(const char** string) {
    if (!(*string)) {
        LOGGER(stderr, "invalid args provided(get_number)\n");
        return E_INVALID_ARGS;
    }
    
    char temp[MAX_NUMBER] = {0};
    const char *ptr = *string;
    *temp = *ptr;

    int i = 0;
    while (*ptr != '\0' && isdigit(*ptr) || *ptr == '.') {
        temp[i++] = *ptr++;
    }

    // Move string position to next symbol after number
    *string += ptr - 1 - *string;

    return strtod(temp, NULL);
}
