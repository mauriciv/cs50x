#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <cs50.h>

bool onlyhasletters(string s);
bool isuppercase(char c);
bool islowercase(char c);
bool isletter(char c);
string tolowercase(string s);

int main(int argc, string argv[]) {

    if (argc != 2) {
        printf("Please enter one and only one keyword\n");
        return 1;
    } else if (!onlyhasletters(argv[1])){
        printf("The key can only have alphabetic characters\n");
        return 1;
    }

    string message = GetString();
    string encryptedMessage = message;

    string key = argv[1];

    key = tolowercase(key);

    int length = strlen(message);
    int nonlettercount = 0;
    for (int i = 0; i < length; i++) {


        if (isletter(message[i])){
            // Figure out which char of the key we need to use
            int keypos = (i - nonlettercount) % strlen(key);
            int offset = key[keypos] - 97;

            char newLetter = '0';
            if (isuppercase(message[i])) {
                int position = (message[i] + offset) % (26 + 65);

                if (position < 65){
                    position += 65;
                }

                newLetter = position ;
                encryptedMessage[i] = newLetter;

            } else if (islowercase(message[i])) {
                int position = (message[i] + offset) % (26 + 97);

                if (position < 97){
                    position += 97;
                }

                newLetter = position;
                encryptedMessage[i] = newLetter;
            }

        } else {
            nonlettercount++;
        }

    }
    printf("%s\n", encryptedMessage);
    return 0;
}

bool onlyhasletters(string s){
    int length = strlen(s);
    for (int i = 0; i < length; i++){
        if (!isletter(s[i])) {
            return false;
        }
    }
    return true;
}

bool isletter(char c){
    return isuppercase(c) || islowercase(c);
}

bool isuppercase(char c){
    return c >= 65 && c <= 90;
}

bool islowercase(char c){
    return c >= 97 && c <= 122;
}

string tolowercase(string s){
    int length = strlen(s);

    for (int i = 0; i < length; i++) {
        if (isuppercase(s[i])) {
            s[i] += 32;
        }
    }
    return s;
}
