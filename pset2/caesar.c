#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    if (argc != 2) //check that 1 & only 1 string is entered as CLA
    {
        printf("Please provide a key\n");
        return 1;
    }
    int k = atoi(argv[1]); //get key
    if (k < 1) //ensure key is a positive int
    {
        printf("Please provide a valid key\n");
        return 1;
    }
    string s = GetString();
    for (int i = 0, n = strlen(s); i < n; i++) //loop over message
    {
        if (isalpha(s[i]))
        {
            if (isupper(s[i])) //encrypt uppers
            {
                printf("%c", ((s[i] - 65 + k) % 26) + 65);
            }
            else //encrypt lowers
            {
                printf("%c", ((s[i] - 97 + k) % 26) + 97);
            }
        }
        else //don't encrypt non-alpha chars
        {
        printf("%c", s[i]);
        }
    }
    printf("\n");
    return 0;
}