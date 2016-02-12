#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // declare variables
    int height = -1;
    
    // define printed characters so they can be changed easily
    string block = "#";
    string space = " ";
    
    // set number of blocks at top 
    int top_blocks = 1;
    
    // ask for user input until gets a number from 0 to 23
    do
    {
        printf("height: ");
        height = GetInt();
    }
    while (height <= -1 | height > 23);  
    
    // prints line by line adding the return character 
    for (int d = height; d > 0 ; d--)
    {
        // prints spaces 
        for (int d_spaces = d;d_spaces > 1 ; d_spaces--)
        {
            printf("%s", space);    
        }
        
        // prints blocks
        for (int n = 0 ; n < 2 ; n++)
        {
            for (int n_blocks = -top_blocks;n_blocks < (height - d) ; n_blocks++)
            {
                printf("%s", block);    
            }
            // avoids printing useless spaces
            if (n == 1) 
                break;
            
            // prints space between stairs
            printf("  ");
        }   
        
        printf("\n");
          
    }
    return 0;
}
