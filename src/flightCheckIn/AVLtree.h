#include <stdbool.h>
#include <stdio.h>

typedef struct TreeNode TreeNode;
typedef struct AVL AVL;

AVL* avlCreate(void);
char* find(AVL* tree, const char* code);
void avlDeleteNode(AVL* tree, const char* code);
void avlPush(AVL* tree, const char* code, const char* name);
void avlFree(AVL* tree);
void avlInorder(AVL* tree);
bool isEmpty(AVL* tree);
void avlSave(AVL* tree, const char* filename);
int avlSize(AVL* tree);