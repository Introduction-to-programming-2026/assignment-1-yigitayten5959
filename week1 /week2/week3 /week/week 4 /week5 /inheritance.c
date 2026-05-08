// CS50x Week 5 — Lab: Inheritance
// Simulate the inheritance of blood types across three generations.

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Each person has two parents and two alleles
#define GENERATIONS 3
#define INDENT_LENGTH 4

typedef struct person
{
    struct person *parents[2];   // NULL if no parents
    char alleles[2];             // 'A', 'B', or 'O'
} person;

// Function prototypes
person *create_family(int generations);
void free_family(person *p);
void print_family(person *p, int generation);
char random_allele(void);

int main(void)
{
    // Seed the random number generator
    srand(time(0));

    // Create a new family with three generations
    person *p = create_family(GENERATIONS);

    // Print the family tree of blood types
    print_family(p, 0);

    // Free memory allocated for the family
    free_family(p);

    return 0;
}

/**
 * create_family
 * -------------
 * Recursively creates a family tree.
 * Base case: If generations == 1, create a person with no parents and random alleles.
 * Recursive step: Create a person, recursively create their parents, 
 * and inherit one allele from each parent.
 */
person *create_family(int generations)
{
    // Allocate memory for a new person
    person *p = malloc(sizeof(person));
    if (p == NULL)
    {
        return NULL;
    }

    // If there are still generations left to create
    if (generations > 1)
    {
        // Recursively create two parents for the current person
        p->parents[0] = create_family(generations - 1);
        p->parents[1] = create_family(generations - 1);

        // Randomly pick one allele from each parent to inherit
        p->alleles[0] = p->parents[0]->alleles[rand() % 2];
        p->alleles[1] = p->parents[1]->alleles[rand() % 2];
    }
    // Base case: Oldest generation (no parents)
    else
    {
        // Set parents to NULL
        p->parents[0] = NULL;
        p->parents[1] = NULL;

        // Assign random alleles
        p->alleles[0] = random_allele();
        p->alleles[1] = random_allele();
    }

    // Return the newly created person
    return p;
}

/**
 * free_family
 * -----------
 * Recursively frees all memory in the family tree.
 * Uses post-order traversal to ensure parents are freed 
 * after their pointers are used to find the grandparents.
 */
void free_family(person *p)
{
    // Base case: if person is NULL, nothing to free
    if (p == NULL)
    {
        return;
    }

    // Recursively free the parents first
    free_family(p->parents[0]);
    free_family(p->parents[1]);

    // Free the current person
    free(p);
}

/**
 * print_family
 * ------------
 * Prints the family tree, indented by generation.
 */
void print_family(person *p, int generation)
{
    if (p == NULL)
    {
        return;
    }

    // Print parents
