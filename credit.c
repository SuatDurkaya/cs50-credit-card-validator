#include <cs50.h>
#include <stdio.h>

int amex_checker(long card_number);
int visa_checker(long card_number);
int masterc_checker(long card_number);
int check_sum(long card_number);

int length(long card_number);

int main(void)
{
    long card_number;
    do
    {
        card_number = get_long("Card Number: ");
    }
    while (card_number < 1); // preventing 0 and below integers.

    if (!check_sum(card_number))
    {
        printf("INVALID\n");
        return 0;
    }

    if (amex_checker(card_number))
    {
        return 0; // already checked with functions
    }
    else if (visa_checker(card_number))
    {
        return 0;
    }
    else if (masterc_checker(card_number))
    {
        return 0;
    }
    else
    {
        printf("INVALID\n");
        return 0;
    }
}

int length(long card_number) // for credit card length
{
    int len = 0;
    while (card_number > 0)
    {
        card_number /= 10;
        len++;
    }
    return len;
}

int amex_checker(long card_number)
{
    int len = length(card_number);
    long first_two_digit = card_number;

    while (first_two_digit >= 100)
    {
        first_two_digit /= 10;
    }
    if ((first_two_digit == 34 || first_two_digit == 37) && len == 15)
    {
        printf("AMEX\n");
        return 1;
    }
    return 0;
}

int visa_checker(long card_number)
{
    int len = length(card_number);
    long first_two_digit = card_number;

    while (first_two_digit >= 10)
    {
        first_two_digit /= 10;
    }
    if (first_two_digit == 4 && (len == 13 || len == 16))
    {
        printf("VISA\n");
        return 1;
    }
    return 0;
}

int masterc_checker(long card_number)
{
    int len = length(card_number);
    long first_two_digit = card_number;

    while (first_two_digit >= 100)
    {
        first_two_digit /= 10;
    }
    if ((first_two_digit == 51 || first_two_digit == 52 || first_two_digit == 53 ||
         first_two_digit == 54 || first_two_digit == 55) &&
        len == 16)
    {
        printf("MASTERCARD\n");
        return 1;
    }
    return 0;
}

int check_sum(long card_number) // checks digits
{
    int sum = 0;
    int counter = 0;
    while (card_number > 0)
    {
        int digit = card_number % 10;
        if (counter % 2 == 1) // EVERY OTHER
        {
            digit *= 2;

            if (digit > 9)
            {
                digit = (digit / 10) + (digit % 10);
            }
        }

        sum += digit;
        card_number /= 10;
        counter++;
    }
    return (sum % 10 == 0); // if true it is valid.
}
