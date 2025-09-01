/*
Set2 Q3(vii) Heap Sort
*/


#include <stdio.h>
#define MAX 100

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(int arr[], int n, int i) {
    int largest = i;         
    int left = 2 * i + 1;    
    int right = 2 * i + 2;   

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);  
        heapify(arr, i, 0);     
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

    heapSort(arr, n);

    printf("Array after Sorting: ");
    printArray(arr, n);

    return 0;
}
