#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    if (argc != 2) //check that 1 & only 1 string is entered at command line
    {
        printf("Please provide a key\n");
        return 1;
    }
    string k = argv[1]; //get key
    for (int x = 0, keylength = strlen(k); x < keylength; x++)
    //check k is alphabetic
    {
      if (!isalpha(k[x])) 
        {
        printf("Please provide an alphabetic key\n");
        return 1;
        }  
    }
    int keylength = strlen(k);
    string s = GetString(); //get message to be encrypted
    int j = 0; //initialize key index to zero
    for (int y = 0; y < keylength; y++) //convert key to upper
    {
        if (islower(k[y]))
        {
            k[y] = toupper(k[y]);
        }
    }
    for (int i = 0, n = strlen(s); i < n; i++) //loop over message
    {
        if (isalpha(s[i]))
        {
            if (isupper(s[i])) //encrypt uppers and increment key index
            {
                printf("%c", ((s[i] - 65 + (k[j % keylength] - 65)) % 26) + 65);
                j++;
            }
            else //encrypt lowers and increment key index
            {
                printf("%c", ((s[i] - 97 + (k[j % keylength] - 65)) % 26) + 97);
                j++;
            }
        }
        else //don't encrypt non-alpha chars, don't increment key index
        {
        printf("%c", s[i]);
        }
    }
    printf("\n");
    return 0;
}