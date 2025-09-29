#include <stdio.h>
#include <stdlib.h>

// Structure for a job
typedef struct {
    char id;        // Job ID (like A, B, C...)
    int deadline;   // Deadline of job
    int profit;     // Profit if job is done before or on deadline
} Job;

// Comparator function to sort jobs by profit (descending order)
int compare(const void* a, const void* b) {
    Job* j1 = (Job*)a;
    Job* j2 = (Job*)b;
    return (j2->profit - j1->profit);
}

// Function to find the maximum deadline
int findMaxDeadline(Job jobs[], int n) {
    int max = jobs[0].deadline;
    for (int i = 1; i < n; i++) {
        if (jobs[i].deadline > max)
            max = jobs[i].deadline;
    }
    return max;
}

// Function to schedule jobs
void jobSequencing(Job jobs[], int n) {
    // Sort jobs by profit (greedy choice)
    qsort(jobs, n, sizeof(Job), compare);

    int maxDeadline = findMaxDeadline(jobs, n);

    // Array to store result (slots)
    char result[maxDeadline + 1];
    int slot[maxDeadline + 1];

    // Initialize all slots as free
    for (int i = 0; i <= maxDeadline; i++) {
        slot[i] = 0;
        result[i] = '-';
    }

    // Iterate through jobs
    for (int i = 0; i < n; i++) {
        // Find a free slot from deadline backwards
        for (int j = jobs[i].deadline; j > 0; j--) {
            if (slot[j] == 0) {
                slot[j] = 1;
                result[j] = jobs[i].id;
                break;
            }
        }
    }

    // Print the scheduled jobs
    printf("Scheduled jobs: ");
    for (int i = 1; i <= maxDeadline; i++) {
        if (slot[i])
            printf("%c ", result[i]);
    }
    printf("\n");
}

// Driver function
int main() {
    Job jobs[] = {
        {'A', 2, 100},
        {'B', 1, 19},
        {'C', 2, 27},
        {'D', 1, 25},
        {'E', 3, 15}
    };

    int n = sizeof(jobs) / sizeof(jobs[0]);

    jobSequencing(jobs, n);

    return 0;
}
