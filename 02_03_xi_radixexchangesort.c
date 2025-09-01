/*
Set2 Q3(xu) Radix Exchange Sort
*/

#include <stdio.h>

#define MAX 100

int getMax(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];
    return max;
}

int getMaxBits(int max) {
    int bits = 0;
    while (max > 0) {
        max /= 2;
        bits++;
    }
    return bits;
}

void radixExchangeSort(int arr[], int left, int right, int bit) {
    if (left >= right || bit < 0)
        return;

    int i = left, j = right;
    while (i <= j) {
        while (i <= right && !(arr[i] & (1 << bit))) i++; // 0-bit
        while (j >= left && (arr[j] & (1 << bit))) j--;   // 1-bit
        if (i < j) {
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    radixExchangeSort(arr, left, j, bit - 1);
    radixExchangeSort(arr, i, right, bit - 1);
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int arr[MAX], n;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter %d integers:\n", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    printf("Array before sorting: ");
    printArray(arr, n);

    int max = getMax(arr, n);
    int bits = getMaxBits(max);

    radixExchangeSort(arr, 0, n - 1, bits - 1);

    printf("Array after sorting: ");
    printArray(arr, n);

    return 0;
}
