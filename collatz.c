#include <cs50.h>
#include <stdio.h>

int collatz(int n);

int main(void)
{
    int get_number = get_int("n: ");

    int n = collatz(get_number);

    printf("%i\n", n);
}

int collatz(int n)
{
    // if n is 1, stop
    if (n == 1)
        return 0;
    // otherwise, if n is even, repeat this process on n / 2
    else if ((n % 2) == 0)
        return 1 + collatz(n / 2);
    // otherwise, if n is odd, repeat this process on 3n + 1
    else
        return 1 + collatz(3 * n + 1);
}
