#include <stdio.h>
#include <stdlib.h>
#include "bnumber.h"
const int base = 1000000000;

big_int * init() {
    big_int * new_bn;
    new_bn = (big_int*)malloc(sizeof(big_int));
    new_bn->size = 64;
    new_bn->elems = 0;
    new_bn->sign = 0;
    new_bn->ranks = (int*)malloc(sizeof(int)*new_bn->size);
    return new_bn;
}
void resize(big_int* big) {
    big->size *= 2;
    big->ranks = (int*)realloc(big->ranks,sizeof(int)*big->size);
}
void delete(big_int *big) {
    free(big->ranks);
    free(big);
}
void push_back(big_int *b, int num) {
    if(!(b->size - b->elems))
        resize(b);
    b->ranks[b->elems++] = num;
}
big_int * scan_big_int(char sign, char first) {
    big_int *result = init();
    result->sign = sign;
    int temp=0, ch_size = 128;
    char c;
    char * ch = (char*)malloc(sizeof(char)*ch_size);
    if(first>='1'&&first<='9') {
        ch[temp++] = first;
    }
    while((c=getchar())!= '\n'&& c!= ' ' && c!= EOF) {
        if(!(ch_size - temp)) {
            ch = (char*)realloc(ch,sizeof(char)*ch_size);
        }
        ch[temp++] = c;
    }
    ch[temp] = '\0';
    int i;
    for(i = (int)strlen(ch);i>0;i-=9) {
        ch[i]=0;
        push_back(result, atoi(i>=9?ch+i-9:ch));
    }
    free(ch);
    return result;
}
void print(big_int *a) {
    printf("%d",(a->elems==0?0:a->ranks[a->elems-1]));
    int i;
    for(i = a->elems - 2;i>= 0;i--) {
        printf("%09d",a->ranks[i]);
    }
    printf("\n");
}
void add(big_int *a, big_int *b) {
    print(a);
    print(b);
     int carry=0,i;
     for(i=0;i<a->elems || i<b->elems || carry ;i++) {
            if(i==a->elems) {
                push_back(a,0);
            }
            a->ranks[i] += carry + (i < (b->elems)? (b->ranks[i]):0);
            carry = a->ranks[i] >= base;
            if(carry) a->ranks[i] -= base;
     }
}
void diff(big_int *a, big_int *b) {
    int carry = 0,i;
    for(i=0;i<b->elems||carry;++i) {
        a->ranks[i] -= carry + (i < b->elems ? b->ranks[i] : 0);
        carry = a->ranks[i] < 0;
        if(carry) a->ranks[i] += base;
    }
    while( a->elems > 1 && a->ranks[a->elems-1]==0)
        a->elems--;
}
big_int * multiply(big_int *a, big_int *b) {
    big_int *c = init();
    while(c->size<a->elems+b->elems) {
        resize(c);
    }
    int i,j,carry;
    c->elems = a->elems + b->elems;
    for(i = 0;i < c->elems;i++) {
        c->ranks[i] = 0;
    }
    for( i=0;i<a->elems;i++) {
        for( j =0, carry =0;j<b->elems || carry; ++j) {
            long long cur = c->ranks[i+j] + a->ranks[i]*1ll*(j<b->elems?b->ranks[j]:0) + carry;
            c->ranks[i+j] =  (cur % base);
            carry =  (cur / base);

        }
    }
    while (c->elems > 1 && c->ranks[c->elems -1] == 0)
        c->elems--;
    return c;
}
big_int *  divn(big_int *a, big_int *b) {
    big_int *c = init(), *d = init(),*res =init() ;
    c->elems = 1;
    d->elems = 1;
    res->elems = 0;
    c->ranks[0] = 0;
    d->ranks[0] = 1;
    res->ranks[0] =1;
    add(c,b);
    if(!comp(a,b))
        return d;
    while(comp(a,b)<0) {
        add(b,c);
        add(res,d);
    }
    return res;
}

int comp(big_int *a, big_int *b) {
    if(a->elems > b->elems)
        return -1;
    if(a->elems < b->elems)
        return 1;
    int i = a->elems-1;
    for(; i>=0;i--) {
        if(a->ranks[i]> b->ranks[i])
            return -1;
        if(a->ranks[i] < b->ranks[i])
            return 1;
    }
    return 0;
}
