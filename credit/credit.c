#include <cs50.h>
#include <stdio.h>

int sum_every_other(long card_number, int digit_count);
int multiply_and_sum_products_every_other(long card_number, int digit_count);
bool check_valid(int sum, int multiply);
void print_result(long card_number, bool valid);
int number_digits(long card_number);

int main(void)
{
    // Validate card
    // Collect input long
    long card_number = get_long("Number: ");

    // Count the number of digits
    int digits = number_digits(card_number);

    // From right to left, starting with the last digit, sum every other number
    int sum = sum_every_other(card_number, digits);

    // From right to left, starting with the SECOND to last digit, multiply each number by 2, sum each result
    int multiply = multiply_and_sum_products_every_other(card_number, digits);

    // Add the two sums togeather
    // If last digit is 0; valid
    // If last digit is NOT 0; INVALID
    bool valid_checksum = check_valid(sum, multiply);

    // If the card passes the checksum determine the the type based off of the first two numbers and total length
    print_result(card_number, valid_checksum);
}

int number_digits(long card_number)
{
    int count = 0;
    do
    {
        card_number /= 10;
        count++;
    }
    while (card_number != 0);
    return count;
}

int sum_every_other(long card_number, int digit_count)
{
    int sum = 0;
    // long reverse_card_number = reverse_number(card_number);
    for (int i = 0; i < digit_count; i++)
    {
        int digit = card_number % 10;
        card_number /= 10;
        if (i % 2 == 0)
        {
            sum += digit;
        }
    }
    return sum;
}

int multiply_and_sum_products_every_other(long card_number, int digit_count)
{
    int sum = 0;
    // long reverse_card_number = reverse_number(card_number);
    for (int i = 0; i < digit_count; i++)
    {
        int digit = card_number % 10;
        card_number /= 10;
        if (i % 2 != 0)
        {
            if (digit * 2 < 10)
            {
                sum += digit * 2;
            }
            else
            {
                int total = digit * 2;
                int digit_one = total % 10;
                int digit_two = total / 10;
                sum += (digit_one + digit_two);
            }
        }
    }
    return sum;
}

bool check_valid(int sum, int multiply)
{
    int total = sum + multiply;
    bool result = false;
    if (total % 10 == 0)
    {
        result = true;
    }
    return result;
}

// Helper function to raise an int to a given exponent
long power(int base, int exp)
{
    long result = 1;
    for (int i = 0; i < exp; i++)
    {
        result *= base;
    }
    return result;
}

void print_result(long card_number, bool valid_checksum)
{
    // If valid, determine type of card
    if (valid_checksum)
    {
        // Count digits
        int digit_count = number_digits(card_number);
        // Find first two digits
        int base = 10;
        int exp = digit_count - 2;
        long denom = power(base, exp);
        int first_two_numbers = card_number / denom;

        // Determine card type off of card length && first two digits
        // AMEX 15 long && first digit 34 or 37
        if (digit_count == 15 && (first_two_numbers == 34 || first_two_numbers == 37))
        {
            printf("AMEX\n");
        }
        // MASTERCARD 16 long && first digit 51, 52, 53, 54, or 55
        else if (digit_count == 16 && (first_two_numbers == 51 || first_two_numbers == 52 || first_two_numbers == 53
                                       || first_two_numbers == 54 || first_two_numbers == 55))
        {
            printf("MASTERCARD\n");
        }
        // VISA 13 or 16 && first digit 4
        else if ((digit_count == 13 || digit_count == 16) && (first_two_numbers / 10 == 4))
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}