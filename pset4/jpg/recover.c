/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */

 #include <stdio.h>
 #include <stdlib.h>

 typedef int bool;
 #define true 1
 #define false 0

 bool is_valid_4th_byte(char c);

 char bytes[16]= {0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9, 0xea,
                0xeb, 0xec, 0xed, 0xee, 0xef};

int main(int argc, char* argv[])
{
    FILE* card = fopen("card.raw", "r");
    if (card == NULL) {
        fprintf(stderr, "Could not open file 'card.raw'\n");
        return 1;
    }

    unsigned char* buffer = malloc(512);
    bool already_found_a_jpeg = false;
    int jpeg_number = 0;
    FILE* img;
    // While there are still unread blocks in the file
    while (fread(buffer, 512, 1, card) == 1) {
        if (*buffer == 0xff && *(buffer+1) == 0xd8 && *(buffer+2) == 0xff && is_valid_4th_byte( *(buffer+3) )) {
            char title[10];
            if (already_found_a_jpeg) {
                fclose(img);
                sprintf(title, "%03d.jpg", jpeg_number);
                jpeg_number++;
                img = fopen(title, "a");
                if (img == NULL) {
                    printf("Could not create %s\n", title);
                }
                // Write the first 512 bytes of the image
                fwrite(buffer, 512, 1, img);
            } else { // The first jpeg found
                already_found_a_jpeg = true;
                sprintf(title, "%03d.jpg", jpeg_number);
                jpeg_number++;
                img = fopen(title, "a");
                if (img == NULL) {
                    printf("Could not create %s\n", title);
                }
                // Write the first 512 bytes of the image
                fwrite(buffer, 512, 1, img);
            }
        } else if (already_found_a_jpeg) {
            fwrite(buffer, 512, 1, img);
        }
    }



    free(buffer);
    fclose(img);
    fclose(card);
    return 0;
}

bool is_valid_4th_byte(char c){
    for (int i = 0; i < 16; i++) {
        if (c == bytes[i]) {
            return true;
        }
    }
    return false;
}
