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

void run(char letter, long long n)
{
    long long p;

    if (letter == 'p') {
        if (is_prime(n))
            printf("%lld is prime\n", n);
        else
            printf("%lld is not prime\n", n);
        return;
    }

    /* letter == 'g' */
    if (n <= 2 || n % 2 != 0) {
        printf("Goldbach's conjecture is applicable only to even numbers greater than 2!\n");
        return;
    }
    for (p = 2; p <= n / 2; p++) {
        if (is_prime(p) && is_prime(n - p)) {
            printf("%lld = %lld + %lld\n", n, p, n - p);
            return;
        }
    }
}

int main(void)
{
    int c, neg, digits, len, i;
    char ch1, ch2;
    long long n;

    for (;;) {
        printf("Give me a number: ");

        /* diavasma arithmou */
        c = getchar();
        while (c != EOF && is_space(c))
            c = getchar();
        if (c == EOF) {
            printf("EOF detected, exiting\n");
            return 0;
        }

        neg = 0;
        if (c == '-' || c == '+') {
            if (c == '-')
                neg = 1;
            c = getchar();
        }

        n = 0;
        digits = 0;
        while (c >= '0' && c <= '9') {
            digits++;
            if (n <= MAXN)
                n = n * 10 + (c - '0');
            c = getchar();
        }

        if (digits == 0 || (c != EOF && !is_space(c))) {
            fprintf(stderr, "Invalid input: expected an integer\n");
            return 1;
        }
        if ((neg && n > 0) || n > MAXN) {
            fprintf(stderr, "Number should be in the range [0, 10000000000]\n");
            return 1;
        }

        printf("Choose how to test %lld - ('p' for prime, 'g' for goldbach) ", n);

        /* diavasma epilogis (p, g i kai ta dyo p.x. pg) */
        while (c != EOF && is_space(c))
            c = getchar();
        if (c == EOF) {
            printf("EOF detected, exiting\n");
            return 0;
        }

        len = 0;
        ch1 = 0;
        ch2 = 0;
        while (c != EOF && !is_space(c)) {
            if (len == 0)
                ch1 = c;
            else if (len == 1)
                ch2 = c;
            len++;
            c = getchar();
        }

        if (!(ch1 == 'p' || ch1 == 'g') ||
            len > 2 ||
            (len == 2 && !(ch2 == 'p' || ch2 == 'g'))) {
            fprintf(stderr, "Invalid choice: expected 'p' or 'g'\n");
            return 1;
        }

        for (i = 0; i < len; i++) {
            if (i == 0)
                run(ch1, n);
            else
                run(ch2, n);
        }
    }
}

