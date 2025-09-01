/*
Set2 Q3(v) Quick Sort
*/

#include <stdio.h>
#define MAX 100


void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high]; 
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high); 

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int arr[MAX], n;
    printf("Enter number of values: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter value Arr[%d]: ", i);
        scanf("%d", &arr[i]);
    }

    printf("Array before Sorting: ");
    printArray(arr, n);

    quickSort(arr, 0, n - 1);

    printf("Array after Sorting: ");
    printArray(arr, n);

    return 0;
}
