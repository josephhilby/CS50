#include <cs50.h>
#include <stdio.h>

bool prime(int number);

int main(void)
{
    int min;
    do
    {
        min = get_int("Minimum: ");
    }
    while (min < 1);

    int max;
    do
    {
        max = get_int("Maximum: ");
    }
    while (min >= max);

    for (int i = min; i <= max; i++)
    {
        if (prime(i))
        {
            printf("%i\n", i);
        }
    }
}

bool prime(int number)
{
    bool result;
    // If num <= 1 return false
    if (number <= 1)
    {
        result = false;
    }
    // If num = 2 OR 3 return true
    else if (number == 2 || number == 3)
    {
        result = true;
    }
    // If num > 2 AND num % 2 == 0 return false
    else if (number > 2 && number % 2 == 0)
    {
        result = false;
    }
    // If num > 3 AND num % 3 == 0 return false
    else if (number > 3 && number % 3 == 0)
    {
        result = false;
    }
    // If num > 5 AND num % 5 == 0 return false
    else if (number > 5 && number % 5 == 0)
    {
        result = false;
    }
    // If num > 7 AND num % 7 == 0 return false
    else if (number > 7 && number % 7 == 0)
    {
        result = false;
    }
    // Else true
    else
    {
        result = true;
    }
    return result;
}
