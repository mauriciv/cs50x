#include <stdio.h>
#include <math.h>
#include <cs50.h>

int main() {
    float change;

    do {
        printf("How much change is owed?\n");
        change = GetFloat();
    } while(change < 0);

    int numberOfCoins = 0;
    int changeInCents = (int) roundf(change * 100);

    while (changeInCents != 0) {

        if (changeInCents >= 25) {
            changeInCents -= 25;
            numberOfCoins++;
        } else if (changeInCents >= 10) {
            changeInCents -= 10;
            numberOfCoins++;
        } else if (changeInCents >= 5) {
            changeInCents -= 5;
            numberOfCoins++;
        } else {
            changeInCents -= 1;
            numberOfCoins++;
        }
    }

    printf("%i\n", numberOfCoins);

    return 0;
}
