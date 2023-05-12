def main():
    number = input("Height: ")
    # Validate user input
    while (number.isnumeric() != True or int(number) < 1 or int(number) > 8):
        number = input("Height: ")
    number = int(number)
    # Print each row
    for i in range(1, number + 1):
        print(" " * (number - i) + "#" * i + "  " + "#" * i)


main()