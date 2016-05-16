/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    int i = 0;
    int j = n - 1;
    int midpoint = (i + j)/2;
    if (n < 1)
    {
        return false;
    }
    while (i <= j)
    {
        if (values[midpoint] == value)
            return true;
        else if (values[midpoint] > value)
        {
            j = midpoint - 1;
        }
        else
        {
            i = midpoint + 1;
        }
        midpoint = (i + j)/2;
    }
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (values[j] > values[j + 1])
                {
                    int swap = values[j];
                    values[j] = values[j + 1];
                    values[j + 1] = swap;
                }
        }
    }
    return;
}