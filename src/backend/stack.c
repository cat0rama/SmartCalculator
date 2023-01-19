#include "include/stack.h"

#include <stdarg.h>
#include <stdlib.h>

#include "include/utils.h"

// Check if type is available
static inline bool type_checker(const enum eType st_type) {
    return st_type >= MAX || st_type <= MIN ? false : true;
}

// Check pointer
static inline bool check_stack_ptr(const stack* const st) {
    return !st || !st->m_data ? false : true;
}

// Create stack
enum eError create_stack(stack* st_new, const size_t st_size, const enum eType st_type) {
    if (!st_new || !type_checker(st_type)) {
        LOGGER(stderr, "invalid args provided(create_stack)\n");
        return E_INVALID_ARGS;
    }

    st_new->m_top = 0;
    st_new->m_type = st_type;
    st_new->m_capacity = st_size;

    // Allocate memory for the size of the maximum type in union
    st_new->m_data = calloc(st_new->m_capacity, sizeof(*st_new->m_data));

    if (!st_new->m_data) {
        perror("calloc() failed\n");
        return E_ALLOCATION_ERROR;
    }

    return E_SUCCES;
}

void destroy_stack(stack* st) {
    if (check_stack_ptr(st)) {
        free(st->m_data);
        st->m_capacity = 0;
        st->m_data = NULL;
        st->m_top = 0;
        st->m_type = 0;
    }
}

enum eError push_stack(stack* const st, ...) {
    if (!check_stack_ptr(st)) {
        LOGGER(stderr, "invalid args provided(push_stack)\n");
        return E_INVALID_ARGS;
    }

    va_list list;
    va_start(list, st);

    if (st->m_top >= st->m_capacity) {
        st->m_capacity = st->m_capacity * 2;
        union stack_data* tmp = realloc(st->m_data, st->m_capacity * sizeof(*st->m_data));
        if (!tmp) {
            perror("realloc() failed\n");
            return E_ALLOCATION_ERROR;
        } else {
            st->m_data = tmp;
        }
    }

    switch (st->m_type) {
    case MIN:
        break;

    case T_DOUBLE:
        st->m_data[st->m_top++].var_d = va_arg(list, double);
        break;

    case T_INT:
        st->m_data[st->m_top++].var_i = va_arg(list, int);
        break;

    case T_CHAR:
        st->m_data[st->m_top++].var_c = (char)va_arg(list, int);
        break;

    case T_VOID_PTR:
        st->m_data[st->m_top++].var_vp = va_arg(list, void*);
        break;

    case MAX:
        break;
    }

    va_end(list);

    return E_SUCCES;
}

enum eError pop_stack(stack* const st, void* elem) {
    if (!check_stack_ptr(st)) {
        LOGGER(stderr, "invalid args provided(pop_stack)\n");
        return E_INVALID_ARGS;
    } else if (st->m_top <= 0) {
        LOGGER(stderr, "stack is empty\n");
        return E_EMPTY;
    }

    if (elem) {
        switch (st->m_type) {
        case MIN:
            break;

        case T_DOUBLE:
            *(double*)elem = st->m_data[--st->m_top].var_d;
            break;

        case T_INT:
            *(int*)elem = st->m_data[--st->m_top].var_i;
            break;

        case T_CHAR:
            *(char*)elem = st->m_data[--st->m_top].var_c;
            break;

        case T_VOID_PTR:
            *(void**)elem = st->m_data[--st->m_top].var_vp;
            break;

        case MAX:
            break;
        }
    } else {
        st->m_top--;
    }

    return E_SUCCES;
}

char get_char_top(stack* const st) {
    if (!check_stack_ptr(st)) {
        LOGGER(stderr, "invalid args provided(pop_stack)\n");
        return -1;
    } else if (is_empty_stack(st)) {
        return -2;
    }

    return st->m_data[st->m_top - 1].var_c;
}

inline bool is_empty_stack(const stack* st) { return check_stack_ptr(st) && st->m_top == 0; }
