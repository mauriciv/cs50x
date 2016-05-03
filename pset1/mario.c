#include <stdio.h>
#include <cs50.h>

int main() {
    int rowCount;

    do {
        printf("Please enter the number of rows for the half-pyramid,\n");
        printf("it has to be greater than 0 and smaller than 23\n");
        rowCount = GetInt();
    } while(rowCount < 0 || rowCount > 23);

    int numberOfSpaces = rowCount - 1;

    for (int row = 1; row <= rowCount; row++) {
        for (int column = 1; column <= (row + 1); column++) {
            printf("#");
        }
        printf("\n");
    }
    return 0;
}
   ##
  ###
 ####
#####
