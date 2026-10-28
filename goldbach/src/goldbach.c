/*
 * goldbach.c - Η Εικασία του Goldbach
 *
 * Διαβάζει επαναλαμβανόμενα έναν ακέραιο n (0 <= n <= 10^10) και μια επιλογή:
 *   p - ελέγχει αν ο n είναι πρώτος
 *   g - βρίσκει n = p + q (p, q πρώτοι, p <= q) με τον μικρότερο δυνατό p
 *
 */
#include <stdio.h>

/* Μέγιστο n. Το LL το κάνει long long: το 10^10 δεν χωράει σε int. */
#define MAXN 10000000000LL

/* 1 αν ο c είναι κενός χαρακτήρας (κενό, νέα γραμμή, tab). */
int is_space(int c)
{
    return c == ' ' || c == '\n' || c == '\t' || c == '\r';
}

/* 1 αν ο n είναι πρώτος, αλλιώς 0. Δοκιμάζουμε διαιρέτες μέχρι sqrt(n):
 * αν ο n έχει διαιρέτη > sqrt(n), έχει και έναν μικρότερο. */
int is_prime(long long n)
{
    long long i;

    if (n < 2)              /* το 0 και το 1 δεν είναι πρώτοι */
        return 0;
    if (n % 2 == 0)         /* από τους άρτιους μόνο το 2 είναι πρώτος */
        return n == 2;
    /* μόνο περιττοί διαιρέτες. Το i * i <= n είναι ίδιο με i <= sqrt(n) */
    for (i = 3; i * i <= n; i += 2)
        if (n % i == 0)
            return 0;
    return 1;
}
/* Εκτελεί την επιλογή (letter = 'p' ή 'g') για τον αριθμό n. */
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

    /* letter == 'g': η εικασία αφορά άρτιους μεγαλύτερους του 2 */
    if (n <= 2 || n % 2 != 0) {
        printf("Goldbach's conjecture is applicable only to even numbers greater than 2!\n");
        return;
    }

    /* Δοκιμάζουμε p = 2, 3, 4, ... με αύξουσα σειρά. Το πρώτο p με p και
     * n - p πρώτους είναι ο μικρότερος δυνατός, άρα η απάντηση είναι
     * μοναδική και p <= q. Σταματάμε στο n / 2. */
    for (p = 2; p <= n / 2; p++) {
        if (is_prime(p) && is_prime(n - p)) {
            printf("%lld = %lld + %lld\n", n, p, n - p);
            return;
        }
    }
}

int main(void)
{
    int c;                  /* τρέχων χαρακτήρας (int, για το EOF) */
    int neg, digits;        /* αρνητικός; πόσα ψηφία διαβάστηκαν */
    int len;                /* πόσοι χαρακτήρες έχει η επιλογή */
    char ch;                /* ο χαρακτήρας επιλογής */
    long long n;            /* ο αριθμός που διαβάζουμε */

    for (;;) {              /* μέχρι EOF ή λάθος */
        printf("Give me a number: ");

        /* --- Ανάγνωση αριθμού: προσπερνάμε πρώτα τα κενά --- */
        c = getchar();
        while (c != EOF && is_space(c))
            c = getchar();
        if (c == EOF) {
            printf("EOF detected, exiting\n");
            return 0;
        }

        neg = 0;            /* προαιρετικό πρόσημο */
        if (c == '-' || c == '+') {
            if (c == '-')
                neg = 1;
            c = getchar();
        }

        /* Χτίζουμε τον αριθμό ψηφίο-ψηφίο: n * 10 + (c - '0'). Μόλις
         * ξεπεράσει το όριο, σταματάμε να τον αλλάζουμε (όχι υπερχείλιση). */
        n = 0;
        digits = 0;
        while (c >= '0' && c <= '9') {
            digits++;
            if (n <= MAXN)
                n = n * 10 + (c - '0');
            c = getchar();
        }

        /* Λάθος: κανένα ψηφίο ("banana") ή κάτι μετά τον αριθμό ("12abc") */
        if (digits == 0 || (c != EOF && !is_space(c))) {
            fprintf(stderr, "Invalid input: expected an integer\n");
            return 1;
        }
        /* Λάθος: αρνητικός (εκτός από το -0) ή πολύ μεγάλος */
        if ((neg && n > 0) || n > MAXN) {
            fprintf(stderr, "Number should be in the range [0, 10000000000]\n");
            return 1;
        }
        printf("Choose how to test %lld - ('p' for prime, 'g' for goldbach) ", n);
        /* --- Ανάγνωση επιλογής: προσπερνάμε πρώτα τα κενά --- */
        while (c != EOF && is_space(c))
            c = getchar();
        if (c == EOF) {
            printf("EOF detected, exiting\n");
            return 0;
        }

        /* Διαβάζουμε όλη τη λέξη μέχρι το επόμενο κενό: κρατάμε τον πρώτο
         * χαρακτήρα και μετράμε πόσοι ήταν συνολικά. */
        len = 0;
        ch = 0;
        while (c != EOF && !is_space(c)) {
            if (len == 0)
                ch = c;
            len++;
            c = getchar();
        }
        /* Έγκυρη επιλογή: ακριβώς ένας χαρακτήρας, p ή g. Αλλιώς λάθος
         * (π.χ. "x" ή "pg"). */
        if (len != 1 || (ch != 'p' && ch != 'g')) {
            fprintf(stderr, "Invalid choice: expected 'p' or 'g'\n");
            return 1;
        }
        run(ch, n);
    }
}
