#include <cs50.h>
#include <stdio.h>

int factorial(int n);

int main(void)
{
    // Get positive value of n
    int n;
    do
    {
        n = get_int("n: ");
    }
    while (n < 0);

    // Print factorial
    printf("%i\n", factorial(n));
}

int factorial(int n)
{
    // Implement factorial function
    // Base case
    if (n == 1)
    {
        return 1;
    }

    return n * factorial(n - 1);
}
