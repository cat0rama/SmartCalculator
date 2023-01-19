#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "include/executer.h"
#include "include/parse_infix.h"
#include "include/utils.h"

static double stod(const char* s) {
    double rez = 0, fact = 1;
    if (*s == '-') {
        s++;
        fact = -1;
    };
    for (int point_seen = 0; *s; s++) {
        if (*s == '.') {
            point_seen = 1;
            continue;
        };
        int d = *s - '0';
        if (d >= 0 && d <= 9) {
            if (point_seen)
                fact /= 10.0f;
            rez = rez * 10.0f + (float)d;
        };
    };

    return rez * fact;
};

static double get_number(const char** string) {
    if (!string || !*string) {
        LOGGER(stderr, "invalid arg provided(get_number)\n");
        return E_INVALID_ARGS;
    }

    char temp[MAX_NUMBER] = {0};
    for (int i = 0; **string && (isdigit(**string) || **string == '.'); i++) {
        temp[i] = **string;
        (*string)++;
    }

    return stod(temp);
}

enum eError calc_operator(const char op, stack* st) {
    if (!st) {
        LOGGER(stderr, "invalid stack(calc_operator)\n");
        return E_INVALID_ARGS;
    }

    enum eError err_flag = 0;

    double a = 0, b = 0;
    double temp = 0;

    switch (op) {
    case '+':
        pop_stack(st, &a);
        err_flag = pop_stack(st, &b);
        push_stack(st, b + a);
        break;
    case '-':
        pop_stack(st, &a);
        err_flag = pop_stack(st, &b);
        push_stack(st, b - a);
        break;
    case '/':
        pop_stack(st, &a);
        err_flag = pop_stack(st, &b);
        push_stack(st, b / a);
        break;
    case '^':
        pop_stack(st, &a);
        err_flag = pop_stack(st, &b);
        push_stack(st, pow(b, a));
        break;
    case '*':
        pop_stack(st, &a);
        err_flag = pop_stack(st, &b);
        push_stack(st, b * a);
        break;
    case 's':
        err_flag = pop_stack(st, &temp);
        push_stack(st, sin(temp));
        break;
    case 'c':
        err_flag = pop_stack(st, &temp);
        push_stack(st, cos(temp));
        break;
    case 't':
        err_flag = pop_stack(st, &temp);
        push_stack(st, tan(temp));
        break;
    case 'C':
        err_flag = pop_stack(st, &temp);
        push_stack(st, acos(temp));
        break;
    case 'S':
        err_flag = pop_stack(st, &temp);
        push_stack(st, asin(temp));
        break;
    case 'T':
        err_flag = pop_stack(st, &temp);
        push_stack(st, atan(temp));
        break;
    case 'Q':
        err_flag = pop_stack(st, &temp);
        push_stack(st, sqrt(temp));
        break;
    case 'l':
        err_flag = pop_stack(st, &temp);
        push_stack(st, log(temp));
        break;
    case 'L':
        err_flag = pop_stack(st, &temp);
        push_stack(st, log10(temp));
        break;
    case 'm':
        pop_stack(st, &a);
        err_flag = pop_stack(st, &b);
        push_stack(st, fmod(b, a));
        break;
    case '~':
        err_flag = pop_stack(st, &temp);
        push_stack(st, temp * -1);
        break;
    case '&':
        break;
    }

    return err_flag;
}

enum eError calc_expression(const char* string, double* out_value, double x, int str_end) {
    if (!string || !out_value) {
        return E_INVALID_ARGS;
    }

    enum eError err_flag = 0;

    stack st = {0};
    create_stack(&st, 10, T_DOUBLE);

    for (int i = 0; *string && i < str_end; i++) {
        if (isdigit(*string)) {
            push_stack(&st, get_number(&string));
        } else if (*string == 'x') {
            push_stack(&st, x);
        }

        err_flag = calc_operator(*string, &st);

        if (err_flag < 0) {
            break;
        } else if (*string != '\0') {
            string++;
        }
    }

    if (err_flag < 0) {
        pop_stack(&st, out_value);
    } else {
        err_flag = pop_stack(&st, out_value);
    }
    destroy_stack(&st);

    return err_flag;
}
