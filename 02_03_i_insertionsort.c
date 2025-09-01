// Set2 Q3(i) Insertion Sort

#include<stdio.h>

int main(){
    int arr[100], n, key, j;
    printf("Enter the number of Values:");
    scanf("%d",&n);
    for(int i=0; i<n; i++){
        printf("Enter value Arr[%d]:",i);
        scanf("%d", &arr[i]);
    }

    printf("Array before sorting:");
    for(int i=0; i<n; i++){
        printf("%d ", arr[i]);
    }

    for (int k = 0; k < n; k++){
        key = arr[k];
        j = k - 1;
        while (key < arr[j] && j >= 0)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
    printf("\n");
    printf("Array after Sorting:");
    for(int i=0; i<n; i++){
        printf("%d ", arr[i]);
    }
    return 0;
}