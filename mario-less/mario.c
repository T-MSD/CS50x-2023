#include <cs50.h>
#include <stdio.h>

void draw_stairs(void)
{
    int height;

    // repeats until the input meets the requirements
    do
    {
        height = get_int("Height: ");
    }
    // height can't be less than 1, more than 8, letters, strings or nothing
    while (height < 1 || height > 8);

    // repeats until i = height
    for (int i = 0; i < height; i++)
    {
        // prints space "x" times (x = line number - 1)
        for (int j = height - i; j > 1; j--)
        {
            printf(" ");
        }

        // prints # "x" times (x = line number), i + 1 because i starts at 0
        for (int n = 0; n < i + 1; n++)
        {
            printf("#");
        }

        // new line every time a line is complete 
        printf("\n");
    }
}

int main(void)
{
    draw_stairs();
}