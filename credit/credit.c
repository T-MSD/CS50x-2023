#include <cs50.h>
#include <stdio.h>


// Gets the input from the user
long get_number(void)
{
    long number;
    do
    {
        number = get_long("Number: ");
    }
    while (number < 0);

    return number;
}


// Verifys if the last digit of the sum is equal to 0
int verify_FinalNumber(int final_number)
{
    if (final_number == 0)
    {
        return 1;
    }
    return 0;
}


// Lunh's Algorithm
int Lunhs_Algorithm(long number)
{
    int n = 0;
    int digit;
    int sum = 0;
    int final_number;

    // When the number is < 1 it means that we reached the 1st digit
    while (number > 1)
    {
        // n is a counter used to iterate trought the number 2 by 2
        n++;
        if (n % 2 == 0)
        {
            // Saves the last digit of the number
            digit = number % 10;
            if (digit > 4)
            {
                // Numbers > 4 when multiplied by 2 have 2 digits so we need to separate them
                digit = digit * 2;
                sum += (digit % 10) + (digit / 10);
            }
            else
            {
                sum += digit * 2;
            }
        }
        // Numbers that we don't need to multiply by 2
        else
        {
            digit = number % 10;
            sum += digit;
        }
        // Removes the last digit
        number = number / 10;
    }

    // Last digit of sum
    final_number = sum % 10;
    return verify_FinalNumber(final_number);
}


// Verifys the number specifiations for American Express
int verify_AMEX(int count_digits, int first2)
{
    if (count_digits == 15 && (first2 == 34 || first2 == 37))
    {
        return 1;
    }
    return 0;
}


// Verifys the number specifiations for Mastercard
int verify_MASTERCARD(int count_digits, int first2)
{
    if (count_digits == 16 && (first2 > 50 && first2 < 56))
    {
        return 1;
    }
    return 0;
}


// Verifys the number specifiations for Visa
int verify_VISA(int count_digits, int first2)
{
    if ((count_digits == 13 || count_digits == 16) && (first2 > 39 && first2 < 50))
    {
        return 1;
    }
    return 0;
}


void count_digits(long number)
{
    if (Lunhs_Algorithm(number))
    {
        int count_digits = 0;
        int first2;

        // When the number is < 1 it means that we reached the 1st digit
        while (number > 1)
        {
            // When the number is < 1000 and we divide by 1 we get the first 2 digits
            if (number < 1000 && number > 99)
            {
                first2 = number / 10;
            }
            // Removes the last digit
            number = number / 10;
            count_digits++;
        }

        if (verify_AMEX(count_digits, first2))
        {
            printf("AMEX\n");
        }
        else if (verify_MASTERCARD(count_digits, first2))
        {
            printf("MASTERCARD\n");
        }
        else if (verify_VISA(count_digits, first2))
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}


int main(void)
{
    count_digits(get_number());
    return 0;
}