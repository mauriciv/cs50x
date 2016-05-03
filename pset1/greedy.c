#include <stdio.h>
#include <cs50.h>

int main() {
    int change;

    do {
        printf("How much change is owed?\n");
        change = GetFloat();
    } while(change < 0);

    return 0;
}
