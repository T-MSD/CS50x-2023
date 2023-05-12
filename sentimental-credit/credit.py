from cs50 import get_int
import math


# Gets the input from the user
def getInput():
    number = get_int("Number: ")
    while (number <= 0):
        number = get_int("Number: ")
    return number


# Verifys specifiations for American Express
def verifyAmex(number):
    string = str(number)
    if (len(string) == 15 and (int(string[:2]) == 34 or int(string[:2]) == 37)):
        return True
    return False


# Verifys specifiations for Visa
def verifyVisa(number):
    string = str(number)
    if ((len(string) == 13 or len(string) == 16) and int(string[0]) == 4):
        return True
    return False


# Verifys specifiations for Mastercard
def verifyMastercard(number):
    string = str(number)
    if (len(string) == 16 and int(string[:2]) > 50 and int(string[:2]) < 56):
        return True
    return False


# Lunh's Algorithm
def LunhsAlgorithm(number):
    sum = 0
    index = 0
    # When the number is < 1 it means that we reached the 1st digit
    while (number > 1):
        # Variable to iterate throught the number
        index += 1
        if (index % 2 == 0):
            # Get the last digit
            digit = number % 10
            # Numbers > 4 when multiplied by 2 have 2 digits so we need to separate them
            if (digit > 4):
                digit = digit * 2
                sum += (digit % 10) + (digit // 10)
            else:
                sum += digit * 2
        # Numbers that we don't need to multiply by 2
        else:
            sum += number % 10
        # Removes the last digit
        number = number // 10
    if (sum % 10 == 0):
        return True
    return False


def main():
    number = getInput()
    if (LunhsAlgorithm(number)):
        if (verifyAmex(number)):
            print("AMEX")
        elif (verifyMastercard(number)):
            print("MASTERCARD")
        elif (verifyVisa(number)):
            print("VISA")
        else:
            print("INVALID")
    else:
        print("INVALID")


if __name__ == "__main__":
    main()