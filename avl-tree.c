#include <stdio.h>
#include <stdlib.h>

#define ALLOWED_IMBALANCE 1

typedef struct AVLNode {
    int data;
    int height;
    struct AVLNode* left;
    struct AVLNode* right;
} AVLNode;

AVLNode* createNode(int data);
AVLNode* searchNode(int data, AVLNode* tree);
void insertNode(int data, AVLNode** treePointer);
void removeNode(int data, AVLNode** treePointer);

int max(int a, int b);
int getHeight(AVLNode* tree);
AVLNode* findMinNode(AVLNode* tree);
AVLNode* findMaxNode(AVLNode* tree);

void balanceTree(AVLNode** treePointer);
void rotateWithLeftChild(AVLNode** k2Pointer);
void rotateWithRightChild(AVLNode** k1Poinnter);
void doubleWithLeftChild(AVLNode** k3Pointer);
void doubleWithRightChild(AVLNode** k3Pointer);

void printAVLTreeRecur(AVLNode* tree, int layer);
void printAVLTree(AVLNode* tree);
void printHints();

int main() {
    AVLNode* tree = NULL;
    int tempData;
    char command;

    printHints();
    while (1) {
        while ((command = getchar()) == '\n');

        switch(command) {
            case 'S':
                printf("Please enter the data that you want to search:\n");
                scanf("%d", &tempData);
                AVLNode* result = searchNode(tempData, tree);
                if (result == NULL) printf("The data you entered is not in the AVL Tree.\n");
                else {
                    printf("Search data: %d\n", tempData);
                    printf("The address of the node: %p\n", result);
                    printf("The height of the node: %d\n", result->height);
                    printf("To know exactly where the node is, you can use command 'P' to print the tree.\n");
                }
                break;
            case 'I':
                printf("Please enter the data that you want to insert to the AVL Tree:\n");
                scanf("%d", &tempData);
                insertNode(tempData, &tree);
                printf("After Insertion: \n");
                printAVLTree(tree);
                break;
            case 'R':
                printf("Please enter the data that you want to remove from the AVL Tree:\n");
                scanf("%d", &tempData);
                removeNode(tempData, &tree);
                printf("After removal:\n");
                printAVLTree(tree);
                break;
            case 'P':
                printAVLTree(tree);
                break;
            case 'Q':
                return 0;
            default:
                printf("Unknown command. Please try again.\n");
        }
        printHints();
    }
    return 0;
}

AVLNode* createNode(int data) {
    AVLNode* node = (AVLNode*)malloc(sizeof(AVLNode));
    node->data = data;
    node->height = 0;
    node->left = NULL, node->right = NULL;
}

AVLNode* searchNode(int data, AVLNode* tree) {
    if (tree == NULL) return NULL;

    if (data < tree->data) return searchNode(data, tree->left);
    else if (data > tree->data) return searchNode(data, tree->right);
    return tree;
}

void insertNode(int data, AVLNode** treePointer) {
    AVLNode* tree = *treePointer;
    if (tree == NULL) *treePointer = createNode(data);
    else if (data < tree->data) insertNode(data, &tree->left);
    else if (data > tree->data) insertNode(data, &tree->right);

    balanceTree(treePointer);
}

void removeNode(int data, AVLNode** treePointer) {
    AVLNode* tree = *treePointer;
    if (tree == NULL) return;

    if (data < tree->data) removeNode(data, &tree->left);
    else if (data > tree->data) removeNode(data, &tree->right);
    else if (tree->left != NULL && tree->right != NULL) {
        tree->data = findMinNode(tree->right)->data;
        removeNode(tree->data, &tree->right);
    } else {
        AVLNode* oldNode = tree;
        (*treePointer) = (tree->left != NULL) ? tree->left : tree->right;
        free(oldNode);
    }
}

int max(int a, int b) {
    return (a >= b) ? a : b;
}

int getHeight(AVLNode* tree) {
    if (tree == NULL) return -1;
    return tree->height;
}

AVLNode* findMinNode(AVLNode* tree) {
    while (tree->left != NULL) tree = tree->left;
    return tree;
}

AVLNode* findMaxNode(AVLNode* tree) {
    while (tree->right != NULL) tree = tree->right;
    return tree;
}

void balanceTree(AVLNode** treePointer) {
    if (treePointer == NULL | *treePointer == NULL) return;
    AVLNode* tree = *treePointer;
    if (getHeight(tree->left) - getHeight(tree->right) > ALLOWED_IMBALANCE) {
        if (getHeight(tree->left->left) >= getHeight(tree->left->right)) {
            rotateWithLeftChild(treePointer);
        } else {
            doubleWithLeftChild(treePointer);
        }
    } else if (getHeight(tree->right) - getHeight(tree->left) > ALLOWED_IMBALANCE) {
        if (getHeight(tree->right->right) >= getHeight(tree->right->left)) {
            rotateWithRightChild(treePointer);
        } else {
            doubleWithRightChild(treePointer);
        }
    }

    tree->height = max(getHeight(tree->left), getHeight(tree->right)) + 1;
}

void rotateWithLeftChild(AVLNode** k2Pointer) {
    AVLNode* k2 = *k2Pointer;
    AVLNode* k1 = k2->left;

    k2->left = k1->right;
    k1->right = k2;
    k2->height = max(getHeight(k2->left), getHeight(k2->right)) + 1;
    k1->height = max(getHeight(k1->left), getHeight(k1->right)) + 1;

    *k2Pointer = k1;
}

void rotateWithRightChild(AVLNode** k1Pointer) {
    AVLNode* k1 = *k1Pointer;
    AVLNode* k2 = k1->right;

    k1->right = k2->left;
    k2->left = k1;
    k1->height = max(getHeight(k1->left), getHeight(k1->right)) + 1;
    k2->height = max(getHeight(k2->left), getHeight(k2->right)) + 1;

    *k1Pointer = k2;
}

void doubleWithLeftChild(AVLNode** k3Pointer) {
    AVLNode* k3 = *k3Pointer;
    rotateWithRightChild(&(k3->left));
    rotateWithLeftChild(k3Pointer);
}

void doubleWithRightChild(AVLNode** k1Pointer) {
    AVLNode* k1 = *k1Pointer;
    rotateWithLeftChild(&(k1->right));
    rotateWithRightChild(k1Pointer);
}

void printAVLTreeRecur(AVLNode* tree, int layer) {
    if (tree == NULL) return;

    for (int i = 0; i < layer; i++) printf("-");
    printf("%d\n", tree->data);

    printAVLTreeRecur(tree->left, layer + 1);
    printAVLTreeRecur(tree->right, layer + 1);
}

void printAVLTree(AVLNode* tree) {
    printf("\n");
    printf("The current AVL tree is:\n");
    for (int i = 0; i < 20; i++) printf("-");
    printf("\n");
    printAVLTreeRecur(tree, 0);
    for (int i = 0; i < 20; i++) printf("-");
    printf("\n\n");
}

void printHints() {
    printf("Which operation do you want to perform on the AVL Tree?\n");
    printf("'S' to search whether the data is already in this AVL Tree.\n");
    printf("'I' to insert a node with data you entered.\n");
    printf("'R' to remove a node with data you entered.\n");
    printf("'P' to print the current AVL Tree.\n");
    printf("'Q' to quit the program.\n");
    printf("IMPORTANT: You can only enter ONE character at one time!!!\n");
}
