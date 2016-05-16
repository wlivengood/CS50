#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    float change;
    int q, d, n, p, cents, coins;
    do
    {
            printf("How much change do you need?: ");
            change = GetFloat();
    }
    while (change < 0);
    
    cents = round(change * 100);
    
    q = cents / 25;
    
    d = (cents % 25) / 10;
    
    n = ((cents % 25) % 10) / 5;
    
    p = (((cents % 25) % 10)) % 5;
    
    coins = q + d + n + p;
    
    printf("%i\n", coins);
}