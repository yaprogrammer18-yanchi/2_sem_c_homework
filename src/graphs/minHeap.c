#include "TownsCountries.h"
#include <stdlib.h>

typedef struct MinHeap {
    struct Town** data;
    size_t size;
    size_t capacity;
} MinHeap;

static void swapNodes(Town** a, Town** b)
{
    Town* tmp = *a;
    *a = *b;
    *b = tmp;
}

typedef struct HeapNode {
    Town* town;
    int length;
} HeapNode;

int nodeGetSumLength(HeapNode* node)
{
    if (node == NULL) {
        return -1;
    }
    return node->length;
}

// функция для корректной вставки.
// Поддержание св-ва кучи.
static void siftUp(MinHeap* heap, size_t index)
{
    while (index > 0) {
        size_t parent = (index - 1) / 2;
        if (nodeGetSumLength(heap->data[parent]) <= nodeGetSumLength(heap->data[index])) {
            break;
        }
        swapNodes(&heap->data[parent], &heap->data[index]);
        index = parent;
    }
}

// функция для корректного удаления.
// Поддержание св-ва кучи.
static void siftDown(MinHeap* heap, size_t index)
{
    size_t n = heap->size;
    while (1) {
        size_t left = 2 * index + 1;
        size_t right = 2 * index + 2;
        size_t smallest = index;
        if (left < n && nodeGetSumLength(heap->data[left]) < nodeGetSumLength(heap->data[smallest])) {
            smallest = left;
        }
        if (right < n && nodeGetSumLength(heap->data[right]) < nodeGetSumLength(heap->data[smallest])) {

            smallest = right;
        }

        if (smallest == index)
            break;
        swapNodes(&heap->data[index], &heap->data[smallest]);
        index = smallest;
    }
}

MinHeap* heapCreate(size_t capacity)
{
    MinHeap* heap = malloc(sizeof(MinHeap));
    if (!heap) {
        return NULL;
    }
    heap->data = malloc(capacity * sizeof(HeapNode*));
    if (!heap->data) {
        free(heap);
        return NULL;
    }
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void heapFree(MinHeap* heap)
{
    if (!heap) {
        return;
    }
    free(heap->data);
    free(heap);
}

static bool heapResize(MinHeap* heap, size_t newCapacity)
{
    HeapNode** tmp = realloc(heap->data, newCapacity * sizeof(HeapNode*));
    if (!tmp) {
        return false;
    }
    heap->data = tmp;
    heap->capacity = newCapacity;
    return true;
}

bool heapPush(MinHeap* heap, HeapNode* node)
{
    if (!heap) {
        return false;
    }
    if (node == NULL) {
        return false;
    }
    if (heap->size == heap->capacity) {
        size_t newCap = heap->capacity ? heap->capacity * 2 : 16;
        if (!heapResize(heap, newCap))
            return false;
    }
    heap->data[heap->size] = node;
    siftUp(heap, heap->size);
    heap->size++;
    return true;
}

Town* heapPop(MinHeap* heap)
{
    if (!heap || heap->size == 0)
        return NULL;
    Town* min = heap->data[0];
    heap->size--;
    if (heap->size > 0) {
        heap->data[0] = heap->data[heap->size];
        siftDown(heap, 0);
    }
    return min;
}

int heapEmpty(const MinHeap* heap)
{
    return !heap || heap->size == 0;
}

size_t heapSize(const MinHeap* heap)
{
    return heap ? heap->size : 0;
}
