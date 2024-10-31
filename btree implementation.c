#include <stdio.h>
#include <stdlib.h>

int MAX, MIN;

struct BTreeNode {
    int *keys;
    struct BTreeNode **child;
    int n;
    int leaf;
};

struct BTreeNode *createNode(int leaf) {
    struct BTreeNode *node = (struct BTreeNode *)malloc(sizeof(struct BTreeNode));
    node->leaf = leaf;
    node->n = 0;
    node->keys = (int *)malloc((MAX) * sizeof(int));
    node->child = (struct BTreeNode **)malloc((MAX + 1) * sizeof(struct BTreeNode *));
    for (int i = 0; i < MAX + 1; i++)
        node->child[i] = NULL;
    return node;
}

void inorder(struct BTreeNode *root) {
    if (root != NULL) {
        for (int i = 0; i < root->n; i++) {
            if (!root->leaf)
                inorder(root->child[i]);
            printf("%d ", root->keys[i]);
        }
        if (!root->leaf)
            inorder(root->child[root->n]);
    }
}

void preorder(struct BTreeNode *root) {
    if (root != NULL) {
        for (int i = 0; i < root->n; i++) {
            printf("%d ", root->keys[i]);
            if (!root->leaf)
                preorder(root->child[i]);
        }
        if (!root->leaf)
            preorder(root->child[root->n]);
    }
}

void postorder(struct BTreeNode *root) {
    if (root != NULL) {
        for (int i = 0; i < root->n; i++) {
            if (!root->leaf)
                postorder(root->child[i]);
        }
        if (!root->leaf)
            postorder(root->child[root->n]);
        for (int i = 0; i < root->n; i++)
            printf("%d ", root->keys[i]);
    }
}

struct BTreeNode *search(struct BTreeNode *root, int k) {
    int i = 0;
    while (i < root->n && k > root->keys[i])
        i++;
    if (i < root->n && k == root->keys[i])
        return root;
    if (root->leaf)
        return NULL;
    return search(root->child[i], k);
}

void splitChild(struct BTreeNode *parent, int i, struct BTreeNode *fullChild) {
    struct BTreeNode *newNode = createNode(fullChild->leaf);
    newNode->n = MIN - 1;
    for (int j = 0; j < MIN - 1; j++)
        newNode->keys[j] = fullChild->keys[j + MIN];
    if (!fullChild->leaf) {
        for (int j = 0; j < MIN; j++)
            newNode->child[j] = fullChild->child[j + MIN];
    }
    fullChild->n = MIN - 1;
    for (int j = parent->n; j >= i + 1; j--)
        parent->child[j + 1] = parent->child[j];
    parent->child[i + 1] = newNode;
    for (int j = parent->n - 1; j >= i; j--)
        parent->keys[j + 1] = parent->keys[j];
    parent->keys[i] = fullChild->keys[MIN - 1];
    parent->n += 1;
}

void insertNonFull(struct BTreeNode *node, int k) {
    int i = node->n - 1;
    if (node->leaf) {
        while (i >= 0 && k < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = k;
        node->n += 1;
    } else {
        while (i >= 0 && k < node->keys[i])
            i--;
        i++;
        if (node->child[i]->n == MAX) {
            splitChild(node, i, node->child[i]);
            if (k > node->keys[i])
                i++;
        }
        insertNonFull(node->child[i], k);
    }
}

struct BTreeNode *insert(struct BTreeNode *root, int k) {
    if (root == NULL) {
        root = createNode(1);
        root->keys[0] = k;
        root->n = 1;
    } else {
        if (root->n == MAX) {
            struct BTreeNode *newRoot = createNode(0);
            newRoot->child[0] = root;
            splitChild(newRoot, 0, root);
            int i = (newRoot->keys[0] < k) ? 1 : 0;
            insertNonFull(newRoot->child[i], k);
            root = newRoot;
        } else {
            insertNonFull(root, k);
        }
    }
    return root;
}

void deleteKey(struct BTreeNode *node, int k) {
    int idx = 0;
    while (idx < node->n && node->keys[idx] < k)
        idx++;

    if (idx < node->n && node->keys[idx] == k) {
        if (node->leaf) {
            for (int j = idx + 1; j < node->n; j++)
                node->keys[j - 1] = node->keys[j];
            node->n--;
        } else {
            if (node->child[idx]->n >= MIN) {
                struct BTreeNode *predecessor = node->child[idx];
                while (!predecessor->leaf)
                    predecessor = predecessor->child[predecessor->n];
                node->keys[idx] = predecessor->keys[predecessor->n - 1];
                deleteKey(node->child[idx], node->keys[idx]);
            } else if (node->child[idx + 1]->n >= MIN) {
                struct BTreeNode *successor = node->child[idx + 1];
                while (!successor->leaf)
                    successor = successor->child[0];
                node->keys[idx] = successor->keys[0];
                deleteKey(node->child[idx + 1], node->keys[idx]);
            } else {
                merge(node, idx);
                deleteKey(node->child[idx], k);
            }
        }
    } else {
        if (node->leaf) {
            printf("Key %d not found in the tree.\n", k);
            return;
        }
        
        int shouldDelete = (idx == node->n) ? 1 : 0;

        if (node->child[idx]->n < MIN) {
            if (idx != 0 && node->child[idx - 1]->n >= MIN) {
                borrowFromPrev(node, idx);
            } else if (idx != node->n && node->child[idx + 1]->n >= MIN) {
                borrowFromNext(node, idx);
            } else {
                if (idx != node->n)
                    merge(node, idx);
                else
                    merge(node, idx - 1);
            }
        }
        deleteKey(node->child[idx], k);
    }
}

int main() {
    struct BTreeNode *root = NULL;
    int choice, key;
    printf("Enter the maximum number of keys a node can hold: ");
    scanf("%d", &MAX);
    MIN = (MAX + 1) / 2;
    printf("\n1. Insert\n2. Delete\n3. Search\n4. Inorder Traversal\n5. Preorder Traversal\n6. Postorder Traversal\n7. Exit\n");
    while (1) {
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter the key to insert: ");
                scanf("%d", &key);
                root = insert(root, key);
                break;
            case 2:
                printf("Delete function is not implemented.\n");
                break;
            case 3:
                printf("Enter the key to search: ");
                scanf("%d", &key);
                (search(root, key) != NULL) ? printf("Key %d found\n", key) : printf("Key %d not found\n", key);
                break;
            case 4:
                printf("Inorder Traversal: ");
                inorder(root);
                printf("\n");
                break;
            case 5:
                printf("Preorder Traversal: ");
                preorder(root);
                printf("\n");
                break;
            case 6:
                printf("Postorder Traversal: ");
                postorder(root);
                printf("\n");
                break;
            case 7:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}
