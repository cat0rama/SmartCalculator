#include "include/parse_infix.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "include/utils.h"

static bool is_operator_unar(const char sym) {
    switch (sym) {
    case '+':
    case '-':
    case '/':
    case '*':
    case '^':
    case '(':
    case ')':
        return true;
    }

    return false;
}

static enum eToken get_tok_func_by_name(const char* string) {
    if (!string) {
        LOGGER(stderr, "invalid arg provided(get_func_by_name)\n");
        return O_UNKNOWN;
    }

    if (STR_EQUAL("cos", string)) {
        return O_COS;
    } else if (STR_EQUAL("sin", string)) {
        return O_SIN;
    } else if (STR_EQUAL("tan", string)) {
        return O_TAN;
    } else if (STR_EQUAL("acos", string)) {
        return O_ACOS;
    } else if (STR_EQUAL("asin", string)) {
        return O_ASIN;
    } else if (STR_EQUAL("atan", string)) {
        return O_ATAN;
    } else if (STR_EQUAL("sqrt", string)) {
        return O_SQRT;
    } else if (STR_EQUAL("ln", string)) {
        return O_LN;
    } else if (STR_EQUAL("log", string)) {
        return O_LOG;
    } else if (STR_EQUAL("mod", string)) {
        return O_MOD;
    }

    return O_UNKNOWN;
}

static enum eToken is_function(const char** string) {
    if (!string || !*string) {
        LOGGER(stderr, "invalid arg provided(is_function)\n");
        return O_UNKNOWN;
    }

    char temp[MAX_FUNC_NAME] = {0};
    const char* ptr = *string;

    // Copy func name to temp array
    for (int i = 0; *ptr && i < MAX_FUNC_NAME;) {
        if (*ptr == '\0' || isdigit(*ptr) || is_operator_unar(*ptr) || *ptr == ' ') {
            break;
        } else {
            temp[i++] = *ptr++;
        }
    }

    enum eToken tok = get_tok_func_by_name(temp);

    // Move string position to next symbol after number
    if (tok) {
        *string += ptr - 1 - *string;
    }

    return tok;
}

inline uint8_t get_op_priority(const enum eToken tok) {
    switch (tok) {
    case O_OBRACK:
        return 5;
    case O_CBRACK:
        return 0;
        break;
    case O_ADD:
    case O_SUB:
        return 10;

    case O_DIV:
    case O_MUL:
    case O_MOD:
        return 20;

    case O_EXP:
        return 30;

    case O_COS:
    case O_SIN:
    case O_TAN:
    case O_ACOS:
    case O_ASIN:
    case O_ATAN:
    case O_SQRT:
    case O_LN:
    case O_LOG:
        return 40;

    case O_U_MINUS:
    case O_U_PLUS:
        return 50;

    case O_UNKNOWN:
        break;
    }

    return O_UNKNOWN;
}

enum eError write_number_in_buffer(const char** string, char* output_str, int* c) {
    if (!string || !*string || !output_str || !c || *c > MAX_OUTPUT_LEN) {
        LOGGER(stderr, "invalid args provided(write_number_in_buffer)\n");
        return E_INVALID_ARGS;
    }

    for (; **string != '\0' && (isdigit(**string) || **string == '.');) {
        output_str[(*c)++] = **string;
        (*string)++;
    }
    (*c)++;

    return E_SUCCES;
}

enum eError write_char_in_buffer(stack* st, char* output_str, int* c) {
    if (!output_str || !c || *c > MAX_OUTPUT_LEN) {
        LOGGER(stderr, "invalid args provided(write_number_in_buffer)\n");
        return E_INVALID_ARGS;
    }

    enum eError err_flag = 0;

    char tmp_op = 0;
    err_flag = pop_stack(st, &tmp_op);
    output_str[*c] = tmp_op;
    *c += 2;

    return err_flag;
}

enum eToken is_operator(const char** string) {
    enum eToken tok = 0, tmp;
    if (is_operator_unar(**string)) {
        tok = **string;
    } else if ((tmp = is_function(string))) {
        tok = tmp;
    }

    return tok;
}

enum eError parse_string(const char* string, const char** to_buffer, int* buf_pos) {
    if (!string || strlen(string) > MAX_STRING || !buf_pos) {
        LOGGER(stderr, "invalid arg provided(parse_string)\n");
        return E_INVALID_ARGS;
    }

    static char output_str[MAX_OUTPUT_LEN] = {0};
    memset(output_str, ' ', MAX_OUTPUT_LEN - 1);

    enum eError err_flag = 0;

    stack ops = {0};
    create_stack(&ops, 10, T_CHAR);

    for (int i = 0; *string; i++) {
        enum eToken tok = 0;

        if ((*string == '-' && i == 0) || (*(string - 1) == '(' && *string == '-')) {
            push_stack(&ops, O_U_MINUS);
            string++;
        } else if ((*string == '+' && i == 0) || (*(string - 1) == '(' && *string == '+')) {
            push_stack(&ops, O_U_PLUS);
            string++;
        }

        if (isdigit(*string)) {
            if (write_number_in_buffer(&string, output_str, buf_pos) < 0) {
                err_flag = E_INVALID_DATA;
            }
        } else if (*string == 'x') {
            output_str[*buf_pos] = *string;
            *buf_pos += 2;
        }

        if ((tok = is_operator(&string))) {
            if (tok == ')') {
                while (!is_empty_stack(&ops) && get_char_top(&ops) != '(') {
                    if (write_char_in_buffer(&ops, output_str, buf_pos) < 0) {
                        err_flag = E_INVALID_DATA;
                    }
                }
                pop_stack(&ops, NULL);
            } else {
                if (is_empty_stack(&ops)) {
                    push_stack(&ops, tok);
                } else {
                    if (get_op_priority(tok) > get_char_top(&ops)) {
                        push_stack(&ops, tok);
                    } else {
                        while (!is_empty_stack(&ops) &&
                               get_op_priority(tok) <= get_op_priority(get_char_top(&ops)) &&
                               tok != '(') {
                            if (write_char_in_buffer(&ops, output_str, buf_pos) < 0) {
                                err_flag = E_INVALID_DATA;
                            }
                        }
                        push_stack(&ops, tok);
                    }
                }
            }
        }

        if (err_flag < 0) {
            break;
        } else if (*string != '\0') {
            string++;
        }
    }

    // Writing the remaining characters to the output string
    if (err_flag >= 0) {
        while (!is_empty_stack(&ops)) {
            err_flag = write_char_in_buffer(&ops, output_str, buf_pos);
        }
        // Get buffer from func
        *to_buffer = output_str;
    } else {
        err_flag = E_CALC_ERROR;
    }

    // Free data
    destroy_stack(&ops);

    return err_flag;
}
