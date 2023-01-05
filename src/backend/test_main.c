#include <stdio.h>

#include "include/defines.h"
#include "include/stack.h"
#include "include/utils.h"

int main() {
    stack st;

    create_stack(&st, 3, T_INT);

    push_stack(&st, 3);
    push_stack(&st, 6);
    push_stack(&st, 23);
    push_stack(&st, 9);
    push_stack(&st, 34);
    push_stack(&st, 55);
    push_stack(&st, 3);
    push_stack(&st, 6);
    push_stack(&st, 23);
    push_stack(&st, 9);
    push_stack(&st, 34);
    push_stack(&st, 55);

    int elem = 0;
    pop_stack(&st, &elem);

    printf("elem %d\n", elem);

    int elem2 = 0;

    pop_stack(&st, &elem2);

    printf("elem %d\n", elem2);
    
    destroy_stack(&st);
}