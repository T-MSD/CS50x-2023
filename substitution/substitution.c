#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int verify_arg(int argc, string argv[]);
int verify_letter(char letter, char alphabet[26]);
void cipher(string plaintext, string argv[]);

int main(int argc, string argv[])
{
    if (verify_arg(argc, argv))
    {
        return 1;
    }

    string plaintext = get_string("plaintext: ");
    cipher(plaintext, argv);

    return 0;
}


int verify_arg(int argc, string argv[])
{
    int length;
    // Variable to store all the letters
    char alphabet[26];
    // Verifyes if the number of the arguments is != 2, one for ./caesar and the other one for the key
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else
    {
        // Since argv is a "string with strings" we need to use argv[1], argv[1] == key
        length = strlen(argv[1]);
        if (length != 26)
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
        for (int i = 0; i < length; i++)
        {
            // In argv[1][i] i represents each character of the key. If the key contains numbers the function returns 1
            if (!isalpha(argv[1][i]))
            {
                printf("Key must contain 26 characters.\n");
                return 1;
            }
            // Verifys if the letters is repeated or not
            if (verify_letter(argv[1][i], alphabet))
            {
                printf("Must contain each letter exactly once.\n");
                return 1;
            }
            // When not repeted adds the letter to the varaible to compare on the next loop
            else
            {
                alphabet[i] = argv[1][i];
            }
        }
    }
    return 0;
}

// Verifys if the letter is repeated
int verify_letter(char letter, char alphabet[26])
{
    for (int i = 0; i < 26; i++)
    {
        if (letter == alphabet[i])
        {
            return 1;
        }
    }
    return 0;
}


void cipher(string plaintext, string argv[])
{
    int value;
    int length = strlen(plaintext);
    char ciphertext[length];

    for (int i = 0; i < length + 1; i++)
    {
        // For alphabetical characters
        if (isalpha(plaintext[i]))
        {
            // Lowercase letters
            if (islower(plaintext[i]))
            {
                // Subtracting 97 gives us the position in the key array (value) since it is in "alphabetical order" (a = position 0 and z = position 25).
                // 97 because 'a' value on the ascii table is 97 (97 - 97 = 0 = position in the  key array)
                value = plaintext[i] - 97;
                // Tolower allows us to handle lowercase and uppercase keys
                ciphertext[i] = tolower(argv[1][value]);
            }
            // Uppercase letters
            else if (isupper(plaintext[i]))
            {
                // Subtracting 65 gives us the position in the key array (value) since it is in "alphabetical order" (a = position 0 and z = position 25).
                // 65 because 'A' value on the ascii table is 65 (65 - 65 = 0 = position in the  key array)
                value = plaintext[i] - 65;
                // Tolupper allows us to handle lowercase and uppercase keys
                ciphertext[i] = toupper(argv[1][value]);
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