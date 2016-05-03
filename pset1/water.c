#include <stdio.h>
#include <cs50.h>

int main()
{
    printf("How long do you take to shower? (in minutes)\n");
    int minutes = GetInt();
    printf("Minutes: %i\n", minutes);
    printf("Bottles: %i\n", minutes*12);
    return 0;
}