#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int verify_arg(int argc, string argv[]);
void Caesar_cypher(string plaitext, string argv[]);

int main(int argc, string argv[])
{
    if (verify_arg(argc, argv))
    {
        return 1;
    }

    string plaintext = get_string("plaintext: ");
    Caesar_cypher(plaintext, argv);

    return 0;
}


int verify_arg(int argc, string argv[])
{
    int length;
    // Verifyes if the number of the arguments is != 2, one for ./caesar and the other one for the key
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    else
    {
        // Since argv is a "string with strings" we need to use argv[1], argv[1] == key
        length = strlen(argv[1]);
        for (int i = 0; i < length; i++)
        {
            // In argv[1][i] i represents each character of the key. If the key contains letters the function returns 1
            if (isalpha(argv[1][i]))
            {
                printf("Usage: ./caesar key\n");
                return 1;
            }
        }
    }
    return 0;
}


void Caesar_cypher(string plaintext, string argv[])
{
    int length = strlen(plaintext);
    int key = atoi(argv[1]);
    char ciphertext[length];
    int  value;
    for (int i = 0; i < length + 1; i++)
    {
        // For alphabetical characters
        if (isalpha(plaintext[i]))
        {
            // Keys smaller or equal to 26
            if (key <= 26)
            {
                value = plaintext[i] + key;
                // Verfifys if the value does not exceed the 'Z' lowercase/uppercase value
                if ((islower(plaintext[i]) && value <= 122) || (isupper(plaintext[i]) && value <= 90))
                {
                    // The ith character on the ciphertext after encrypting
                    ciphertext[i] = (char)(value);
                }
                // The value exceeds the 'Z' lowercase/uppercase value
                else
                {
                    // Avoids examples like: A + 27 becoming [
                    value -= 26;
                    ciphertext[i] = (char)(value);
                }
            }
            // Keys bigger than 26
            else
            {
                value = plaintext[i] + (key % 26);
                if ((islower(plaintext[i]) && value <= 122) || (isupper(plaintext[i]) && value <= 90))
                {
                    ciphertext[i] = (char)(value);
                }
                else
                {
                    value -= 26;
                    ciphertext[i] = (char)(value);
                }
            }
        }
        // Non alphabetical characters
        else
        {
            ciphertext[i] = plaintext[i];
        }
    }
    printf("ciphertext: %s", ciphertext);
    printf("\n");
}