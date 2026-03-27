#pragma once
#include "TownsCountries.h"
#include <stdbool.h>
#include <stdio.h>

typedef struct MinHeap MinHeap;
typedef struct HeapNode HeapNode;
MinHeap* heapCreate(size_t capacity);
void heapFree(MinHeap* h);
bool heapPush(MinHeap* h, HeapNode* node);
HeapNode* heapPop(MinHeap* h);
int heapEmpty(const MinHeap* h);
size_t heapSize(const MinHeap* h);
HeapNode* createNode(Town* town, int len);
Town* getTownFromHeapNode(HeapNode* node);
