#include <stdio.h>
#include <string.h>
#include <math.h>

#define d 256    // number of characters in input alphabet
#define q 101    // a prime number for modulo operation

void rabinKarp(char pattern[], char text[]) {
    int m = strlen(pattern);
    int n = strlen(text);
    int i, j;
    int p = 0;  // hash value for pattern
    int t = 0;  // hash value for text
    int h = 1;

    // h = pow(d, m-1) % q
    for (i = 0; i < m - 1; i++)
        h = (h * d) % q;

    // Calculate hash value of pattern and first window of text
    for (i = 0; i < m; i++) {
        p = (d * p + pattern[i]) % q;
        t = (d * t + text[i]) % q;
    }

    // Slide the pattern over text one by one
    for (i = 0; i <= n - m; i++) {
        // Check the hash values of current window and pattern
        if (p == t) {
            // If hash values match, check characters one by one
            for (j = 0; j < m; j++) {
                if (text[i + j] != pattern[j])
                    break;
            }
            if (j == m)
                printf("Pattern found at index %d\n", i);
        }

        // Calculate hash for next window: remove leading char, add trailing char
        if (i < n - m) {
            t = (d * (t - text[i] * h) + text[i + m]) % q;

            // If t becomes negative, convert it to positive
            if (t < 0)
                t = (t + q);
        }
    }
}

int main() {
    char text[100], pattern[100];

    printf("Enter text: ");
    gets(text);

    printf("Enter pattern: ");
    gets(pattern);

    rabinKarp(pattern, text);

    return 0;
}
