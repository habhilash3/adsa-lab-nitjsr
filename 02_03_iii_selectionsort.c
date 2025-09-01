/*
Set2 Q3(iii) Slection Sort
*/

#include <stdio.h>
#define MAX 100

void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i; 

        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex])
                minIndex = j;
        }

        int temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
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

    selectionSort(arr, n);

    printf("Array after Sorting: ");
    printArray(arr, n);

    return 0;
}
