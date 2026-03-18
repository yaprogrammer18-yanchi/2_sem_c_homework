#include "AVLtree.h"
#include <assert.h>
#include <string.h>

void testCreateAndFree(void)
{
    AVL* tree = avlCreate();
    assert(tree != NULL);
    assert(isEmpty(tree));
    avlPush(tree, "TEST", "Test Airport");
    assert(!isEmpty(tree));
    avlFree(tree);
}

void testInsertAndFind(void)
{
    AVL* tree = avlCreate();
    avlPush(tree, "SVO", "Sheremetyevo");
    avlPush(tree, "DME", "Domodedovo");
    avlPush(tree, "VKO", "Vnukovo");
    avlPush(tree, "LED", "Pulkovo");
    avlPush(tree, "KZN", "Kazan");
    char* name = find(tree, "SVO");
    printf("%s\n", name);
    assert(name != NULL && "не найден элемент SVO");
    assert(strcmp(name, "Sheremetyevo") == 0);
    name = find(tree, "LED");
    assert(name != NULL);
    assert(strcmp(name, "Pulkovo") == 0);
    name = find(tree, "ZZZ");
    assert(name == NULL);
    avlFree(tree);
}

void testDelete(void)
{
    AVL* tree = avlCreate();

    avlPush(tree, "SVO", "Sheremetyevo");
    avlPush(tree, "DME", "Domodedovo");
    avlPush(tree, "VKO", "Vnukovo");
    avlPush(tree, "LED", "Pulkovo");

    printf("  До удаления: ");

    avlDeleteNode(tree, "LED");
    assert(find(tree, "LED") == NULL);
    printf("  После удаления LED: ");

    avlDeleteNode(tree, "VKO");
    assert(find(tree, "VKO") == NULL);
    printf("  После удаления VKO: ");

    avlDeleteNode(tree, "SVO");
    assert(find(tree, "SVO") == NULL);
    printf("  После удаления SVO: ");

    avlDeleteNode(tree, "ZZZ");
    avlFree(tree);
}

int main(void)
{
    testCreateAndFree();
    testInsertAndFind();
    testDelete();
}
