#include <cs50.h>
#include <stdio.h>

int main(void)
{
    printf("How many minutes did you spend in the shower?\n");
    int n = GetInt();
    printf("bottles: %i\n", n*12);
}
