/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize n infile outfile");
        return 1;
    }
    
    if (*argv[1] > 100)
    {
        printf("Abording... n must be in [1, 100] range!");
        return 2;  
    }

    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];
    
    // transform ASCII to int and remember size 
    int resize = atoi(argv[1]);
    
    
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
        return 5;
    }

    // determine padding for scanlines
    int padding_new =  (4 - (bi.biWidth * sizeof(RGBTRIPLE) * resize) % 4) % 4;
    int padding_old =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    /**
     * DEBUG
     *
    printf("OLD VALUES\n----------\n");
    printf("bfSize %u\n", bf.bfSize);
    printf("biWidth %u\n", bi.biWidth);
    printf("biHeight %u\n", bi.biHeight);
    printf("biSizeimage %u\n", bi.biSizeImage);
    printf("padding %i, \n", padding_old );
     */

    // Write new header data
    bi.biWidth *= resize;
    bi.biHeight *= resize;
    
    // Size = Headers + RaWmap * padding
    bi.biSizeImage = ((bi.biBitCount / 8) * bi.biWidth * bi.biWidth) 
                     + (padding_new * (0xFFFFFFFF - bi.biHeight + 1));
                
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER)   
              + sizeof(BITMAPINFOHEADER);
    
    /**
     * DEBUG
     *
    printf("\nNEW VALUES\n----------\n");
    printf("resize %i\n", resize);
    printf("bfSize %u\n", bf.bfSize);
    printf("biWidth %u\n", bi.biWidth);
    printf("biHeight %u\n", bi.biHeight);
    printf("biSizeimage %u\n", bi.biSizeImage);
    printf("padding %i, \n", padding_new );
    // printf("biSize %u, \n", bi.biSize);
    
    */
     
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    
    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight) / resize; i < biHeight; i++)
    {
        // Write n times lines
        for (int h = 0 ; h < resize ; h++)
        {
            // iterate over pixels original file in scanline
            for (int j = 0; j < bi.biWidth / resize; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                              
                // Write n times same value (width)
                for (int l = 0 ; l < resize ; l++)
                {
                    // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);  
                }
            }
            
            // skip over padding, if any
            fseek(inptr, padding_old, SEEK_CUR);
                
            // add the new padding
            for (int k = 0; k < padding_new; k++)
            {
                fputc(0x00, outptr); 
            }
             
            // go back to begining of original line to reiterate it -- N - 1
            if (h + 1 < resize)
            {
                // 3 times to get bytes
                fseek(inptr, -((bi.biWidth / resize * 3) 
                + padding_old), SEEK_CUR); 
            }
             
        } 
 
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
