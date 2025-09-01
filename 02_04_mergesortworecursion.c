#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int left;
    int right;
    int stage; // 0 = divide, 1 = merge
} Frame;

void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSortNonRecursive(int arr[], int n) {
    Frame stack[2 * MAX];
    int top = -1;

    // push initial frame
    stack[++top] = (Frame){0, n - 1, 0};

    while (top >= 0) {
        Frame curr = stack[top--];

        if (curr.left >= curr.right) 
            continue;

        if (curr.stage == 0) {
            int mid = curr.left + (curr.right - curr.left) / 2;

            // push merge stage
            stack[++top] = (Frame){curr.left, curr.right, 1};

            // push right subarray for divide stage
            stack[++top] = (Frame){mid + 1, curr.right, 0};

            // push left subarray for divide stage
            stack[++top] = (Frame){curr.left, mid, 0};
        } else {
            int mid = curr.left + (curr.right - curr.left) / 2;
            merge(arr, curr.left, mid, curr.right);
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

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter elements:\n");
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);

    printf("Array before sorting: ");
    printArray(arr, n);

    mergeSortNonRecursive(arr, n);

    printf("Array after sorting: ");
    printArray(arr, n);

    return 0;
}
