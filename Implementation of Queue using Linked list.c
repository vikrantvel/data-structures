#include <stdio.h>
#include <stdlib.h> // Corrected: Use <stdlib.h> for malloc instead of <stlid.h>

struct node {
    int data;
    struct node* next;
};

struct node* front = NULL;
struct node* rear = NULL;

void enqueue() {
    struct node* temp = (struct node*)malloc(sizeof(struct node)); // Corrected: Fixed declaration of temp
    int item;
    printf("Enter the element to enqueue: ");
    scanf("%d", &item);
    temp->data = item;
    temp->next = NULL;
    if (rear == NULL) {
        front = rear = temp; // If the queue is empty, both front and rear should point to the new node
    } else {
        rear->next = temp;
        rear = temp; // Update rear to the new node
    }
    printf("%d enqueued to the queue\n", item);
}

void dequeue() {
    if (front == NULL) { // Corrected: Added condition to check if the queue is empty
        printf("Queue is empty\n");
    } else {
        struct node* temp = front;
        printf("%d dequeued from the queue\n", front->data); // Corrected: Access the 'data' field in 'front'
        front = front->next;
        if (front == NULL) {
            rear = NULL; // If the queue becomes empty, set rear to NULL as well
        }
        free(temp); // Corrected: Added semicolon to free(temp)
    }
}

void display() {
    if (front == NULL) {
        printf("Queue is empty\n");
    } else {
        struct node* temp = front;
        printf("Queue elements: ");
        while (temp != NULL) {
            printf("%d ", temp->data); // Corrected: Added space between elements for better readability
            temp = temp->next;
        }
        printf("\n");
    }
}

int main() {
    int choice;
    while (1) {
        printf("\nQueue operations (linked list):\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: enqueue(); break;
            case 2: dequeue(); break;
            case 3: display(); break;
            case 4: return 0;
            default: printf("Invalid choice\n");
        }
    }
    return 0;
}

