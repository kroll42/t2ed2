#ifndef ABB_H
#define ABB_H

#define MAX 4
#define MIN 2

typedef struct BTreeNode {
    char keys[MAX + 1][21]; // 20 characters + 1 for the null terminator
    int count;
    struct BTreeNode *link[MAX + 1];
} BTreeNode;

extern BTreeNode* root;  // Declaração externa da variável root

BTreeNode* createNode(char key[21], BTreeNode* child);
void insertNode(char key[21]);
BTreeNode* insert(BTreeNode* node, char key[21], char upKey[21], int *isSplit);
int searchPos(char key[21], char keys[MAX + 1][21], int n, int *pos);
void insertByShift(BTreeNode* node, char key[21], BTreeNode* rightChild, int pos);
void split(BTreeNode* node, char key[21], BTreeNode* rightChild, int pos, char upKey[21], BTreeNode** newChild);
void displayNode(BTreeNode *root);
BTreeNode* searchNode(BTreeNode *root, char key[21]);
void destroyNode(BTreeNode *root);

#endif // ABB_H
