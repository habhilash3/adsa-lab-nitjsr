#include <stdio.h>
#include <limits.h>
#include <math.h>
#include <time.h>

#define MAXN 20
#define INF 1000000000

int n; // number of nodes
int dist[MAXN][MAXN];
int dp[1 << MAXN][MAXN]; // DP table

int tsp(int mask, int pos) {
    if (mask == (1 << n) - 1)
        return dist[pos][0];  // return to start

    if (dp[mask][pos] != -1)
        return dp[mask][pos];

    int ans = INF;
    for (int city = 0; city < n; city++) {
        if ((mask & (1 << city)) == 0) {
            int newAns = dist[pos][city] + tsp(mask | (1 << city), city);
            if (newAns < ans)
                ans = newAns;
        }
    }
    return dp[mask][pos] = ans;
}

int main() {
    n = 10; // Example for 10 nodes

    // Generate a random complete graph with weights
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) dist[i][j] = 0;
            else dist[i][j] = rand() % 100 + 1;
        }
    }

    // Initialize DP
    for (int i = 0; i < (1 << n); i++)
        for (int j = 0; j < n; j++)
            dp[i][j] = -1;

    clock_t start = clock();
    int ans = tsp(1, 0);  // start from node 0
    clock_t end = clock();

    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Minimum tour cost: %d\n", ans);
    printf("Execution time: %f seconds\n", time_taken);

    return 0;
}
