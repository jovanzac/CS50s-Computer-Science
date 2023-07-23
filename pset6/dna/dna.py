import sys
import csv


def main():
    # Check if all the command line arguments have been provided
    if len(sys.argv) != 3:
        print("Usage: python dna.py <database> <sequence>")
        sys.exit(1)

    # Load the database into memory
    with open(sys.argv[1], "r") as data_file:
        database = list(csv.DictReader(data_file))
        str_list = list(i for i in database[0] if i != "name")

    # Load the dna sequence to test into memory
    with open(sys.argv[2], "r") as dna_file:
        dna_sequence = dna_file.read()

    # Find out the longest consecutive repeats for each STR in the dna sequence
    str_dict = str_repeats(dna_sequence, str_list)

    # Check the database to see if the dna belongs to the same person
    match = dna_test(str_dict, database)

    print(match)


def str_repeats(dna_sequence, str_list):
    """A function that returns a dict that shows the longest consecutive repeats for each STR"""
    str_dict = dict()

    # Iterate through all the STR in the database, checking for their longest consecutive reccurances in the dna sequence
    for STR in str_list:
        skip = list()
        # Variables to keep count of longest consecutive repeats of an STR
        tmp, longest = 0, 0

        for i in range(len(dna_sequence)):
            if i in skip:
                continue

            elif dna_sequence[i: i + len(STR)] == STR:
                tmp += 1
                skip.extend([j for j in range(i + 1, i + len(STR))])

            else:
                if tmp > longest:
                    longest = tmp
                tmp = 0

        # Add a key value pair to str_dict with the key being the STr and the value being its longest consecutive occurance in the dna sequence
        str_dict[STR] = longest

    return str_dict


def dna_test(str_dict, database):
    """A fuction that compares the values in str_dict and database to check whether they belong to any person in the database"""
    # Going through each person in the database
    for person in database:
        counter = 0

        # Going through each STR in str_dict and comparing it to the STR's for the person
        for STR in str_dict:
            # If an STR in str_dict matches the STR belonging to that person then increment the counter by 1
            if str_dict[STR] == int(person[STR]):
                counter += 1

        # print(counter)
        # Finally if the counter equals the length of str_dict, ie, The value for every STR in str_dct equals the value for every STR belonging to that person
        # Then return the person's name
        if counter == len(str_dict):
            return person["name"]

    # If this line has been reached then it means that we could find no match for the given dna sequence in the database
    # So return 'No match'
    return "No match"


main()