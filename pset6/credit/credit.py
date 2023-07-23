import sys
import cs50


def main():
    card_num = get_int("Please Enter a Card Number")

    card = card_type_check(card_num)
    if not card:
        print("invalid in 1")
        print("INVALID\n")
        sys.exit(1)

    valid = card_num_check(card_num)

    if valid:
        print(card)
    else:
        print("invalid in 2")
        print("INVALID\n")


def get_int(text):
    """Accepts and returns a card number from user as long as it is a valid integer and is 13, 15 or 16 digits long"""
    card_len, user_input = 0, 0

    user_input = int(input(f"{text} : ").strip())
    card_len = len(str(user_input))

    if card_len not in [13, 15, 16] or not isinstance(user_input, int):
        print("INVALID\n")
        sys.exit(1)

    return user_input


def card_type_check(card_num):
    """Checks to see if the card number received from user belongs to any certain type of card"""
    num = str(card_num)

    # Check if the card number satisfies the conditions for American Express cards
    if len(num) == 15 and num[:2] in ["34", "37"]:
        return "AMEX\n"

    # Check if the card number satisfies the conditions for MasterCards
    elif len(num) == 16 and int(num[:2]) in range(51, 56):
        return "MASTERCARD\n"

    # Check if the card number satisfies the conditions for Visa cards
    elif len(num) in [13, 16] and num[0] == "4":
        return "VISA\n"
    else:
        return False


def card_num_check(card_num):
    """Checks to see if the given card number satisfies Luhn’s Algorithm"""
    num = str(card_num)
    sum_digits = 0
    # Iterating through every other digit starting from the second to last, multiplying each by 2 and adding up the digits of ech of the products
    for digit in num[-2:: -2]:
        pdt = int(digit) * 2
        for p_digit in str(pdt):
            sum_digits += int(p_digit)

    # Iterating through every other digit starting from the last digit and adding them to sum_digits
    for digit in num[len(num) - 1:: -2]:
        sum_digits += int(digit)

    # If the last digit of the sum is 0, card is valid
    if str(sum_digits)[-1] == "0":
        return True
    else:
        return False


main()
