#include <cs50.h>
#include <stdio.h>

// Function prototypes
int get_cents(void);
int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickels(int cents);
int calculate_pennies(int cents);

int main(void)
{
    // Ask the user how much change is owed
    int cents = get_cents();

    // Calculate the number of quarters to give the customer
    int quarters = calculate_quarters(cents);
    cents = cents - (quarters * 25);

    // Calculate the number of dimes to give the customer
    int dimes = calculate_dimes(cents);
    cents = cents - (dimes * 10);

    // Calculate the number of nickels to give the customer
    int nickels = calculate_nickels(cents);
    cents = cents - (nickels * 5);

    // Calculate the number of pennies to give the customer
    int pennies = calculate_pennies(cents);
    cents = cents - (pennies * 1);

    // Sum the total number of coins
    int coins = quarters + dimes + nickels + pennies;

    // Print the total number of coins
    printf("%i\n", coins);
}

int get_cents(void)
{
    int cents;
    // Prompt user for non-negative integer
    do
    {
        cents = get_int("Change owed: ");
    }
    while (cents < 0);

    return cents;
}

int calculate_quarters(int cents)
{
    // Calculate how many quarters (25c) fit into cents
    return cents / 25;
}

int calculate_dimes(int cents)
{
    // Calculate how many dimes (10c) fit into cents
    return cents / 10;
}

int calculate_nickels(int cents)
{
    // Calculate how many nickels (5c) fit into cents
    return cents / 5;
}

int calculate_pennies(int cents)
{
    // Every remaining cent is 1 penny
    return cents;
}
