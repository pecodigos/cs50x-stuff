#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int x, y, soma, div, subt, mult;
    string operation;
    string somar = "somar";
    string subtrair = "subtrair";
    string dividir = "dividir";
    string multiplicar = "multiplicar";

    operation = get_string("Você quer somar, subtrair, dividir  ou múltiplicar? \n");

    if (operation == somar)
    {
        x = get_int("Diga o valor de x: ");
        y = get_int("Diga o valor de y: ");
        soma = x + y;
        printf("%i\n", soma);
    }
    else if (operation == subtrair)
    {
        x = get_int("Diga o valor de x: ");
        y = get_int("Diga o valor de y: ");
        subt = x - y;
        printf("%i\n", subt);
    }
    else if (operation == dividir)
    {
        x = get_int("Diga o valor de x: ");
        y = get_int("Diga o valor de y: ");
        div = x / y;
        printf("%f\n", (float) div);
    }
    else if (operation == multiplicar)
    {
        x = get_int("Diga o valor de x: ");
        y = get_int("Diga o valor de y: ");
        mult = x * y;
        printf("%i\n", mult);
    }
}
