#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    // asks for user plaintext
    string name = GetString();
        
    if (name != NULL)
    {
        // prints first char as first initial
        printf("%c", toupper(name[0]));
          
        // loop to get each char
        for (int i = 0, n = strlen(name) ; i < n ; i++)
        {
            // gets first char after space
            if ((int) name[i] == 32)
            {
                printf("%c", toupper(name[i + 1]));
            }
        }
        printf("\n");
        return 0;
    }
    else
    {
        return 1;
    }
   
}


