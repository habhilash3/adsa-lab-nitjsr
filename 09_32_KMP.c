#include <stdio.h>
#include <string.h>

// Function to compute LPS (Longest Prefix Suffix) array
void computeLPS(char pattern[], int m, int lps[]) {
    int len = 0;  // length of previous longest prefix suffix
    int i = 1;
    lps[0] = 0;   // first element is always 0

    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0)
                len = lps[len - 1];
            else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// KMP search function
void KMPsearch(char text[], char pattern[]) {
    int n = strlen(text);
    int m = strlen(pattern);
    int lps[m];
    computeLPS(pattern, m, lps);

    int i = 0; // index for text
    int j = 0; // index for pattern

    while (i < n) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }

        if (j == m) {
            printf("Pattern found at index %d\n", i - j);
            j = lps[j - 1];  // continue searching
        } 
        else if (i < n && pattern[j] != text[i]) {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }
}

int main() {
    char text[100], pattern[100];

    printf("Enter text: ");
    gets(text);

    printf("Enter pattern: ");
    gets(pattern);

    KMPsearch(text, pattern);

    return 0;
}
