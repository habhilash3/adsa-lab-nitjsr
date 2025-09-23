#include <stdio.h>

int n;                // number of items
int W;                // capacity of knapsack
int weight[20];       // weight of items
int value[20];        // value of items

int maxValue = 0;     // best value found so far

// Backtracking function
void knapsack(int i, int currWeight, int currValue) {
    // If capacity exceeded, stop
    if (currWeight > W) return;

    // If all items considered, update maxValue
    if (i == n) {
        if (currValue > maxValue)
            maxValue = currValue;
        return;
    }

    // Choice 1: Exclude item i
    knapsack(i + 1, currWeight, currValue);

    // Choice 2: Include item i
    knapsack(i + 1, currWeight + weight[i], currValue + value[i]);
}

int main() {
    int i;
    
    // Example input
    n = 3;
    W = 50;
    weight[0] = 10; value[0] = 60;
    weight[1] = 20; value[1] = 100;
    weight[2] = 30; value[2] = 120;

    // Start backtracking from item 0
    knapsack(0, 0, 0);

    printf("Maximum value = %d\n", maxValue);

    return 0;
}
