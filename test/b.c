#include <stdio.h>

#define masm(...) #__VA_ARGS__ "\n"

void f(){
    asm(masm(
        mov rcx, 'a';
        call putchar;
        ):::"rcx");
}

int main(int argc, char *argv[])
{
    f();
    printf("\n%d\n%d", 1, 2);
    return 0;
}

