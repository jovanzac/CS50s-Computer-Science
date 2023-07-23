def main():
    # get the height of the mario blocks from the user
    height = get_int("How tall must the blocks be", 1, 8)
    # Print the mario blocks onto the screen
    print_blocks(height)


def get_int(text, lower_bound, upper_bound):
    """Returns an integer input from the user. Accepts the user input as long as its an int and it is within the specified upper and lower bounds"""
    user_input = lower_bound - 1
    while user_input < lower_bound or user_input > upper_bound:
        try:
            user_input = int(input(f"{text} : "))
        except:
            user_input = lower_bound - 1
    return user_input


def print_blocks(height):
    """ Prints the Mario blocks on the screen"""
    for i in range(height):
        print(" " * (height - i - 1) + "#" * (i + 1) + "  " + "#" * (i + 1))


main()