/*
Set1 Q2. Write a C program to implement singly linked list with the operations for delection, insertion, searching and traversal.
         The program shuold include menu driven interface to allow users to perform the operations interactively. 
*/


#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* head = NULL;

void insert(int val) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = val;
    newNode->next = NULL;

    if (head == NULL) {
        head = newNode;
        return;
    }
    struct Node* temp = head;
    while (temp->next != NULL) temp = temp->next;
    temp->next = newNode;
}

void deleteNode(int val) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }
    if (head->data == val) {
        struct Node* temp = head;
        head = head->next;
        free(temp);
        printf("Deleted %d\n", val);
        return;
    }
    struct Node* temp = head;
    while (temp->next != NULL && temp->next->data != val) {
        temp = temp->next;
    }
    if (temp->next != NULL) {
        struct Node* del = temp->next;
        temp->next = del->next;
        free(del);
        printf("Deleted %d\n", val);
    } else {
        printf("Value not found.\n");
    }
}

void search(int val) {
    struct Node* temp = head;
    int pos = 0;
    while (temp != NULL) {
        if (temp->data == val) {
            printf("Found %d at position %d\n", val, pos);
            return;
        }
        temp = temp->next;
        pos++;
    }
    printf("Value not found.\n");
}

void display() {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }
    struct Node* temp = head;
    printf("Linked List: ");
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

int main() {
    int choice, val;

    do {
        printf("\n--- Singly Linked List Menu ---\n");
        printf("1. Insert\n2. Delete\n3. Search\n4. Display\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &val);
                insert(val);
                break;
            case 2:
                printf("Enter value to delete: ");
                scanf("%d", &val);
                deleteNode(val);
                break;
            case 3:
                printf("Enter value to search: ");
                scanf("%d", &val);
                search(val);
                break;
            case 4:
                display();
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 5);

    return 0;
}