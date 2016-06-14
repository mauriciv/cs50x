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
#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    if (n < 1){
        return false;
    }
    for (int i = 0; i < n; i++) {
        if (values[i] == value){
            return true;
        }
    }
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // Selection sort
    for (int i = 0; i < n; i++) {

        int lowestnum = values[i];
        int lowestpos;

        for (int j = i; j < n; j++) {

            if (values[j] < lowestnum) {
                lowestnum = values[j];
                lowestpos = j;
            }

        }
        if (lowestnum != values[i]) {
            values[lowestpos] = values[i];
            values[i] = lowestnum;
        }
        printf("%i\n", values[i]);
    }

    return;
}
