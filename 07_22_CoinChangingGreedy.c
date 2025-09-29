#include <stdio.h>

// Function to implement greedy coin change
void coinChange(int coins[], int n, int amount) {
    printf("Coins used to make amount %d:\n", amount);
    for (int i = 0; i < n; i++) {
        while (amount >= coins[i]) {
            amount -= coins[i];
            printf("%d ", coins[i]);
        }
    }
    printf("\n");
}

int main() {
    // Example: Indian currency denominations
    int coins[] = {1000, 500, 200, 100, 50, 20, 10, 5, 2, 1};
    int n = sizeof(coins) / sizeof(coins[0]);

    int amount;
    printf("Enter the amount: ");
    scanf("%d", &amount);

    coinChange(coins, n, amount);

    return 0;
}
