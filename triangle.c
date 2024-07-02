#include <cs50.h>
#include <stdio.h>

bool valid_triangle (float x, float y, float z);

int main(void)
{
    // Input
    int a = get_int("Lado x do triângulo: ");
    int b = get_int("Lado y do triângulo: ");
    int c = get_int("Lado z do triângulo: ");

    // boolean
    bool result = valid_triangle(a, b, c);

    // Output true or false
    printf("%d\n", result);
}

bool valid_triangle (float x, float y, float z)
{
    // If both are positive
    if(x || y || z >= 0)
    {
        // If sum of two are greater than third
        if((x + y <= z) || (y + z <= x) || (x + z <= y))
        {
            return false;
        }
    }
    // If both are false, then true
    return true;
}
