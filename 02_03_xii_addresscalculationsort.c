/*
Set2 Q3(xii) Addres Calculation Sort
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX 100

void addressCalculationSort(int arr[], int n) {
    int i, j;
    int min = arr[0], max = arr[0];

    
    for (i = 1; i < n; i++) {
        if (arr[i] < min) min = arr[i];
        if (arr[i] > max) max = arr[i];
    }

    int range = max - min + 1;
    int *aux = (int *)calloc(range, sizeof(int)); 

    
    for (i = 0; i < n; i++) {
        aux[arr[i] - min]++;
    }

    j = 0;
    for (i = 0; i < range; i++) {
        while (aux[i] > 0) {
            arr[j++] = i + min;
            aux[i]--;
        }
    }

    free(aux);
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

    addressCalculationSort(arr, n);

    printf("Array after sorting: ");
    printArray(arr, n);

    return 0;
}
