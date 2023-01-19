#include "include/utils.h"

#include <stdio.h>
#include <string.h>

#include "include/stack.h"

bool validate_parentheses(const char* str) {
    if (!str) {
        LOGGER(stderr, "invalid arg provided(validate_parentheses)\n");
        return false;
    }

    bool err_flag = 0;
    stack st;

    create_stack(&st, 10, T_CHAR);

    for (size_t i = 0; i < strlen(str); i++) {
        if (str[i] == '(') {
            push_stack(&st, str[i]);
        } else if (!is_empty_stack(&st) && get_char_top(&st) == '(' && str[i] == ')') {
            pop_stack(&st, NULL);
        } else if (str[i] == '(' || str[i] == ')') {
            push_stack(&st, str[i]);
        }
    }

    if (is_empty_stack(&st)) {
        err_flag = true;
    }

    destroy_stack(&st);

    return err_flag;
}
