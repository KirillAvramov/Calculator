#include <stdio.h>
#include <stdlib.h>
#include "bnumber.h"
#include "stack.h"

void err_m() {
    fprintf(stderr,"empty stack");
}

int main()
{
    big_int *a;
    big_int *b;
    char c;
    stack_init();
    while(1) {
        c=getchar();
        switch(c) {
        case ' ':
        case '\n':
            continue;
        case '=':
            print(stack_peek());
            break;
        case EOF:
        case 'q':
            delete_stack();
            return 0;
            break;
        case '+':
            if(stack_size()<2)
            {
                err_m();
                break;
            }
            b = stack_pop();
            a = stack_pop();
            add(a,b);
            stack_push(a);
            break;
        case '-':
            if(stack_size()<2)
            {
                err_m();
                break;
            }
            b = stack_pop();
            a = stack_pop();
            diff(a,b);
            stack_push(a);
            break;
        case '*':
            if(stack_size()<2)
            {
                err_m();
                break;
            }
            b = stack_pop();
            a = stack_pop();
            stack_push(multiply(a,b));
            break;
        case '/':
            if(stack_size()<2)
            {
                err_m();
                break;
            }
            b = stack_pop();
            a = stack_pop();
            stack_push(divn(a,b));
            break;
        default:
            a=scan_big_int((c=='-'?'-':0),(c=='-'?0:c));
            stack_push(a);
        }
    }
    return 0;
}
