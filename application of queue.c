#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 5
#define TASK_LENGTH 100

// Global variables for the task queue
char tasks[MAX][TASK_LENGTH];
int front = -1;
int rear = -1;

// Function to check if the queue is empty
int isEmpty() {
    return front == -1;
}

// Function to check if the queue is full
int isFull() {
    return rear == MAX - 1;
}

// Function to add a task to the queue
void enqueue(char* task) {
    if (isFull()) {
        printf("Task queue is full. Cannot add more tasks.\n");
        return;
    }
    if (isEmpty()) {
        front = 0; // Initialize front if the queue is empty
    }
    rear++;
    strcpy(tasks[rear], task);
    printf("Task added: %s\n", task);
}

// Function to complete a task from the queue
void dequeue() {
    if (isEmpty()) {
        printf("No tasks to complete.\n");
        return;
    }
    printf("Completed task: %s\n", tasks[front]);
    front++;
    if (front > rear) {
        front = rear = -1; // Reset the queue
    }
}

// Function to display current tasks in the queue
void display() {
    if (isEmpty()) {
        printf("No tasks in the queue.\n");
        return;
    }
    printf("Current tasks:\n");
    for (int i = front; i <= rear; i++) {
        printf("%d: %s\n", i - front + 1, tasks[i]);
    }
}

// Main function
int main() {
    char task[TASK_LENGTH];
    int choice;

    while (1) {
        printf("\nTask Management System:\n");
        printf("1. Add Task\n");
        printf("2. Complete Task\n");
        printf("3. Display Tasks\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline character

        switch (choice) {
            case 1:
                printf("Enter the task: ");
                fgets(task, TASK_LENGTH, stdin);
                task[strcspn(task, "\n")] = 0; // Remove newline character
                enqueue(task);
                break;
            case 2:
                dequeue();
                break;
            case 3:
                display();
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
