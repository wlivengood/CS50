/**
 * resize.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Resizes bmp image by integer factor
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: resize n infile outfile\n");
        return 1;
    }

    int n = atoi(argv[1]);
    char* infile = argv[2]; 
    char* outfile = argv[3];
    
    //ensure n is between 1 and 100
    if (n < 1 || n > 99)
    {
        printf("Number must be between 1 and 100\n");
        return 2;
    }
    
    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 3;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf, rbf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    rbf = bf;

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi, rbi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    rbi = bi;

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 5;
    }
    
    
    //determine new width and height
    rbi.biWidth = bi.biWidth * n;
    rbi.biHeight = bi.biHeight * n;
    
    // determine padding for original and resized bmps
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) %4) % 4;
    int rpadding = (4 - (rbi.biWidth * sizeof(RGBTRIPLE)) %4) % 4;
    
    //determine new image size values for headers
    rbi.biSizeImage = (rbi.biWidth * sizeof(RGBTRIPLE) + rpadding) 
    * abs(rbi.biHeight);
    rbf.bfSize = bf.bfSize - bi.biSizeImage + rbi.biSizeImage;
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&rbf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&rbi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        //read each scanline n times (resize vertically)
        for (int j = 0; j < n; j++)
        {
            // iterate over pixels in scanline
            for (int k = 0; k < bi.biWidth; k++)
            {
                // temporary storage
                RGBTRIPLE triple;
    
                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
    
                // write RGB triple to outfile n times (resize horizontally)
                for (int m = 0; m < n; m++)
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }
            // Add new padding
            for (int m = 0; m < rpadding; m++)
                fputc(0x00, outptr);
            
            // Return to beginning of scanline
            if (j < n - 1)
                fseek(inptr, -bi.biWidth * sizeof(RGBTRIPLE), SEEK_CUR);
        }

        // Skip over old padding, if any
        fseek(inptr, padding, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
