#include <stdio.h>
#include <cs50.h>

string find_card_type(long card_num);

string luhns_algorithm(long card_num);

int main(void)
{
    string valid = "VALID";
    string invalid = "INVALID";
    long card_num = get_long("Enter your credit card number: ");
    string card_type = find_card_type(card_num);
    if (card_type == invalid)
    {
        printf("INVALID\n");
    }
    else
    {
        string validity = luhns_algorithm(card_num);
        if (validity == valid)
        {
            printf("%s\n", card_type);
        }
        else
        {
            printf("INVALID\n");
        }
    }
}


string find_card_type(long card_num)
{
    // To find what the card type is, ie, Visa, AMEX or MasterCard
    // Done by checking the length of the card number and the first digits.
    int num_len = 0;
    long num_copy = card_num;
    string card_type = "INVALID";
    while (num_copy != 0)
    {
        num_copy /= 10;
        num_len++;
    }
    if (num_len == 13)
    {
        int first_digit = card_num / 1000000000000;
        if (first_digit == 4)
        {
            card_type = "VISA";
        }
    }
    else if (num_len == 15)
    {
        int first_two_digits = card_num / 10000000000000;
        if (first_two_digits == 34 || first_two_digits == 37)
        {
            card_type = "AMEX";
        }
    }
    else if (num_len == 16)
    {
        int first_two_digits = card_num / 100000000000000;
        if (first_two_digits > 50 && first_two_digits < 56)
        {
            card_type = "MASTERCARD";
        }
        else if (first_two_digits >= 40 && first_two_digits < 50)
        {
            card_type = "VISA";
        }
    }
    return card_type;
}

string luhns_algorithm(long card_num)
{
    int sum = 0;
    while (card_num > 0)
    {
        int last_num = card_num % 10;
        card_num /= 10;
        int second_last = 2 * (card_num % 10);
        card_num /= 10;
        int digits_sum = 0;
        while (second_last > 0)
        {
            digits_sum += second_last % 10;
            second_last /= 10;
        }
        sum += (digits_sum + last_num);
    }
    if (sum % 10 == 0)
    {
        return "VALID";
    }
    else
    {
        return "INVALID";
    }
}