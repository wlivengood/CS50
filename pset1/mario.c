#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height, i, j;
    do
    {
        printf("Give me a height between 1 and 23: ");
        height = GetInt();
        if (height == 0)
            return 0;
    }
    while (height < 1 || height > 23);

    for (i = 0; i < height; i++)
    {
        for (j = 0; j < height - i - 1; j++)
            printf(" ");
        for (j = 0; j < i + 2; j++)
            printf("#");
    printf("\n");
    }
}