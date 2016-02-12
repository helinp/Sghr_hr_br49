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

int main(int argc, char* argv[])
{
    /**
     * COMMAND LINE VERSION
     *
     
    if (argc != 2)
    {
        printf("Usage: recover file\n");
        return 1;
    }
    
    // save filename
    char* infile = argv[1];
    
    // open input file 
    FILE* filein = fopen(infile, "r");
    
     */
    
    // open input file
    FILE* filein = fopen("card.raw", "r");
   
    // sanity check
    if (filein == NULL)
    {
        printf("File not found!\n");
        return 2;
    }
    
    // declare variables   
    unsigned header[5] = {0xff, 0xd8, 0xff, 0xe0, 0xe1};
    unsigned char buffer[512];
    int count = -1;
    char output[12];
    FILE* fileout = NULL;
    
    // read file
    while (fread(&buffer, 1, 512, filein)!=0)
    {
              
        // find jpeg header
        if (buffer[0] == header[0] && buffer[1] == header[1] 
        && buffer[2] == header[2] && (buffer[3] == header[3] 
        || buffer[3] == header[4]))
        {
            // close former file
            if (count >= 0)
            {
                fclose(fileout);
            }
            // increment filename
            count++;
            
            // create ouput files 
            sprintf(output, "%03i.jpg", count);
            // printf("Header found! Saving %s...\n", output);
            fileout = fopen(output, "w");
        } 
                
        // open output file
        if (fileout == NULL && count >= 0)
        {
            fclose(filein);
            printf("Could not create %c.\n", *output);
            return 3;
        }
        else if (count >= 0)
        { 
            fwrite(&buffer, 512, 1, fileout);
        }
    }    

    // close opened files
    fclose(fileout);                         
    fclose(filein); 
    
    // printf("Job completed!\n");    
    return 0;
    
}
