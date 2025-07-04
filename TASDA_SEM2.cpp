#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 50

// Node structure for queue (scene 3)
struct Node {
    char name[MAX_NAME_LEN];
    struct Node* next;
};

struct Node* front = NULL;
struct Node* rear = NULL;

// Add customer to the queue (scene 4)
int addCustomer(char name[]) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode) return 0; // memory allocation failed

    strcpy(newNode->name, name);
    newNode->next = NULL;

    if (rear == NULL) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }

    return 1; // success
}

// Serve customer from the queue (scene 5)
int serveCustomer(char servedName[]) {
    if (front == NULL) return 0; // queue is empty

    struct Node* temp = front;
    strcpy(servedName, front->name);
    front = front->next;
    if (front == NULL) rear = NULL;

    free(temp);
    return 1; // success
}

// Get the list of waitlist customers as a string (scene 6)
int getWaitlist(char list[][MAX_NAME_LEN], int maxCount) {
    struct Node* temp = front;
    int i = 0;
    while (temp != NULL && i < maxCount) {
        strcpy(list[i], temp->name);
        temp = temp->next;
        i++;
    }
    return i; // number of names copied
}

// Show the menu and return user's choice (scene 7)
int showMenu() {
    int choice;
    printf("\n=== Restaurant Waitlist ===\n");
    printf("1. Add Customer to Waitlist\n");
    printf("2. Serve Next Customer\n");
    printf("3. View Waitlist\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    getchar(); // consume newline
    return choice;
}

// Main program
int main() {
    int choice;
    char name[MAX_NAME_LEN];
    char served[MAX_NAME_LEN];
    char waitlist[100][MAX_NAME_LEN]; // assuming max 100 customers

    do {
        choice = showMenu();

        if (choice == 1) {
            printf("Enter customer name: ");
            fgets(name, MAX_NAME_LEN, stdin);
            name[strcspn(name, "\n")] = '\0'; // remove newline
            if (addCustomer(name))
                printf("%s has been added to the waitlist.\n", name);
            else
                printf("Failed to add customer. Memory error.\n");

        } else if (choice == 2) {
            if (serveCustomer(served))
                printf("Serving %s...\n", served);
            else
                printf("Waitlist is empty. No customer to serve.\n");

        } else if (choice == 3) {
            int count = getWaitlist(waitlist, 100);
            if (count == 0) {
                printf("Waitlist is empty.\n");
            } else {
                printf("Current Waitlist:\n");
                for (int i = 0; i < count; i++) {
                    printf("%d. %s\n", i + 1, waitlist[i]);
                }
            }
        } else if (choice == 4) {
            printf("Exiting. Goodbye!\n");
        } else {
            printf("Invalid choice. Try again.\n");
        }

    } while (choice != 4);

    return 0;
}
