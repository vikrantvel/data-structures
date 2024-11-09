#include <stdio.h>
#define MAX 5  // Defining MAX as 5 for the queue size

int queue[MAX];
int front = -1, rear = -1;

void enqueue() {
    int item;
    if ((rear + 1) % MAX == front) {
        printf("Queue is full\n");
    } else {
        printf("Enter the element to enqueue: ");
        scanf("%d", &item);
        if (front == -1) front = 0;  // Initialize front if it's the first element
        rear = (rear + 1) % MAX;     // Circular increment for rear
        queue[rear] = item;
        printf("%d enqueued to the queue\n", item);
    }
}

void dequeue() {
    if (front == -1) {
        printf("Queue is empty\n");
    } else {
        printf("%d dequeued from the queue\n", queue[front]);
        if (front == rear) {
            // Queue becomes empty after this dequeue
            front = rear = -1;
        } else {
            front = (front + 1) % MAX;  // Circular increment for front
        }
    }
}

void display() {
    if (front == -1) {
        printf("Queue is empty\n");
    } else {
        printf("Queue elements: ");
        int i = front;
        while (1) {
            printf("%d ", queue[i]);
            if (i == rear) break;
            i = (i + 1) % MAX;  // Circular traversal
        }
        printf("\n");
    }
}

int main() {
    int choice;
    while (1) {
        printf("\nQueue Operations (Array): \n");
        printf("1. Enqueue\n2. Dequeue\n3. Display\n4. Exit\n");
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

