#include "include/stack.h"
#include "include/utils.h"

#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

// Check if type is available
static inline bool type_checker(const enum eType st_type) {
    return st_type >= ALL || st_type <= MIN ? false : true;
}

// Check pointer
static inline bool check_ptr(const stack* const st) {
    return !st || !st->m_data ? false : true; 
}

int create_stack(stack* st_new, const size_t st_size, const enum eType st_type) {
    if (!st_new || !type_checker(st_type) || st_size < 0) {
        fprintf(stderr, "invalid args provided\n");
        return E_INVALID_ARGS;
    }

    st_new->m_top = 0;
    st_new->m_type = st_type;
    st_new->m_capacity = st_size;
    
    // Allocate memory for the size of the maximum type in union
    st_new->m_data = calloc(st_new->m_capacity, sizeof(*st_new->m_data));

    if (!st_new->m_data) {
        fprintf(stderr, "calloc() failed\n");
        return E_ALLOCATION_ERROR;
    }

    return E_SUCCES;
}

void destroy_stack(stack* stack) {
    if (stack && stack->m_data) {
        free(stack->m_data);
    }
}

int push_stack(stack* const st, ...) {
    if (!check_ptr(st)) {
        puts("invalid args provided");
        return E_INVALID_ARGS;
    }

    va_list list;
    va_start(list, st);

    if (st->m_top >= st->m_capacity) {
        st->m_capacity = st->m_capacity * 2;
        union stack_data* tmp = realloc(st->m_data, st->m_capacity * sizeof(*st->m_data));
        if (!tmp) {
            fprintf(stderr, "realloc() failed\n");
            return E_ALLOCATION_ERROR;
        } else {
            st->m_data = tmp;
        }
    }

    switch (st->m_type) 
    {
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
    }

    va_end(list);
    
    return E_SUCCES;
}

int pop_stack(stack* const st, void* elem) {
    if (!check_ptr(st) || !elem) {
        fprintf(stderr, "invalid args provided\n");
        return E_INVALID_ARGS;
    }

    switch (st->m_type) 
    {
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
    }

    return E_SUCCES;
}

bool is_empty_stack(const stack* st) {
    return check_ptr(st) && st->m_top == 0;
}
