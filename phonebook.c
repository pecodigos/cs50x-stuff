#include <cs50.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
    string name;
    string number;
} person;

int main(void)
{
    person people[3];

    people[0].name = "Pedro";
    people[0].number = "48-9-98038701";

    people[1].name = "Aerth";
    people[1].number = "48-9-93843891";

    people[2].name = "Mario";
    people[2].number = "48-9-99331239";

    string name = get_string("Name: ");
    for (int i = 0; i < 3; i++)
    {
        if (strcmp(people[i].name, name) == 0)
        {
            printf("Found: %s\n", people[i].number);
            return 0;
        }
    }
    printf("Not found.\n");
    return 1;
}
