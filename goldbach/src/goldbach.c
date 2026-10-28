/*
 * goldbach.c - Η Εικασία του Goldbach
 *
 * Η εικασία: κάθε άρτιος ακέραιος > 2 γράφεται ως άθροισμα δύο πρώτων
 * (π.χ. 10 = 3 + 7). Το πρόγραμμα διαβάζει επαναλαμβανόμενα έναν ακέραιο n
 * (0 <= n <= 10^10) και μια επιλογή:
 *   p - ελέγχει αν ο n είναι πρώτος
 *   g - βρίσκει n = p + q (p, q πρώτοι, p <= q) με τον μικρότερο δυνατό p
 *
 */
#include <stdio.h>

/* Μέγιστο n. Το LL το κάνει long long: το 10^10 δεν χωράει σε int. */
#define MAXN 10000000000LL

/* 1 αν ο c είναι κενός χαρακτήρας (κενό, νέα γραμμή, tab), αλλιώς 0. */
int is_space(int c)
{
    return c == ' ' || c == '\n' || c == '\t' || c == '\r';
}

/* 1 αν ο n είναι πρώτος, αλλιώς 0. Δοκιμάζουμε διαιρέτες μέχρι sqrt(n):
 * αν ο n έχει διαιρέτη > sqrt(n), έχει και έναν μικρότερο, που θα τον
 * είχαμε βρει. Για n = 10^10 είναι το πολύ 50.000 δοκιμές. */
int is_prime(long long n)
{
    long long i;

    if (n < 2)              /* το 0 και το 1 δεν είναι πρώτοι */
        return 0;
    if (n % 2 == 0)         /* από τους άρτιους μόνο το 2 είναι πρώτος */
        return n == 2;
    /* Μένουν οι περιττοί, άρα δοκιμάζουμε μόνο περιττούς διαιρέτες.
     * Το i * i <= n είναι το ίδιο με i <= sqrt(n), χωρίς sqrt. */
    for (i = 3; i * i <= n; i += 2)
        if (n % i == 0)
            return 0;
    return 1;
}

/* Εκτελεί την επιλογή (letter = 'p' ή 'g') για τον αριθμό n. */
void run(char letter, long long n)
{
    long long p;

    /* Επιλογή 'p': τυπώνουμε αν ο n είναι πρώτος. */
    if (letter == 'p') {
        if (is_prime(n))
            printf("%lld is prime\n", n);
        else
            printf("%lld is not prime\n", n);
        return;
    }

    /* Επιλογή 'g': η εικασία αφορά μόνο άρτιους μεγαλύτερους του 2. */
    if (n <= 2 || n % 2 != 0) {
        printf("Goldbach's conjecture is applicable only to even numbers greater than 2!\n");
        return;
    }

    /* Δοκιμάζουμε p = 2, 3, 4, ... με αύξουσα σειρά. Το πρώτο p με p και
     * n - p πρώτους είναι ο μικρότερος δυνατός, άρα η απάντηση είναι
     * μοναδική και p <= q (π.χ. 10 = 3 + 7, όχι 5 + 5). Σταματάμε στο
     * n / 2, γιατί μετά τα ζεύγη θα επαναλαμβάνονταν ανάποδα. */
    for (p = 2; p <= n / 2; p++) {
        if (is_prime(p) && is_prime(n - p)) {
            printf("%lld = %lld + %lld\n", n, p, n - p);
            return;
        }
    }
}

int main(void)
{
    int c;                  /* τρέχων χαρακτήρας (int, για να χωράει το EOF) */
    int neg, digits;        /* αρνητικός αριθμός; πόσα ψηφία διαβάστηκαν */
    int len;                /* πόσους χαρακτήρες έχει η επιλογή */
    char ch;                /* ο χαρακτήρας επιλογής */
    long long n;            /* ο αριθμός που διαβάζουμε */

    for (;;) {              /* επαναλαμβάνουμε μέχρι EOF ή λάθος */
        printf("Give me a number: ");

        /* --- Ανάγνωση αριθμού --- */

        /* Προσπερνάμε τα κενά. Στο EOF τερματίζουμε κανονικά (κωδικός 0). */
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

        /* Χτίζουμε τον αριθμό ψηφίο-ψηφίο: n * 10 + (c - '0'), όπου το
         * (c - '0') είναι η τιμή του ψηφίου. Μόλις ο n ξεπεράσει το όριο,
         * σταματάμε να τον αλλάζουμε, ώστε να μην γίνει υπερχείλιση. */
        n = 0;
        digits = 0;
        while (c >= '0' && c <= '9') {
            digits++;
            if (n <= MAXN)
                n = n * 10 + (c - '0');
            c = getchar();
        }

        /* Λάθος: κανένα ψηφίο ("banana") ή κάτι μετά τον αριθμό ("12abc").
         * Το μήνυμα πάει στο stderr και βγαίνουμε με κωδικό 1. */
        if (digits == 0 || (c != EOF && !is_space(c))) {
            fprintf(stderr, "Invalid input: expected an integer\n");
            return 1;
        }
        /* Λάθος: αρνητικός (το -0 είναι αποδεκτό) ή πάνω από το όριο. */
        if ((neg && n > 0) || n > MAXN) {
            fprintf(stderr, "Number should be in the range [0, 10000000000]\n");
            return 1;
        }

        printf("Choose how to test %lld - ('p' for prime, 'g' for goldbach) ", n);

        /* --- Ανάγνωση επιλογής --- */

        /* Προσπερνάμε τα κενά (το c έχει τον χαρακτήρα μετά τον αριθμό). */
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

        /* Έγκυρη επιλογή: ακριβώς ένας χαρακτήρας, p ή g. Οτιδήποτε άλλο
         * (π.χ. "x" ή "pg") είναι λάθος. */
        if (len != 1 || (ch != 'p' && ch != 'g')) {
            fprintf(stderr, "Invalid choice: expected 'p' or 'g'\n");
            return 1;
        }

        run(ch, n);         /* εκτελούμε την επιλογή και ξαναρχίζουμε */
    }
}
