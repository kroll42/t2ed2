#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "abb.h"

BTreeNode* root = NULL;

BTreeNode* createNode(char key[21], BTreeNode* child) {
    BTreeNode* newNode = (BTreeNode*)malloc(sizeof(BTreeNode));
    strcpy(newNode->keys[1], key);
    newNode->count = 1;
    newNode->link[0] = root;
    newNode->link[1] = child;
    return newNode;
}

void insertNode(char key[21]) {
    BTreeNode* newRoot;
    char upKey[21];
    int isSplit;

    newRoot = insert(root, key, upKey, &isSplit);
    if (isSplit) {
        root = createNode(upKey, newRoot);
    } else if (root == NULL) {
        root = newRoot;
    }
}

BTreeNode* insert(BTreeNode* node, char key[21], char upKey[21], int *isSplit) {
    BTreeNode* newChild;
    char newKey[21];
    int pos, i;

    if (node == NULL) {
        *isSplit = 1;
        strcpy(upKey, key);
        return NULL;
    }

    if (searchPos(key, node->keys, node->count, &pos)) {
        printf("Duplicação de chave não permitida\n");
        *isSplit = 0;
        return node;
    }

    newChild = insert(node->link[pos], key, newKey, isSplit);
    if (*isSplit) {
        if (node->count < MAX) {
            insertByShift(node, newKey, newChild, pos);
            *isSplit = 0;
        } else {
            split(node, newKey, newChild, pos, upKey, &newChild);
        }
    }
    return node;
}

int searchPos(char key[21], char keys[MAX + 1][21], int n, int *pos) {
    int low = 0, high = n - 1, mid;
    while (low <= high) {
        mid = (low + high) / 2;
        if (strcmp(key, keys[mid]) == 0) {
            *pos = mid;
            return 1;
        } else if (strcmp(key, keys[mid]) < 0) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    *pos = low;
    return 0;
}

void insertByShift(BTreeNode* node, char key[21], BTreeNode* rightChild, int pos) {
    int i;
    for (i = node->count; i > pos; i--) {
        strcpy(node->keys[i + 1], node->keys[i]);
        node->link[i + 1] = node->link[i];
    }
    strcpy(node->keys[pos + 1], key);
    node->link[pos + 1] = rightChild;
    node->count++;
}

void split(BTreeNode* node, char key[21], BTreeNode* rightChild, int pos, char upKey[21], BTreeNode** newChild) {
    int median, i;

    if (pos > MIN) {
        median = MIN + 1;
    } else {
        median = MIN;
    }

    *newChild = (BTreeNode*)malloc(sizeof(BTreeNode));
    for (i = median + 1; i <= MAX; i++) {
        strcpy((*newChild)->keys[i - median], node->keys[i]);
        (*newChild)->link[i - median] = node->link[i];
    }
    (*newChild)->count = MAX - median;
    node->count = median;

    if (pos <= MIN) {
        insertByShift(node, key, rightChild, pos);
    } else {
        insertByShift(*newChild, key, rightChild, pos - median);
    }

    strcpy(upKey, node->keys[node->count]);
    (*newChild)->link[0] = node->link[node->count];
    node->count--;
}

void displayNode(BTreeNode *root) {
    if (root) {
        int i;
        for (i = 0; i < root->count; i++) {
            displayNode(root->link[i]);
            printf("%s ", root->keys[i + 1]);
        }
        displayNode(root->link[i]);
    }
}

BTreeNode* searchNode(BTreeNode *root, char key[21]) {
    int i;
    if (root) {
        for (i = 0; i < root->count; i++) {
            if (strcmp(key, root->keys[i + 1]) == 0) {
                return root;
            } else if (strcmp(key, root->keys[i + 1]) < 0) {
                return searchNode(root->link[i], key);
            }
        }
        return searchNode(root->link[i], key);
    } else {
        return NULL;
    }
}

void destroyNode(BTreeNode *root) {
    int i;
    if (root) {
        for (i = 0; i < root->count + 1; i++) {
            destroyNode(root->link[i]);
        }
        free(root);
    }
}
