/* Goldbach: elegxos protwn kai anazitisi anaparastasis Goldbach.
 * Pigi: dokimi me diairesi (trial division) mexri sqrt(n), 6.000 vimata max. */
#include <stdio.h>
#include <stdlib.h>

#define MAXN 10000000000ULL

static int is_prime(unsigned long long n)
{
    unsigned long long i;

    if (n < 2)
        return 0;
    if (n < 4)
        return 1;
    if (n % 2 == 0)
        return 0;
    for (i = 3; i * i <= n; i += 2)
        if (n % i == 0)
            return 0;
    return 1;
}

static void goldbach(unsigned long long n)
{
    unsigned long long p;

    if (n <= 2 || n % 2 != 0) {
        printf("Goldbach's conjecture is applicable only to even numbers greater than 2!\n");
        return;
    }
    for (p = 2; p <= n / 2; p++) {
        if (is_prime(p) && is_prime(n - p)) {
            printf("%llu = %llu + %llu\n", n, p, n - p);
            return;
        }
    }
    printf("%llu is a counterexample to Goldbach's conjecture!\n", n);
}

static int is_space(int c)
{
    return c == ' ' || c == '\n' || c == '\t' || c == '\r' || c == '\v' || c == '\f';
}

static void fail(const char *msg)
{
    fprintf(stderr, "%s\n", msg);
    exit(1);
}

static void eof_exit(void)
{
    printf("EOF detected, exiting\n");
    exit(0);
}

int main(void)
{
    int c, neg, digits, len, i;
    char buf[8];
    unsigned long long n;

    for (;;) {
        printf("Give me a number: ");

        /* Anagnosi akeraiou */
        c = getchar();
        while (c != EOF && is_space(c))
            c = getchar();
        if (c == EOF)
            eof_exit();

        neg = 0;
        if (c == '-' || c == '+') {
            neg = (c == '-');
            c = getchar();
        }
        n = 0;
        digits = 0;
        while (c >= '0' && c <= '9') {
            digits++;
            if (n <= MAXN)          /* otan ksepernaei to orio menei > MAXN */
                n = n * 10 + (unsigned long long)(c - '0');
            c = getchar();
        }
        if (digits == 0 || (c != EOF && !is_space(c)))
            fail("Invalid input: expected an integer");
        if ((neg && n > 0) || n > MAXN)
            fail("Number should be in the range [0, 10000000000]");

        printf("Choose how to test %llu - ('p' for prime, 'g' for goldbach) ", n);

        /* Anagnosi epilogis (mporei na einai kai "pg") */
        while (c != EOF && is_space(c))
            c = getchar();
        if (c == EOF)
            eof_exit();

        len = 0;
        while (c != EOF && !is_space(c)) {
            if (len < 8)
                buf[len] = (char)c;
            len++;
            c = getchar();
        }
        if (len > 8)
            fail("Invalid choice: expected 'p' or 'g'");
        for (i = 0; i < len; i++)
            if (buf[i] != 'p' && buf[i] != 'g')
                fail("Invalid choice: expected 'p' or 'g'");

        for (i = 0; i < len; i++) {
            if (buf[i] == 'p')
                printf("%llu is%s prime\n", n, is_prime(n) ? "" : " not");
            else
                goldbach(n);
        }
    }
    return 0;