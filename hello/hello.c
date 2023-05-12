#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // gets the name from the user
    string user_name = get_string("What's your name? ");

    // Displays the name 
    printf("hello, %s\n", user_name);
}