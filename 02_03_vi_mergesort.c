/*
Set2 Q3(vi) Merge Sort
*/

#include <stdio.h>
#define MAX 100

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1; 
    int n2 = right - mid;    

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int arr[MAX], n;
    printf("Enter the number of Values: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        printf("Enter value Arr[%d]: ", i);
        scanf("%d", &arr[i]);
    }

    printf("Array before Sorting: ");
    printArray(arr, n);

    mergeSort(arr, 0, n - 1);

    printf("Array after Sorting: ");
    printArray(arr, n);

    return 0;
}
