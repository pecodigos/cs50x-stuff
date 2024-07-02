#include <cs50.h>
#include <stdio.h>

void swap(int *a, int *b);

int main(void)
{
    int x = 10;
    int y = 50;

    printf("The value of x is %i, and y is %i.\n", x, y);

    swap(&x, &y);

    printf("The value of x is %i, and y is %i.\n", x, y);
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
