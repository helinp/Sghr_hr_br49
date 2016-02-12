#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void cipherfy();

int main(int argc, string argv[])
{
    if (argv[1] == NULL | argv[2] != NULL)
    {
        printf("Hey, you forgot the key!\n");
        return 1;
    }
        
    // gets the key ant contains it in 1-26 range
   
   string k = argv[1];
   for (int i = 0, n = strlen(k); i < n; i++)
    {
       printf("%i\n", (int) k[i]);
    }
    
    
}
