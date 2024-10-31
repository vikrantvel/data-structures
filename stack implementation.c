#include <stdio.h>
#include <stdlib.h>

#define MAX 5

int stackArray[MAX];
int topArray = -1;

struct Node {
    int data;
    struct Node* next;
};

struct Node* topList = NULL;

// Array-based stack functions
void pushArray(int val) {
    if (topArray == MAX - 1) {
        printf("Array Stack Overflow\n");
        return;
    }
    stackArray[++topArray] = val;
}

int popArray() {
    if (topArray == -1) {
        printf("Array Stack Underflow\n");
        return -1;
    }
    return stackArray[topArray--];
}

void displayArray() {
    if (topArray == -1) {
        printf("Array Stack is empty\n");
        return;
    }
    printf("Array Stack: ");
    for (int i = topArray; i >= 0; i--) printf("%d ", stackArray[i]);
    printf("\n");
}

// Linked list-based stack functions
void pushList(int val) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = val;
    newNode->next = topList;
    topList = newNode;
}

int popList() {
    if (topList == NULL) {
        printf("Linked List Stack Underflow\n");
        return -1;
    }
    struct Node* temp = topList;
    int popped = temp->data;
    topList = topList->next;
    free(temp);
    return popped;
}

void displayList() {
    if (topList == NULL) {
        printf("Linked List Stack is empty\n");
        return;
    }
    struct Node* temp = topList;
    printf("Linked List Stack: ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    int choice, value, stackChoice;
printf("\nChoose Stack Type:\n1. Array Stack\n2. Linked List Stack\nEnter choice (1 or 2): ");
        scanf("%d", &stackChoice);
        
    while (1) {
        

        printf("\nMenu:\n1. Insert at Beginning\n2. Delete from Beginning\n3. Display\n4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                if (stackChoice == 1) pushArray(value);
                else pushList(value);
                break;
            case 2:
                if (stackChoice == 1) popArray();
                else popList();
                break;
            case 3:
                if (stackChoice == 1) displayArray();
                else displayList();
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}
