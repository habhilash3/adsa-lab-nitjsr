#include <stdio.h>
#include <string.h>
#define NO_OF_CHARS 256

// Function to create the bad character heuristic table
void badCharHeuristic(char *pattern, int m, int badchar[]) {
    int i;
    // Initialize all occurrences as -1
    for (i = 0; i < NO_OF_CHARS; i++)
        badchar[i] = -1;

    // Fill the actual value of the last occurrence of a character
    for (i = 0; i < m; i++)
        badchar[(unsigned char)pattern[i]] = i;
}

// Boyer-Moore search function (using only bad character heuristic)
void boyerMooreSearch(char *text, char *pattern) {
    int n = strlen(text);
    int m = strlen(pattern);
    int badchar[NO_OF_CHARS];

    // Preprocess the pattern
    badCharHeuristic(pattern, m, badchar);

    int s = 0; // s is the shift of the pattern with respect to text
    while (s <= (n - m)) {
        int j = m - 1;

        // Keep reducing index j while characters match
        while (j >= 0 && pattern[j] == text[s + j])
            j--;

        // If the pattern is found
        if (j < 0) {
            printf("Pattern found at index %d\n", s);

            // Shift pattern so that next character in text aligns with last occurrence in pattern
            s += (s + m < n) ? m - badchar[(unsigned char)text[s + m]] : 1;
        } else {
            // Shift pattern so that bad character aligns with last occurrence in pattern
            int shift = j - badchar[(unsigned char)text[s + j]];
            s += (shift > 1) ? shift : 1;
        }
    }
}

int main() {
    char text[100], pattern[100];

    printf("Enter text: ");
    gets(text);

    printf("Enter pattern: ");
    gets(pattern);

    boyerMooreSearch(text, pattern);

    return 0;
}
