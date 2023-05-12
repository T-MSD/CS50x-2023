import csv
import sys


def main():

    # Check for command-line usage
    arguments = len(sys.argv)
    if (arguments != 3):
        print("Wrong Arguments")
        return

    # Read database file into a variable
    person = []
    subsequences = []
    with open(sys.argv[1], "r") as file:
        reader = csv.reader(file)
        for row in reader:
            if (len(subsequences) == 0):
                for i in range(1, len(row)):
                    subsequences.append(row[i])

            # Each person str dictionary
            else:
                strdict = {"name": row[0]}
                for i in range(0, len(subsequences)):
                    strdict[subsequences[i]] = row[i+1]
                # Add to the dictionary list
                person.append(strdict)

    # Read DNA sequence file into a variable
    file = open(sys.argv[2], "r")
    sequence = file.readline()

    # Find longest match of each STR in DNA sequence
    counter = []
    for i in range(0, len(subsequences)):
        value = longest_match(sequence, subsequences[i])
        counter.append(value)

    # Check database for matching profiles
    for i in range(0, len(person)):
        j = 0
        while (j < len(counter)):
            if (int(person[i][subsequences[j]]) != counter[j]):
                break
            elif (j == len(counter) - 1):
                print(person[i]["name"])
                return
            elif (int(person[i][subsequences[j]]) == counter[j]):
                j += 1
    print("No match")
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
