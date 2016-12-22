#pragma once

typedef struct big_int {
    char sign;
    int * ranks;
    int size;
    int elems;
} big_int;

big_int * scan_big_int(char sign,char first);
void push_back(big_int * b, int num);
big_int * init();
void resize(big_int *big);
void delete(big_int *big);
void add(big_int *a,big_int *b);
void diff(big_int *a,big_int *b);
big_int * multiply(big_int *a, big_int *b); 
big_int * divn(big_int *a, big_int *b);
void print(big_int *a);
int comp(big_int *a, big_int *b);
