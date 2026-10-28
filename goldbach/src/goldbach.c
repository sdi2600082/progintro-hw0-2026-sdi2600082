/* Goldbach: elegxos protwn kai anazitisi anaparastasis. Pigi: dokimi me diairesi mexri sqrt(n). */
#include <stdio.h>

#define MAXN 10000000000LL

int is_space(int c)
{
    return c == ' ' || c == '\n' || c == '\t' || c == '\r';
}

int is_prime(long long n)
{
    long long i;

    if (n < 2)
        return 0;
    if (n % 2 == 0)
        return n == 2;
    for (i = 3; i * i <= n; i += 2)
        if (n % i == 0)
            return 0;
    return 1;
}


