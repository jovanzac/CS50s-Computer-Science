def main():
    # Recieve the text to be graded as input from user
    text = input("Enter the text to be graded: ")

    # Find the number of sentences, words and letters in the user input
    lines, words, letters = count_str(text)

    # Find out the grade of the text using  the Coleman-Liau index
    grade = coleman_liau(lines, words, letters)

    # Print grade
    print_grade(grade)


def count_str(text):
    """Function to keep count of the number of sentences, words and letters in a given text"""
    lines, words, letters = 0, 1, 0

    # Iterate through the text and keep count of the number of sentences, words and letters
    for char in text:
        if char.isalpha():
            letters += 1
        elif char.isspace():
            words += 1
        elif char in [".", "?", "!"]:
            lines += 1

    # Return the number of sentences, words and letters
    return lines, words, letters


def coleman_liau(lines, words, letters):
    # Calculate the Coleman-Liau index for the given text
    return 0.0588 * ((letters / words) * 100) - 0.296 * ((lines / words) * 100) - 15.8


def print_grade(grade):
    """Function to print the approprite grade for the text according to the Coleman-Liau index"""
    if grade < 1:
        print("Before Grade 1")
    elif grade > 16:
        print("Grade 16+")
    else:
        print(f"Grade {round(grade)}")


main()