#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void cipherfy();

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("\"Life is rather like a tin of sardines - we're all of us looking for the key.\"\nAlan Bennett\n");
        return 1;
    }
        
    // gets the key ant contains it in 1-26 range
    int key = atoi(argv[1]);
    key = key % 26;
    
    // asks for user plaintext
    string plain = GetString();
    
    if (plain != NULL)
    {  
        // prints encrypted output and exits
        cipherfy(key, plain);
        printf("\n");
        
        return 0;
    } 
    else 
    {
        printf("Hey, something went wrong!\n");
        return 1;
    }  
}

void cipherfy(int fkey, string fplain)
{
    
    for (int i = 0, n = strlen(fplain); i < n; i++)
    {
        // uppercase 65 to 90
        if (isupper(fplain[i]))
        {
            // loops the cipher within the A - Z range
            if (fkey + fplain[i] > 90)
            {
                printf("%c", fplain[i] + fkey - 26);
            }
            else
            {
                printf("%c", fplain[i] + fkey);
            }
        }
        
        // lowercase 97 to 122
        else if (islower(fplain[i]))
        {
            // loops the cipher within the A - Z range
            if (fkey + fplain[i] > 122)
            {
                printf("%c", fplain[i] + fkey - 26);
            }
            else
            {
                printf("%c", fplain[i] + fkey);
            }
        }
        // digits 48 to 57
        else if (isdigit(fplain[i]))
        {
            // loops the cipher within the 0 - 9 range
            if (fkey + fplain[i] > 57)
            {
                printf("%c", fplain[i] + fkey - 10);
            }
            else
            {
                printf("%c", fplain[i] + fkey);
            }
        }
        
        // prints others characters with no cipher
        else 
        {
            printf("%c", fplain[i]);
        }
    }

}
