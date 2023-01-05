#ifndef STACK_H
#define STACK_H

#include "defines.h"

#include <stddef.h>
#include <stdbool.h>

// Union of values
union stack_data {
    double var_d;
    void* var_vp;
    char var_c;
    int var_i;
};

// Struct of stack
typedef struct {
    size_t m_top;
    size_t m_capacity;
    enum eType m_type;
    union stack_data* m_data;
} stack;

int create_stack(stack* st_new, const size_t st_size, const enum eType st_type);

void destroy_stack(stack* stack);

int push_stack(stack* const st, ...);

int pop_stack(stack* const st, void* elem);

bool is_empty_stack(const stack* st);

#endif
