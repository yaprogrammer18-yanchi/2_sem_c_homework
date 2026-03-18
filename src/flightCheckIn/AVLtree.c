#include "AVLtree.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct TreeNode {
    char* code;
    char* name;
    int balance;
    struct TreeNode* leftChild;
    struct TreeNode* rightChild;
} TreeNode;

typedef struct AVL {
    TreeNode* root;
    int size;
} AVL;

AVL* avlCreate(void)
{
    AVL* tree = calloc(1, sizeof(*tree));
    return tree;
}

int avlHeightRecursion(TreeNode* node)
{
    if (node == NULL) {
        return 0;
    }
    int leftHeight = avlHeightRecursion(node->leftChild);
    int rightHeight = avlHeightRecursion(node->rightChild);
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

int avlNodeHeight(TreeNode* node)
{
    if (node == NULL) {
        return 0;
    }
    int height = avlHeightRecursion(node);
    return height - 1;
}

void updateBalance(TreeNode* node)
{

    if (node == NULL) {
        return;
    }
    node->balance = avlNodeHeight(node->rightChild) - avlNodeHeight(node->leftChild);
}

TreeNode* rotateLeft(TreeNode* a)
{
    TreeNode* b = a->rightChild;
    TreeNode* c = b->leftChild;
    b->leftChild = a;
    a->rightChild = c;

    updateBalance(a);
    updateBalance(b);
    return b;
}

TreeNode* rotateRight(TreeNode* a)
{
    TreeNode* b = a->leftChild;
    TreeNode* c = b->rightChild;
    b->rightChild = a;
    a->leftChild = c;

    updateBalance(a);
    updateBalance(b);
    return b;
}

TreeNode* bigRotateLeft(TreeNode* a)
{
    TreeNode* b = a->rightChild;
    TreeNode* c = b->leftChild;
    b->leftChild = c->rightChild;
    a->rightChild = c->leftChild;
    c->leftChild = a;
    c->rightChild = b;

    updateBalance(a);
    updateBalance(b);
    updateBalance(c);
    return c;
}

TreeNode* bigRotateRight(TreeNode* a)
{
    TreeNode* b = a->leftChild;
    TreeNode* c = b->rightChild;
    a->leftChild = c->rightChild;
    b->rightChild = c->leftChild;
    c->leftChild = b;
    c->rightChild = a;

    updateBalance(a);
    updateBalance(b);
    updateBalance(c);
    return c;
}

TreeNode* balance(TreeNode* node)
{
    if (node->balance == 2) {
        if (node->rightChild->balance >= 0)
            return rotateLeft(node);
        return bigRotateLeft(node);
    }
    if (node->balance == -2) {
        if (node->leftChild->balance <= 0)
            return rotateRight(node);
        return bigRotateRight(node);
    }
    return node;
}

TreeNode* insert(TreeNode* node, const char* code, const char* name)
{
    if (node == NULL) {
        TreeNode* newNode = calloc(1, sizeof(TreeNode));
        newNode->name = malloc(strlen(name) + 1);
        newNode->code = malloc(strlen(code) + 1);
        strcpy(newNode->name, name);
        strcpy(newNode->code, code);
        newNode->balance = 0;
        return newNode;
    }

    int cmp = strcmp(code, node->code);

    if (cmp < 0) {
        node->leftChild = insert(node->leftChild, code, name);
    } else if (cmp > 0) {
        node->rightChild = insert(node->rightChild, code, name);
    }
    // обновление имени существующего узла с данным кодом.
    else {
        free(node->name);
        node->name = malloc(strlen(name) + 1);
        strcpy(node->name, name);
        return node;
    }
    updateBalance(node);
    return balance(node);
}

void avlPush(AVL* tree, const char* code, const char* name)
{
    if (tree == NULL) {
        return;
    }
    tree->root = insert(tree->root, code, name);
    tree->size++;
}

TreeNode* findMin(TreeNode* node)
{
    while (node && node->leftChild)
        node = node->leftChild;
    return node;
}

TreeNode* avlDelete(TreeNode* node, const char* code)
{
    if (node == NULL)
        return NULL;

    int cmp = strcmp(code, node->code);

    if (cmp < 0) {
        node->leftChild = avlDelete(node->leftChild, code);
    } else if (cmp > 0) {
        node->rightChild = avlDelete(node->rightChild, code);
    } else {
        if (node->leftChild == NULL) {
            TreeNode* tmp = node->rightChild;
            free(node->code);
            free(node->name);
            free(node);
            return tmp;
        } else if (node->rightChild == NULL) {
            TreeNode* tmp = node->leftChild;
            free(node->code);
            free(node->name);
            free(node);
            return tmp;
        }
        TreeNode* succ = findMin(node->rightChild);
        free(node->code);
        free(node->name);
        node->code = malloc(strlen(succ->code) + 1);
        node->name = malloc(strlen(succ->name) + 1);
        strcpy(node->code, succ->code);
        strcpy(node->name, succ->name);
        node->rightChild = avlDelete(node->rightChild, succ->code);
    }
    updateBalance(node);
    return balance(node);
}

void avlDeleteNode(AVL* tree, const char* code)
{
    if (tree == NULL || tree->root == NULL) {
        return;
    }
    tree->root = avlDelete(tree->root, code);
    tree->size--;
}

char* find(AVL* tree, const char* code)
{
    if (tree == NULL || tree->root == NULL) {
        return NULL;
    }

    TreeNode* current = tree->root;
    while (current != NULL) {
        int cmp = strcmp(code, current->code);
        if (cmp == 0) {
            return current->name;
        } else if (cmp < 0) {
            if (current->leftChild == NULL) {
                return NULL;
            }
            current = current->leftChild;
        } else if (cmp > 0) {
            if (current->rightChild == NULL) {
                return NULL;
            }
            current = current->rightChild;
        }
    }
    return NULL;
}

void avlFreeRecursion(TreeNode* node)
{
    if (node == NULL) {
        return;
    }
    avlFreeRecursion(node->leftChild);
    avlFreeRecursion(node->rightChild);
    free(node->code);
    free(node->name);
    free(node);
}

void avlFree(AVL* tree)
{
    if (tree == NULL)
        return;
    if (tree->root != NULL) {
        avlFreeRecursion(tree->root);
    }
    free(tree);
}

void avlSaveInorderRecursion(TreeNode* node, FILE* file)
{
    if (node == NULL) {
        return;
    }
    avlSaveInorderRecursion(node->leftChild, file);
    fprintf(file, "%s:%s\n", node->code, node->name);
    avlSaveInorderRecursion(node->rightChild, file);
}

void avlSave(AVL* tree, const char* filename)
{
    if (tree == NULL) {
        return;
    }
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        return;
    }
    avlSaveInorderRecursion(tree->root, file);
    fclose(file);
}

bool isEmpty(AVL* tree)
{
    return (tree->root == NULL || tree == NULL);
}

int avlSize(AVL* tree)
{
    return tree->size;
}