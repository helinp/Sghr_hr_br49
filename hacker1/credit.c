#include <stdio.h>
#include <cs50.h>
#include <math.h>

void print_type();
bool chk_card_num();
int card_lenght();
int get_digit_n();

int main(void)
{
    // -1 as true condition for the loop
    long long card_number = -1;

    // asks for user input
    do
    {
        printf("Please insert your credit card number: ");
        card_number = GetLongLong();
    }
    while (card_number <= -1); 
       
    // Variables for human visibility
    int first_digit = get_digit_n(card_number, 1);
    int second_digit = get_digit_n(card_number, 2);
    
    // Calls functions to check card number    
    if (chk_card_num(card_number)) 
        print_type(first_digit, second_digit);
    else 
        printf("INVALID\n");

}

int get_digit_n(long long digit, int n)
{
    char str_digit[18] = "";
     
    // convert long long to string
    sprintf(str_digit, "%lld", digit);

    // convert char to int
    return (int) str_digit[n - 1] - 48;
     
    /**
    
    // Code above doesn't work with numbers > 15 digits
    
    // avoids division by 0 error
    if (n != 0) 
    {
        n = pow(10,n); 
        printf("%lld -- %lld -> %lld\n", digit, n, (digit % n) / (n / 10));
        return (digit % n) / (n / 10);
    }
    else 
        return 0;
    */
}

int card_lenght(long long digit)
{
    int lenght = 1;
    
    for(long long i = 1 ; digit >= i ; i = i * 10)
    {
        lenght++;
    }
    
    return lenght - 1;
}

bool chk_card_num(long long card)
{
    // Very important to assign 0 value
    int sum [3] = {0};
    
    int cl = card_lenght(card);
    
    // Sums _x digits
    for (int i = cl ; i >= 1 ; i -= 2)
    {
        sum[1] += get_digit_n(card, i);
    }
    
    // Sums x_ digits and multibly by 2
    for (int i = cl - 1; i >= 1 ; i -= 2)
    {
        int dig = get_digit_n(card, i) * 2;
        
        if (dig > 9)
            sum[2] += get_digit_n(dig, 1) + get_digit_n(dig, 2);
        else
            sum[2] += dig;   
    }
    
    
    // checks validity and returns boolean
    sum[0] = sum[1] + sum[2];

    if (get_digit_n(sum[0], 2) == 0) 
        return true;
    else 
        return false;
}


void print_type(int frs_digit, int sec_digit)
{
    
    switch (frs_digit)
    {
        case 5:
            if (sec_digit <= 5 && sec_digit != 0) 
            {
                printf("MASTERCARD\n");
                break;
            }
            
        case 4: 
            printf("VISA\n");
            break;
            
        case 3:
            if (sec_digit == 4 | sec_digit == 7) 
            {
                printf("AMEX\n");
                break;
            }

        default: 
            printf("INVALID\n");
    }
}

