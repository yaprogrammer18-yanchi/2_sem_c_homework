#pragma once
#include "TownsCountries.h"
#include <stdbool.h>
#include <stdio.h>

typedef struct MinHeap MinHeap;
MinHeap* heapCreate(size_t capacity);
void heapFree(MinHeap* h);
bool heapPush(MinHeap* h, Town* node);
Town* heapPop(MinHeap* h);
int heapEmpty(const MinHeap* h);
size_t heapSize(const MinHeap* h);
