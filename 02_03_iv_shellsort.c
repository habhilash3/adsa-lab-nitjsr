// Set2 Q3(iv) Shell Sort

#include <stdio.h>
#define MAX 100

void shellSort(int arr[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
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
    printf("Enter the number of Values:");
    scanf("%d",&n);
    for(int i=0; i<n; i++){
        printf("Enter value Arr[%d]:",i);
        scanf("%d", &arr[i]);
    }
    printf("Array befor Sorting: ");
    printArray(arr, n);
    shellSort(arr, n);
    printf("Array after Sorting: ");
    printArray(arr, n);
    return 0;
}
