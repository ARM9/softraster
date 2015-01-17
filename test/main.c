#include <stdio.h>

void f(void *a, void *b){
    printf("%p\n%p", a, b);
}

int main(int argc, char *argv[])
{
    int foo=5, bar=3;
    return 0;
}

