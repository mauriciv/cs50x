#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <cs50.h>

bool isLowercase(char c);
bool comesAfterSpace(string s, int position);


int main() {

    printf("Please enter your name\n");
    string name = GetString();
    string initials = "";

    if (isLowercase(name[0])) {
        initials = initials + (name[0] + 32);
    }

    int n = strlen(name);
    for (int i = 1; i < n; i++) {

        if (comesAfterSpace(name, i) && isLowercase(name[i])){
            initials = initials + name[i] + 32;
        }
        printf("%s\n", name[i]);
    }

    printf("%s\n", initials);

    return 0;
}

bool comesAfterSpace(string s, int position){
    return (s[position-1] == ' ');
}

bool isLowercase(char c){
    return (c >= 'a' && c <= 'z');
}
