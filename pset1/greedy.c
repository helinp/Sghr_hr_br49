#include <stdio.h>
#include <cs50.h>
int main(void)
{
    // declare variables
    float owed = 0;

    // loop until valid user input 
    do 
    {
        printf("How much change is owed?\n");
        owed = GetFloat();
    }
    while (owed <= 0);
    
    // addition avoids 0.999... result
    owed = (owed * 100) + 0.0001;    
      
    int c25 = owed / 25;
    int c10 = (owed - (c25 * 25)) / 10;
    int c05 = (owed - (c25 * 25) - (c10 * 10)) / 5 ;
    int c01 = owed - (c25 * 25) - (c10 * 10) - (c05 * 5);
       
    int totalCoins = c25 + c10 + c05 + c01;
    
    // debug
    /** 
    printf("%i\n", c25);
    printf("%i\n", c10);
    printf("%i\n", c05);
    printf("%i\n", c01);
    */
    
    printf("%i\n", totalCoins);
    
}
