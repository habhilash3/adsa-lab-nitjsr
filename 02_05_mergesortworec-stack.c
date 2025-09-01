#include <stdio.h>
#define MAX 100

void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSortBottomUp(int arr[], int n) {
    int curr_size;  // Size of subarrays to merge
    int left_start; // Starting index of left subarray

    // Merge subarrays in bottom-up manner
    for (curr_size = 1; curr_size < n; curr_size *= 2) {
        for (left_start = 0; left_start < n - 1; left_start += 2 * curr_size) {
            int mid = left_start + curr_size - 1;
            int right_end = (left_start + 2 * curr_size - 1 < n - 1)
                            ? left_start + 2 * curr_size - 1
                            : n - 1;

            if (mid < right_end) // Ensure there are two parts to merge
                merge(arr, left_start, mid, right_end);
        }
    }
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

    printf("Enter elements:\n");
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);

    printf("Array before sorting: ");
    printArray(arr, n);

    mergeSortBottomUp(arr, n);

    printf("Array after sorting: ");
    printArray(arr, n);

    return 0;
}
