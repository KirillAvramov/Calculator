#include "stack.h"
#include "bnumber.h"

#define FIRST_SIZE 64

static big_int ** stack;
static int size;
static int pointer;
void stack_init() {
    size = FIRST_SIZE;
    stack = (big_int**)malloc(sizeof(big_int*)*size);
    pointer = 0;
}
void stack_resize() {
    size *=2;
    stack = (big_int**)realloc(stack, sizeof(big_int*)*size);
}
void delete_stack() {
    while((pointer-1)&&stack[pointer-1]) {
        delete(stack[pointer-1]);
        pointer--;
    }
    free(stack);
}
void stack_push(big_int * elem) {
    if(!(size - pointer)) {
        stack_resize();
    }
    stack[pointer++] = elem;
}
big_int * stack_peek() {
    return stack[pointer-1];
}
big_int * stack_pop() {
    return stack[--pointer];
}
int stack_size() {
    return pointer;
}
