#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void cipherfy(int i_key, char c_plain);

int main(int argc, string argv[])
{
    // is only one argument present?
    if (argc != 2)
    {
        printf("\"Il n'y a rien de plus beau qu'une clef, tant qu'on ne sait pas ce qu'elle ouvre.\"\nMaurice Maeterlinck\n");
        return 1;
    }
    
    // gets the key from command line
    string key = argv[1];
    int lenght = strlen(key);
    int c_plain[lenght];
    
    // converts ASCII to array int and range 1 - 24
    for (int i = 0; i < lenght; i++)
    {
        if (isupper(key[i]))
        {
            c_plain[i] = (int) key[i] - 65;
        }
           
        else if (islower(key[i]))
        {
            c_plain[i] = (int) key[i] - 97;
        }
       
        else
        {
            printf("Hey, only alphas allowed!\n");
            return 1;
        }  
     }
    
    // waits for user plaintext
    string plain = NULL;
    do
    {
        plain = GetString();
    }
    while (plain == NULL);  
    
    // prints encrypted output char by char in vigenere way
    for (int i = 0, j = 0, n = strlen(plain) ; i < n ; i++, j++)
    {
        if (j == lenght)
        {
            j = 0;
        }
        
        /**
         * Prints no-alpha(numeric) characters in plain
         * without iterate the key array
         *
         */
        if (!isalpha(plain[i]) && !isalnum(plain[i])) 
        {
            printf("%c", plain[i]);
            j--;
        }
        else 
        {
            cipherfy(c_plain[j], plain[i]);
        }
    }
    
    printf("\n");
    
    return 0;
       
}

void cipherfy(int i_key, char c_plain)
{
    // uppercase 65 to 90
    if (isupper(c_plain))
    {
        // loops the cipher in the A - Z range
        if (i_key + c_plain > 90)
        {
            printf("%c", c_plain + i_key - 26);
        }
        else
        {
            printf("%c", c_plain + i_key);
        }
    }
        
    // lowercase 97 to 122
    else if (islower(c_plain))
    {
        // loops the cipher within the A - Z range
        if (i_key + c_plain > 122)
        {
            printf("%c", c_plain + i_key - 26);
        }
        else
        {
            printf("%c", c_plain + i_key);
        }
    }
    // digits 48 to 57
    else if (isalnum(c_plain))
    {
        // loops the cipher within the 0 - 9 range
        if (i_key + c_plain > 57)
        {
            printf("%c", c_plain + i_key - 10);
        }
        else
        {
            printf("%c", c_plain + i_key);
        }
     }
        
}

