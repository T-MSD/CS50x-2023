#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Start input
    int n;
    do
    {
        n = get_int("Start size: ");
    }
    while (n < 9);

    // End input
    int end;
    do
    {
        end = get_int("End size: ");
    }
    while (end < n);

    int population = n;
    int years = 0;
    int born, dead;
    // Loop to count how many years
    while (population < end)
    {
        born = population / 3;
        dead = population / 4;
        population += born - dead;
        years++;
    }

    // Print years
    printf("Years: %d\n", years);
    return 0;
}
