#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt user for a credit card number
    long number = get_long("Number: ");
    long temp_number = number;
    
    // STEP 1: Count the number of digits
    int length = 0;
    while (temp_number > 0)
    {
        temp_number /= 10;
        length++;
    }

    // STEP 2: Apply Luhn's Algorithm
    int sum_doubled = 0;
    int sum_rest = 0;
    temp_number = number;

    for (int i = 0; i < length; i++)
    {
        int digit = temp_number % 10;
        
        // If position i is ODD (starting from 0 at the end), it's every other digit starting from second-to-last
        if (i % 2 != 0)
        {
            int product = digit * 2;
            // Add the digits of the product (e.g., 12 -> 1 + 2 = 3)
            sum_doubled += (product % 10) + (product / 10);
        }
        else
        {
            sum_rest += digit;
        }
        temp_number /= 10;
    }

    // STEP 3: Check validity
    if ((sum_doubled + sum_rest) % 10 != 0)
    {
        printf("INVALID\n");
        return 0;
    }

    // STEP 4: Identify card type
    // Get the first two digits
    long first_two = number;
    while (first_two >= 100)
    {
        first_two /= 10;
    }

    // Check conditions for AMEX, MASTERCARD, VISA
    if (length == 15 && (first_two == 34 || first_two == 37))
    {
        printf("AMEX\n");
    }
    else if (length == 16 && (first_two >= 51 && first_two <= 55))
    {
        printf("MASTERCARD\n");
    }
    else if ((length == 13 || length == 16) && (first_two / 10 == 4))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}
