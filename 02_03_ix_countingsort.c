/*
Set2 Q3(ix) Counting Sort
*/

#include <stdio.h>

void countingSort(int arr[], int n) {
    int output[n]; 
    int max = arr[0];

    for (int i = 1; i < n; i++) {
        if (arr[i] > max)
            max = arr[i];
    }

    int count[max + 1]; 
    for (int i = 0; i <= max; i++)
        count[i] = 0;

    for (int i = 0; i < n; i++)
        count[arr[i]]++;

    for (int i = 1; i <= max; i++)
        count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; i--) {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }

    for (int i = 0; i < n; i++)
        arr[i] = output[i];
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int arr[100], n;
    printf("Enter the number of Values:");
    scanf("%d",&n);
    for(int i=0; i<n; i++){
        printf("Enter value Arr[%d]:",i);
        scanf("%d", &arr[i]);
    }

    printf("Original array: ");
    printArray(arr, n);

    countingSort(arr, n);

    printf("Sorted array: ");
    printArray(arr, n);

    return 0;
}
