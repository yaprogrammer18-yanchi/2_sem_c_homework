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
    assert(name != NULL && "не найден элемент SVO");
    assert(strcmp(name, "Sheremetyevo") == 0);
    name = find(tree, "LED");
    assert(name != NULL);
    assert(strcmp(name, "Pulkovo") == 0);
    name = find(tree, "ZZZ");
    assert(name == NULL);
    avlFree(tree);
}

void testSizeAndEmpty(void)
{
    AVL* tree = avlCreate();
    assert(tree != NULL);
    assert(isEmpty(tree));
    assert(avlSize(tree) == 0);

    avlPush(tree, "SVO", "Sheremetyevo");
    assert(!isEmpty(tree));
    assert(avlSize(tree) == 1);

    avlPush(tree, "DME", "Domodedovo");
    avlPush(tree, "VKO", "Vnukovo");
    assert(avlSize(tree) == 3);

    avlPush(tree, "SVO", "Sheremetyevo Updated");
    assert(avlSize(tree) == 3);

    avlDeleteNode(tree, "DME");
    assert(avlSize(tree) == 2);

    avlDeleteNode(tree, "ZZZ");
    assert(avlSize(tree) == 2);

    avlFree(tree);
}

void testUpdateExistingKey(void)
{
    AVL* tree = avlCreate();
    avlPush(tree, "SVO", "Sheremetyevo");
    char* name = find(tree, "SVO");
    assert(name != NULL);
    assert(strcmp(name, "Sheremetyevo") == 0);
    avlPush(tree, "SVO", "Sheremetyevo International");
    name = find(tree, "SVO");
    assert(name != NULL);
    assert(strcmp(name, "Sheremetyevo International") == 0);
    assert(avlSize(tree) == 1);

    avlFree(tree);
}

void testSaveAndLoad(void)
{
    const char* filename = "test_airports.txt";
    {
        AVL* tree = avlCreate();
        avlPush(tree, "SVO", "Sheremetyevo");
        avlPush(tree, "LED", "Pulkovo");
        avlPush(tree, "JFK", "John F Kennedy");
        avlSave(tree, filename);
        avlFree(tree);
        AVL* tree2 = loadBase(filename);
        assert(tree2 != NULL);
        char* name = find(tree2, "SVO");
        assert(name != NULL && strcmp(name, "Sheremetyevo") == 0);
        name = find(tree2, "LED");
        assert(name != NULL && strcmp(name, "Pulkovo") == 0);
        name = find(tree2, "JFK");
        assert(name != NULL && strcmp(name, "John F Kennedy") == 0);
        assert(avlSize(tree2) == 3);
        avlFree(tree2);
    }
}

void testDeleteCases(void)
{
    AVL* tree = avlCreate();
    avlPush(tree, "M", "M");
    avlPush(tree, "F", "F");
    avlPush(tree, "T", "T");
    avlPush(tree, "B", "B");
    avlPush(tree, "H", "H");
    avlDeleteNode(tree, "B");
    assert(find(tree, "B") == NULL);
    avlDeleteNode(tree, "F");
    assert(find(tree, "F") == NULL);
    assert(find(tree, "H") != NULL);
    avlDeleteNode(tree, "M");
    assert(find(tree, "M") == NULL);
    assert(find(tree, "H") != NULL);
    assert(find(tree, "T") != NULL);
    avlFree(tree);
}

int main(void)
{
    testCreateAndFree();
    testInsertAndFind();
    testSizeAndEmpty();
    testUpdateExistingKey();
    testDeleteCases();
    testSaveAndLoad();
    printf("All tests passed!\n");
    return 0;
}
