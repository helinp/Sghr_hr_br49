/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <math.h>
#include "dictionary.h"

// maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45

// number of letters in prefixes 
#define PREFIX_LEN 4

typedef struct node
{
    char word[LENGTH + 1];
    struct node* next;
}
node;


// creates linked list
node* head[38383838] = {NULL};
node* curr = NULL;

long unload_index[810000] = {0};
long dic_len = 0;

// prototypes
node* create_list(char* word1, int index);
node* insert(char* word, int index);
long long hashe(char* word);
char* trim(char *s);

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{

    // Declares variables
    char prefix[PREFIX_LEN] = {0};
    // char debug[50] ;
    char word_tmp[50] = {0};
    char search_tmp[50] = {0} ;
    // char* debug = NULL;
    long long hash = 0;
    
    // Gets prefix
    sprintf(word_tmp, "%s", word);
    sprintf(prefix, "%.*s", PREFIX_LEN , word);
    
    // Hashes it 
    hash = hashe(trim(prefix));
    // printf("%lli ",hash);
    
    // Searches in array
    if (head[hash] != NULL)
    {
        // Searches in node
        node* search = head[hash];
                
        while (search != NULL)
        {             
            sprintf(search_tmp, "%s", trim(search->word));
            // sprintf(debug, "searchptr:%s-word:%s-\n", search_tmp, word_tmp);
            // printf("%s",search_tmp);
            
            if (strcasecmp(word_tmp, search_tmp) == 0)
            {
                // printf(" correct *%s*%s*\n", search_tmp, word_tmp);
                return true;
            }
            
            search = search->next;
            
        } 
        
        // printf(" incorrect *%s*%lli*\n", search_tmp, hash); 
        return false;
    
    }
    else 
    {
        // printf(" incorrect *%s*%lli*\n", search_tmp, hash);
        return false;
    }
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{

    // declares variables
    char word[LENGTH + 1] = "";
    char prefix[PREFIX_LEN + 1] = ""; 
    char *word_tmp = malloc(sizeof(char) * (LENGTH + 1));
    char *prefix_tmp =  malloc(sizeof(char) * (LENGTH + 1));
    int n_prefixes = 0;
    long long i = 0;
    
    // open dictionary
    FILE* dic = fopen(dictionary, "r");

    // dictionary NULL check
    if (dic == NULL) 
    {
        printf("Error: file pointer is null.");
        return false;
    }
 
    
    /**
     *  SEPARATE CHAINING
     *
     */
     

    // Reads dictionary until EOF
    while (true)
    {
        // reads line by line
        fgets(word, LENGTH + 1, dic);
        
        if (feof(dic))
        {
            break;
        }
        
        if (isalpha(word[0]))
        {
            dic_len++;
        
                                    
            // TODO: understand why strcpy changes source var too
            strcpy(word_tmp, trim(word));
            // printf("WORD1 %s\n", word);
                                    
            // get prefix from line
            sprintf(prefix, "%.*s\n", PREFIX_LEN, word);
            
            
            // TODO avoid use of trim()              
            if (strcasecmp(trim(prefix), trim(prefix_tmp)) != 0 )
            {
                n_prefixes = hashe(prefix);
                
                // store index to free
                unload_index[i] = n_prefixes;
                i++;   
                
                // saves prefixe as head
                strcpy(prefix_tmp, prefix);
                                   
            }
                    
            insert(word_tmp, n_prefixes);          
        } 

    }
   
    // closes file and frees memory
    free(word_tmp);
    free(prefix_tmp);
    fclose(dic);
    return true; 
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return dic_len;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{

    struct node* tmp;
 
    for (long long i = 0 ; unload_index[i] != 0 ; i++)
    {
        while (head[unload_index[i]] != NULL)
        {
            tmp = head[unload_index[i]];
            head[unload_index[i]] = head[unload_index[i]]->next;
            free(tmp);
        }
      
    }
   
    return true;
}

node* create_list(char* word, int index)
{
    
    node* new = (node*) malloc(sizeof(node));
    
    if (new == NULL)
    {
        printf("\n Node creation failed \n");
        return NULL;
    }
    
    strcpy(new->word, word);
    new->next = NULL;

    head[index] = curr = new;
    
    // DEBUG
    // printf("input %d           : %s ", index, word);
    // printf("output create %.3d           : %s\n", index, head[index]->word);
    
    return new;
    
}

node* insert(char* word, int index)
{
    
        // check for empty head
    if (head[index] == NULL)
    {
        return (create_list(word, index));
    }
    
    node* new = (node*) malloc(sizeof(node));
    
    // check NULL
    if (new == NULL)
    {
        printf("\n Node creation failed \n");
        exit(1);
    }    
    
    // new node
    strcpy(new->word, word);
    new->next = NULL;

    // insert at last pos
    curr->next = new;
    curr = new;
    
    // DEBUG
    // printf("output insert %.3d           : %s", index, curr->word);
        
    return new;
}


/**
 * Hashes function. 
 */

long long hashe(char* word)
{

    long long int h = 0;
    int j = 0; 
    int k = strlen(trim(word));
  
    for (int i = 0 ; i < k ; i++)
    {
        // caps check
        j = (int) tolower(word[i]) - 96 + 10;
        
        // hashes apostroph
        if (j == (39 - 96 + 10)) 
        {
            j = 37;
        }
        
        // removes specials char (EOF, CAR, etc))
        if (j < (33 - 96 + 10))
        {
            j = 10;
        }
        
        // reverse hashing 10.10.10
        h += j * pow(100, i);
    }
    
    // hashes space in words with less than 2 char
    if (k < 4) 
    {
        h += (long long) 10000000;
    }
    else if (k < 3) 
    {
        h += (long long) 100000;
    }
    else if (k < 2) 
    {
        h += (long long) 1000;
    }
    
    return h;
}

  
char* trim(char* s)
{
    int i = 0;
    i = strlen (s) - 1;
    
    while (isspace (s[i]))
    {
        i--;
    }  
        
    s[i + 1] = '\0';
   
    return s;
}
