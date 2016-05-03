#include <stdio.h>
#include <cs50.h>

int main() {
    int rowCount;

    do {
        printf("Height: ");
        rowCount = GetInt();
        printf("\n");
    } while(rowCount < 0 || rowCount > 23);


    int numberOfSpaces = rowCount - 1;

    for (int row = 1; row <= rowCount; row++) {

        for (int space = 0; space < numberOfSpaces; space++) {
            printf(" ");
        }

        for (int column = 1; column <= (row + 1); column++) {
            printf("#");
        }
        printf("\n");
        numberOfSpaces--;

    }
    return 0;
}
