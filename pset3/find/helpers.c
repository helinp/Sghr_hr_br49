/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 *
 * Calling function as it: search(needle, haystack, size haystack)
 *
 */      
#include <cs50.h>
#include <stdio.h>
#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    
    int cursor = 0;
    
    /**
     * Linear search
     *
 
    for (int i = 0 ; i < n ; i++)
    {
        if (values[i] == value)
        {
            cursor = 1;
        }
    }
    
    return (cursor == 0) ? false : true;
       
    */

    /**
     * address book search
     *
     */
   
    // launches search only if value is in range
    if (values[0] <= value && values[n] >= value)
    {
        int min_half_max[3] = {1, n / 2, n};
            
        while (true)
        {
            // debug
            // printf("Search %i, %i, %i\n", min_half_max[0], 
            // min_half_max[1], min_half_max[2]);
                    
            // easy checks
            if (values[min_half_max[0]] == value 
                || values[min_half_max[1]] == value 
                || values[min_half_max[2]] == value)
            {
                cursor = 1;
                break;
            }
                    
                /**
                 *  Binary search
                 *  
                 *
                 */
                     
            // first half
            else if (values[min_half_max[1]] > value)
            {
                // printf("before!\n");
                min_half_max[2] = min_half_max[1];
                min_half_max[1] = (min_half_max[0] + min_half_max[2]) / 2;  
            }
                    
            // second half
            else if (values[min_half_max[1]] < value)
            {
                // printf("after!\n");
                min_half_max[0] = min_half_max[1];
                                 
                min_half_max[1] = min_half_max[0]     
                + ((min_half_max[2] - min_half_max[0]) / 2);
            }
                   
            // last page and not found
            if (min_half_max[0] == min_half_max[1]
                || min_half_max[2] == min_half_max[1])
            {
                cursor = 0;
                break;
            }
                    
        }
    }
    
    return (cursor == 0) ? false : true;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // Bubble sort
    int buffer = 0;
    
    for(int j = 0; j < n ; j++)
    {    
        for(int i = 0; i < n ; i++)
        {
            if (values[i] > values[i + 1])
            {
                // Switches array's values 
                buffer = values[i];
                values[i] = values[i + 1];
                values[i + 1] = buffer;
            }
        }
     }
}
