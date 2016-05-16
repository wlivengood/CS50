#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    string name = GetString();
    printf("%c", toupper(name[0])); //print the first initial
    for (int i = 0, n = strlen(name); i < n; i++) //loop over string
    {
        if (isblank(name[i])) //print character after spaces in upper case
            {
                printf("%c", toupper(name[i + 1]));
            }
    }
    printf("\n");
}