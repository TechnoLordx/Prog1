#include <stdlib.h>
#include <stdio.h>

void print_out(const char* p, const int x)
{
       // string kiiratasa  int kiiratasa
    printf("p is \"%s\" and x is %d\n", p, x);
}

int main()
{
    printf("Exercise 1\n");
    printf("Hello World!\n\n");

    printf("Exercise 2\n");
    char* first = "Hello";
    char* last = "World!";
    printf("%s %s\n\n", first, last);

    printf("Exercise 3\n");
    print_out("kuta", 233);
    print_out("cica", 14);
    print_out("cow", 30);

    return 0;
}