import csv
import sys


def main():

    # Check for command-line usage
    if len(sys.argv) != 3:
        print("Correct usage: 'python dna.py database/filename.csv sequences/n'")
        return

    rows = []
    # Read database file into a variable
    with open(sys.argv[1]) as file:
        read_data = csv.DictReader(file)
        for row in read_data:
            rows.append(row)

        # Read DNA sequence file into a variable
        with open(sys.argv[2]) as file:
            read_seq = file.read()

            # Find longest match of each STR in DNA sequence
            str_count = {}
            str_fieldnames = read_data.fieldnames
            str_fieldnames.remove('name')
            for str_ in str_fieldnames:
                str_count[str_] = longest_match(read_seq, str_)

            # Check database for matching profiles
            match_person = False
            for row in rows:
                for str_ in str_count:
                    if str_count[str_] != int(row[str_]):
                        break
                else:
                    match_person = True
                    print(row['name'])

            if match_person == False:
                print("No match")


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
