#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);

void build_number(int n)
{
    int number;
    char s_number[BITS_IN_BYTE + 1] = "00000000";
    // j = 7 to start from the end of the binary number
    int j = 7;
    while (n >= 0)
    {
        // Get the number 0 or 1
        number = n % 2;
        if (number == 1)
        {
            s_number[j] = '1';
        }
        j--;
        if (n == 0)
        {
            break;
        }
        n = n / 2;
    }

    int x;
    // Loop to print each bulb
    for (int i = 0; i < BITS_IN_BYTE; i++)
    {
        // -48 because 48 in the asccii table = 0
        x = s_number[i] - 48;
        print_bulb(x);
    }
    // printf next line
    printf("\n");
}

int main(void)
{
    // Get user input
    string message = get_string("Message: ");
    int c;
    for (int i = 0; i < strlen(message); i++)
    {
        // Ascii character value
        c = message[i];
        build_number(c);
    }
}

void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}
