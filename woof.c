#include <cs50.h>
#include <stdio.h>

void woof(int n);

int main(void)
{
    woof(5);
}

void woof(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("woof\n");
    }
}
