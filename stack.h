#pragma once
#include "bnumber"

void stack_init();
void stack_resize();
void delete_stack();
void stack_push(big_int * elem);
big_int * stack_peek();
big_int * stack_pop();
int stack_size();
