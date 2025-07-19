// This C program checks the validity of a given credit card number using Luhn's Algorithm

#include <cs50.h>
#include <stdio.h>

// Function prototypes
int checksum(long n);

int main(void)
{
    // Prompts user for credit card number
    long card_num = get_long("Number: ");

    // Compute checksum
    int outcome = checksum(card_num);

    // Check if card is valid
    if (outcome % 10 != 0)
    {
        printf("INVALID\n");
        return 0;
    }

    // Check for card length and starting digit
    bool amex = false;
    bool mastercard = false;
    bool visa = false;

    long num = card_num;
    int digits = 0;

    // Counts number of digits
    while (num > 0)
    {
        num /= 10;
        digits++;
    }

    // Get fist two digits
    long start = card_num;
    while (start >= 100)
    {
        start /= 10;
    }

    int two_digits = (int) start; // using type cast to get int from long
    int first_digit = two_digits / 10;

    // Verify amex
    if (digits == 15 && (two_digits == 34 || two_digits == 37))
    {
        amex = true;
    }

    // Verify mastercard
    if (digits == 16 && (two_digits >= 51 && two_digits <= 55))
    {
        mastercard = true;
    }

    // Verify visa
    if ((digits == 13 || digits == 16) && first_digit == 4)
    {
        visa = true;
    }

    // Print result
    if (amex)
    {
        printf("AMEX\n");
    }
    else if (mastercard)
    {
        printf("MASTERCARD\n");
    }
    else if (visa)
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }

    return 0;
}

// Calculate checksum
int checksum(long n)
{
    int sum = 0;
    long other_n = n;

    // Loop to add every other digit to sum
    while (other_n > 0)
    {
        int other_digit = other_n % 10; // Gets the last digit
        sum += other_digit;
        other_n /= 100;
    }

    n /= 10; // Starts from the second-to-last digit

    // Loop to add every other digit starting from second-to-last digit to sum
    while (n > 0)
    {
        int second_digit = n % 10; // Gets current second digit
        second_digit *= 2;

        while (second_digit != 0)
        {
            int count_digits = second_digit % 10; // Gets individual digit of product
            sum += count_digits;
            second_digit /= 10;
        }
        n /= 100; // Skip one digit (two steps back)
    }
    return sum;
}