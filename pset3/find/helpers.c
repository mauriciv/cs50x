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
    return binarysearch(value, values, 0, n-1);
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
    }

    return;
}

bool binarysearch(int searchedvalue, int values[], int min, int max){

    if (max < min) {
        return false;
    }
    int pos = (min + max) / 2;
    if (values[pos] < searchedvalue) {
        return binarysearch(searchedvalue, values, pos + 1, max);
    } else if (searchedvalue < values[pos]) {
        return binarysearch(searchedvalue, values, min, pos - 1);
    } else {
        return true;
    }

}
