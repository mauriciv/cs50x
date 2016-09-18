#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize size infile outfile\n");
        return 1;
    }

    int size_multiplier = atoi(argv[1]);
    if (size_multiplier == 0) {
        printf("Error. size must be a number\n");
        return 1;
    }


    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // determine padding for scanlines, in 'pixels'
    int original_padding =  (( bi.biWidth * sizeof(RGBTRIPLE) ) % 4) * 3;

    int original_height = bi.biHeight;
    bi.biHeight = bi.biHeight * size_multiplier;

    int original_width = bi.biWidth;
    bi.biWidth = bi.biWidth * size_multiplier;
    // The amount of bytes to insert after each scanline in the new image
    int new_padding = (( bi.biWidth * sizeof(RGBTRIPLE) ) % 4) * 3;

    int pixel_count = abs(bi.biHeight) * bi.biWidth;
    bi.biSizeImage = pixel_count * sizeof(RGBTRIPLE) + (new_padding * abs(bi.biHeight));
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);


    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(original_height); i < biHeight; i++)
    {

        RGBTRIPLE pixels[bi.biWidth];
        int last_free_cell = 0;

        // iterate over pixels in scanline
        for (int j = 0; j < original_width; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            // Loop for storing the pixel in the array "size_multiplier" times
            for (int repeated_column = 0; repeated_column < size_multiplier; repeated_column++) {
                pixels[last_free_cell] = triple;
                last_free_cell++;
            }

        }

        for (int repeated_row = 0; repeated_row < size_multiplier; repeated_row++) {
            for (int pixel = 0; pixel < bi.biWidth; pixel++) {
                // write RGB triple to outfile
                fwrite(&pixels[pixel], sizeof(RGBTRIPLE), 1, outptr);
            }
            // add padding
            for (int k = 0; k < new_padding; k++) {
                fputc(0x00, outptr);
            }
        }

        // skip over padding, if any
        fseek(inptr, original_padding, SEEK_CUR);

    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
