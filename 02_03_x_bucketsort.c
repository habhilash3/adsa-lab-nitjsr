/*
Set2 Q3(x) Bucket Sort
*/


#include <stdio.h>
#include <stdlib.h>

#define MAX 100

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void bucketSort(int arr[], int n) {
    int maxVal = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > maxVal)
            maxVal = arr[i];
    }

    int bucketCount = maxVal / 10 + 1;

    int *buckets[bucketCount];
    int bucketSizes[bucketCount];

    for (int i = 0; i < bucketCount; i++) {
        buckets[i] = (int *)malloc(n * sizeof(int));
        bucketSizes[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        int index = arr[i] / 10; 
        buckets[index][bucketSizes[index]++] = arr[i];
    }

    for (int i = 0; i < bucketCount; i++) {
        if (bucketSizes[i] > 0)
            insertionSort(buckets[i], bucketSizes[i]);
    }

    int idx = 0;
    for (int i = 0; i < bucketCount; i++) {
        for (int j = 0; j < bucketSizes[i]; j++) {
            arr[idx++] = buckets[i][j];
        }
        free(buckets[i]);
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

    printf("Enter %d integers:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Array before sorting: ");
    printArray(arr, n);

    bucketSort(arr, n);

    printf("Array after sorting: ");
    printArray(arr, n);

    return 0;
}
