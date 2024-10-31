#include <stdio.h>
#include <stdlib.h>
#define MAX 5

struct ArrayQueue {
    int items[MAX];
    int front, rear;
};

struct Node {
    int data;
    struct Node* next;
};

struct LinkedListQueue {
    struct Node* front;
    struct Node* rear;
};

void initArrayQueue(struct ArrayQueue* q);
int isFullArray(struct ArrayQueue* q);
int isEmptyArray(struct ArrayQueue* q);
void enqueueArray(struct ArrayQueue* q, int value);
int dequeueArray(struct ArrayQueue* q);
void printArrayQueue(struct ArrayQueue* q);
void initLinkedListQueue(struct LinkedListQueue* q);
int isEmptyLinkedList(struct LinkedListQueue* q);
void enqueueLinkedList(struct LinkedListQueue* q, int value);
int dequeueLinkedList(struct LinkedListQueue* q);
void printLinkedListQueue(struct LinkedListQueue* q);

int main() {
    int choice, implementation;
    struct ArrayQueue arrayQueue;
    struct LinkedListQueue linkedListQueue;
    
    initArrayQueue(&arrayQueue);
    initLinkedListQueue(&linkedListQueue);
    
    printf("Choose Queue Implementation:\n1. Array Queue\n2. Linked List Queue\n");
    printf("Enter choice: ");
    scanf("%d", &implementation);
    
    while (1) {
        printf("\nMenu:\n1. Enqueue\n2. Dequeue\n3. Print Queue\n4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        
        if (implementation == 1) {
            switch (choice) {
                case 1:
                    printf("Enter value to enqueue: ");
                    scanf("%d", &choice);
                    enqueueArray(&arrayQueue, choice);
                    break;
                case 2:
                    choice = dequeueArray(&arrayQueue);
                    if (choice != -1) {
                        printf("%d dequeued from queue\n", choice);
                    }
                    break;
                case 3:
                    printArrayQueue(&arrayQueue);
                    break;
                case 4:
                    exit(0);
                default:
                    printf("Invalid choice\n");
            }
        } else if (implementation == 2) {
            switch (choice) {
                case 1:
                    printf("Enter value to enqueue: ");
                    scanf("%d", &choice);
                    enqueueLinkedList(&linkedListQueue, choice);
                    break;
                case 2:
                    choice = dequeueLinkedList(&linkedListQueue);
                    if (choice != -1) {
                        printf("%d dequeued from queue\n", choice);
                    }
                    break;
                case 3:
                    printLinkedListQueue(&linkedListQueue);
                    break;
                case 4:
                    exit(0);
                default:
                    printf("Invalid choice\n");
            }
        } else {
            printf("Invalid implementation choice\n");
        }
    }
    
    return 0;
}

void initArrayQueue(struct ArrayQueue* q) {
    q->front = -1;
    q->rear = -1;
}

int isFullArray(struct ArrayQueue* q) {
    return (q->rear + 1) % MAX == q->front;
}

int isEmptyArray(struct ArrayQueue* q) {
    return q->front == -1;
}

void enqueueArray(struct ArrayQueue* q, int value) {
    if (isFullArray(q)) {
        printf("Queue is full\n");
        return;
    }
    if (isEmptyArray(q)) {
        q->front = 0;
    }
    q->rear = (q->rear + 1) % MAX;
    q->items[q->rear] = value;
    printf("%d enqueued to queue\n", value);
}

int dequeueArray(struct ArrayQueue* q) {
    if (isEmptyArray(q)) {
        printf("Queue is empty\n");
        return -1;
    }
    int item = q->items[q->front];
    if (q->front == q->rear) {
        q->front = q->rear = -1;
    } else {
        q->front = (q->front + 1) % MAX;
    }
    return item;
}

void printArrayQueue(struct ArrayQueue* q) {
    if (isEmptyArray(q)) {
        printf("Queue is empty\n");
        return;
    }
    printf("Queue: ");
    int i = q->front;
    while (1) {
        printf("%d ", q->items[i]);
        if (i == q->rear) break;
        i = (i + 1) % MAX;
    }
    printf("\n");
}

void initLinkedListQueue(struct LinkedListQueue* q) {
    q->front = NULL;
    q->rear = NULL;
}

int isEmptyLinkedList(struct LinkedListQueue* q) {
    return q->front == NULL;
}

void enqueueLinkedList(struct LinkedListQueue* q, int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;
    if (isEmptyLinkedList(q)) {
        q->front = newNode;
        q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
    printf("%d enqueued to queue\n", value);
}

int dequeueLinkedList(struct LinkedListQueue* q) {
    if (isEmptyLinkedList(q)) {
        printf("Queue is empty\n");
        return -1;
    }
    struct Node* temp = q->front;
    int item = temp->data;
    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    free(temp);
    return item;
}

void printLinkedListQueue(struct LinkedListQueue* q) {
    if (isEmptyLinkedList(q)) {
        printf("Queue is empty\n");
        return;
    }
    struct Node* temp = q->front;
    printf("Queue: ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}
