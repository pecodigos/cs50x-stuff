#include <cs50.h>
#include <stdio.h>

float multiply_numbers(float x, float y);
int add_two_ints(int a, int b);

int main(void)
{
    // input
    int x = get_int("Give me an integer: ");
    int y = get_int("Give me an integer: ");

    // add the two numbers via a function call
    int sum = add_two_ints(x,y);
    // multiply the two numbers via a function call
    int mult = multiply_numbers(x,y);
    // output result
    printf("%i + %i = %i.\n", x, y, sum);
    printf("%i * %i = %i.\n", x, y, mult);
}

float multiply_numbers(float x, float y)
{
    return x * y;
}

int add_two_ints(int a, int b)
{
    return a + b;
}



