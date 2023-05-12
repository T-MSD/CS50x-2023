from cs50 import get_string


# Get input from the user
def getInput():
    text = get_string("Text: ")
    return text


# Counts the number of letters
def countLetters(text):
    counter = 0
    for i in range(len(text)):
        # Only counts alphabetic characters
        if (text[i].isalpha()):
            counter += 1
    return counter


# Counts the number of words
def countWords(text):
    counter = 0
    i = 0
    l1 = [' ', '.', ',', '!', '?']
    while i < len(text):
        # This avoids counting extra words after a sentence
        if (text[i] in l1 and text[i - 1] in l1):
            counter += 0
        elif (text[i] in l1):
            counter += 1
        i += 1
    return counter


# Counts the number of sentences
def countSentences(text):
    counter = 0
    l1 = ['.', '!', '?']
    for i in range(len(text)):
        if (text[i] in l1):
            counter += 1
    return counter


# Coleman Liau formula and print the results
def ColemanLiau(text):
    words = countWords(text)
    letters = countLetters(text)
    sentences = countSentences(text)

    L = letters * 100 / words
    S = sentences * 100 / words

    # Formula
    index = (0.0588 * L) - (0.296 * S) - 15.8
    grade = round(index)

    if (grade >= 16):
        print("Grade 16+")
    elif (grade < 16 and grade > 1):
        print("Grade " + str(grade))
    elif (grade < 1):
        print("Before Grade 1")


def main():
    text = getInput()
    ColemanLiau(text)


if __name__ == "__main__":
    main()