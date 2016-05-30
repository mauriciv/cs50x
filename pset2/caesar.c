#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <cs50.h>

int main(int argc, string argv[]) {

    if (argc != 2) {
        printf("Please enter one number\n");
        return 1;
    }
    string message = GetString();
    string encryptedMessage = message;

    int key = atoi(argv[1]) % 26;

    int length = strlen(message);
    for (int i = 0; i < length; i++) {

        char newLetter = '0';
        if (message[i] >= 65 && message[i] <= 90) {
            int position = (message[i] + key) % (26 + 65);
            if (position < 65){
                position += 65;
            }
            newLetter = position ;
            encryptedMessage[i] = newLetter;

        } else if (message[i] >= 97 && message[i] <= 122) {
            int position = (message[i] + key) % (26 + 97);
            if (position < 97){
                position += 97;
            }
            newLetter = position;
            encryptedMessage[i] = newLetter;

        }

    }
    printf("%s\n", encryptedMessage);
    return 0;
}
