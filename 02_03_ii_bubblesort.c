// Set2 Q3(ii) Bubble Sort

#include<stdio.h>

int main(){
    int arr[100], n, t;
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

    // Bubble sort
    for(int i=0; i<n; i++){
        for(int j=0; j<n-i-1; j++){
            if (arr[j]>arr[j+1]){
                t=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=t;
            }
        }
    }

    printf("\n");
    printf("Array after Sorting:");
    for(int i=0; i<n; i++){
        printf("%d ", arr[i]);
    }
    return 0;
}