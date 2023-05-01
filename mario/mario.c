#include <cs50.h>
#include <stdio.h>

int get_height(void);
void print_pyramid(int size);

int main(void)
{
    // Get heigth as an int from the user
    int n = get_height();

    // Return the pyramid
    print_pyramid(n);
}

int get_height(void)
{
    int n;
    do
    {
        n = get_int("Size: ");
    }
    // Limit the height from 1 - 8
    while (n > 8 || n < 1);
    return n;
}

void print_pyramid(int size)
{
    // Loop through rows to create pyramid
    for (int i = 0; i < size; i++)
    {
        // Create a given row
        // Create leading whitespace and blocks for first half
        for (int j = 0; j < size; j++)
        {
            if (j < size - (i + 1))
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }
        }
        // Create space between each half of the pyramid
        printf("  ");
        // Create blocks for second half
        for (int k = 0; k < size; k++)
        {
            if (k <= i)
            {
                printf("#");
            }
        }
        printf("\n");
    }
}

// //Answer in class for only one pyramid
// void print_pyramid(int n)
// {
//   for (int i = 0; i < n; i++)
//   {
//     for (int j = 0; j < i; j++)
//     {
//       printf("#");
//     }
//     printf("\n");
//   }
// }

// // Recursive solution
// void draw(int n);

// int main(void)
// {
//   int height = get_int("Height: ");
//   draw(height)
// }

// void draw(int n)
// {
//   // Base case
//   // The recursion will continue until n is less than or equal to 0 then all the recursive calls will be made.
//   if (n <= 0)
//   {
//     return;
//   }
//   // Recursive case
//   draw(n - 1);

//   // Draw row of n hashes
//   for (int i = 0; i < n)
//   {
//     printf("#");
//   }
//   printf("\n");
// }