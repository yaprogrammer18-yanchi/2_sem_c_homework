
#include "TownsCountries.h"
#include "features.h"
#include "minHeap.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// тесты для модуля с городами и странами

void testTownCreate(void)
{
    Town* town = townCreate(1);
    assert(town != NULL);
    assert(belongsToAnyCountry(town) == false);
    freeTown(town);
}

void testCountryCreate(void)
{
    Country* country = createCountry(5);
    assert(country != NULL);
    freeCountry(country);
}

void testCountryAddTown(void)
{
    Country* country = createCountry(1);
    Town* town1 = townCreate(1);
    Town* town2 = townCreate(2);
    Town* town3 = townCreate(3);
    countryAddTown(country, town1);
    countryAddTown(country, town2);
    countryAddTown(country, town3);
    assert(belongsToThisCountry(town2, 1) == true);
    assert(belongsToThisCountry(town3, 1) == true);
    freeTown(town1);
    freeTown(town2);
    freeTown(town3);
    freeCountry(country);
}

void testBelongsToThisCountry(void)
{
    Country* country = createCountry(10);
    Town* town1 = townCreate(1);
    Town* town2 = townCreate(2);
    Town* town3 = townCreate(3);
    countryAddTown(country, town1);
    countryAddTown(country, town2);
    assert(belongsToThisCountry(town1, 10) == true);
    assert(belongsToThisCountry(town2, 10) == true);
    assert(belongsToThisCountry(town3, 10) == false);
    assert(belongsToThisCountry(town1, 5) == false);
    freeTown(town1);
    freeTown(town2);
    freeTown(town3);
    freeCountry(country);
}

void testBelongsToAnyCountry(void)
{
    Country* country = createCountry(1);
    Town* town1 = townCreate(1);
    Town* town2 = townCreate(2);
    countryAddTown(country, town1);
    assert(belongsToAnyCountry(town1) == true);
    assert(belongsToAnyCountry(town2) == false);
    assert(belongsToAnyCountry(NULL) == false);
    freeTown(town1);
    freeTown(town2);
    freeCountry(country);
}

void testTownConnectedToTown(void)
{
    Town* town1 = townCreate(1);
    Town* town2 = townCreate(2);
    Town* town3 = townCreate(3);
    townAddNeighbour(town1, town2, 10);
    townAddNeighbour(town2, town1, 10);
    assert(townConnectedToTown(town1, town2) == true);
    assert(townConnectedToTown(town2, town1) == true);
    assert(townConnectedToTown(town1, town3) == false);
    assert(townConnectedToTown(town2, town3) == false);
    assert(townConnectedToTown(NULL, town1) == false);
    freeTown(town1);
    freeTown(town2);
    freeTown(town3);
}

void testGetLength(void)
{
    Town* town1 = townCreate(1);
    Town* town2 = townCreate(2);
    Town* town3 = townCreate(3);
    townAddNeighbour(town1, town2, 25);
    townAddNeighbour(town2, town1, 25);
    assert(getLength(town1, town2) == 25);
    assert(getLength(town2, town1) == 25);
    assert(getLength(town1, town3) == -1);
    assert(getLength(NULL, town1) == -1);
    freeTown(town1);
    freeTown(town2);
    freeTown(town3);
}

void testTownConnectedToCountryTowns(void)
{
    Country* country = createCountry(1);
    Town* currentTown = townCreate(0);
    Town* town1 = townCreate(1);
    Town* town2 = townCreate(2);
    Town* town3 = townCreate(3);
    Town* town4 = townCreate(4);
    countryAddTown(country, town1);
    countryAddTown(country, town2);
    countryAddTown(country, town3);
    countryAddTown(country, town4);
    townAddNeighbour(currentTown, town1, 10);
    townAddNeighbour(currentTown, town2, 20);
    townAddNeighbour(currentTown, town4, 40);
    townAddNeighbour(town1, town3, 30);
    Town** connected = townsConnectedToCountryTowns(country, currentTown);
    assert(connected != NULL);
    int count = 0;
    while (connected[count] != NULL) {
        count++;
    }
    assert(count == 3);
    bool hasTown1 = false, hasTown2 = false, hasTown4 = false;
    for (int i = 0; i < count; i++) {
        if (connected[i] == town1)
            hasTown1 = true;
        if (connected[i] == town2)
            hasTown2 = true;
        if (connected[i] == town4)
            hasTown4 = true;
        assert(connected[i] != town3);
    }
    assert(hasTown1 && hasTown2 && hasTown4);
    free(connected);
    freeTown(currentTown);
    freeTown(town1);
    freeTown(town2);
    freeTown(town3);
    freeTown(town4);
    freeCountry(country);
}

void testEdgeCases(void)
{
    assert(townsConnectedToCountryTowns(NULL, NULL) == NULL);
    assert(townConnectedToTown(NULL, NULL) == false);
    assert(getLength(NULL, NULL) == -1);
    Country* emptyCountry = createCountry(1);
    Town* someTown = townCreate(1);
    Town** result = townsConnectedToCountryTowns(emptyCountry, someTown);
    assert(result == NULL);
    Country* country = createCountry(2);
    Town* town1 = townCreate(1);
    Town* town2 = townCreate(2);
    Town* isolatedTown = townCreate(3);
    countryAddTown(country, town1);
    countryAddTown(country, town2);
    Town** result2 = townsConnectedToCountryTowns(country, isolatedTown);
    assert(result2 == NULL);
    freeTown(someTown);
    freeTown(town1);
    freeTown(town2);
    freeTown(isolatedTown);
    freeCountry(emptyCountry);
    freeCountry(country);
}

void testTownsNeighbourCheck(void)
{
    Town* town1 = townCreate(1);
    Town* town2 = townCreate(2);
    Town* town3 = townCreate(3);

    assert(!townConnectedToTown(town1, town2));
    assert(!townConnectedToTown(town1, town3));

    townAddNeighbour(town1, town2, 8);
    assert(townConnectedToTown(town1, town2));
    assert(!townConnectedToTown(town1, town3));
    assert(getLength(town1, town2) == 8);
    int length = getLength(town1, town2);
    assert(length != -1);
    townAddNeighbour(town1, town3, 5);
    assert(townConnectedToTown(town1, town3));
    assert(getLength(town1, town3) == 5);
    freeTown(town1);
    freeTown(town2);
    freeTown(town3);
}

void testIsConnectedToCountry(void)
{
    Country* country = createCountry(1);
    Town* c1 = townCreate(1);
    Town* c2 = townCreate(2);
    Town* outside = townCreate(3);
    countryAddTown(country, c1);
    countryAddTown(country, c2);
    assert(isConnectedToCountry(country, outside) == false);
    townAddNeighbour(outside, c1, 10);
    assert(isConnectedToCountry(country, outside) == true);
    assert(isConnectedToCountry(NULL, outside) == false);
    assert(isConnectedToCountry(country, NULL) == false);
    freeTown(c1);
    freeTown(c2);
    freeTown(outside);
    freeCountry(country);
}

void testCountryAndTownMiniFunctions(void)
{
    Country* country = createCountry(42);
    Town* t1 = townCreate(1);
    Town* t2 = townCreate(2);
    assert(getCountrySize(country) == 0);
    assert(countryGetNumber(country) == 42);
    assert(getCountrySize(NULL) == -1);
    assert(countryGetNumber(NULL) == -1);
    assert(getCountryTowns(NULL) == NULL);
    assert(getTownNumber(NULL) == -1);
    countryAddTown(country, t1);
    countryAddTown(country, t2);
    assert(getCountrySize(country) == 2);
    Town** arr = getCountryTowns(country);
    assert(arr != NULL);
    assert(getTownNumber(arr[0]) == 1 || getTownNumber(arr[0]) == 2);
    assert(getTownNumber(arr[1]) == 1 || getTownNumber(arr[1]) == 2);
    assert(getTownNumber(t1) == 1);
    assert(getTownNumber(t2) == 2);
    freeTown(t1);
    freeTown(t2);
    freeCountry(country);
}

// тесты для кучи

void testHeapCreateAndFree(void)
{
    MinHeap* h = heapCreate(4);
    assert(h != NULL);
    assert(heapEmpty(h));
    assert(heapSize(h) == 0);
    heapFree(h);
}

void testSinglePushAndPop(void)
{
    MinHeap* h = heapCreate(1);
    Town* t = townCreate(1);
    HeapNode* n = createNode(t, 10);
    assert(heapPush(h, n));
    assert(!heapEmpty(h));
    assert(heapSize(h) == 1);
    HeapNode* m = heapPop(h);
    assert(m == n);
    assert(getTownFromHeapNode(m) == t);
    assert(heapEmpty(h));
    assert(heapSize(h) == 0);
    free(m);
    freeTown(t);
    heapFree(h);
}

void testHeapOrder(void)
{
    MinHeap* h = heapCreate(2);
    Town* t1 = townCreate(1);
    Town* t2 = townCreate(2);
    Town* t3 = townCreate(3);
    HeapNode* n1 = createNode(t1, 5);
    HeapNode* n2 = createNode(t2, 3);
    HeapNode* n3 = createNode(t3, 7);
    heapPush(h, n1);
    heapPush(h, n2);
    heapPush(h, n3);
    HeapNode* p = NULL;
    p = heapPop(h);
    assert(getTownFromHeapNode(p) == t2);
    free(p);
    p = heapPop(h);
    assert(getTownFromHeapNode(p) == t1);
    free(p);
    p = heapPop(h);
    assert(getTownFromHeapNode(p) == t3);
    free(p);
    assert(heapEmpty(h));
    freeTown(t1);
    freeTown(t2);
    freeTown(t3);
    heapFree(h);
}

void testHeapNullCases(void)
{
    MinHeap* h = heapCreate(2);
    assert(!heapPush(NULL, NULL));
    assert(!heapPush(h, NULL));
    assert(heapPop(NULL) == NULL);
    assert(heapPop(h) == NULL);

    heapFree(h);
}

// тесты для features

void testAreThereAnyTownsLeft(void)
{
    int n = 3;
    Town* towns[n];
    for (int i = 0; i < n; i++) {
        towns[i] = townCreate(i + 1);
    }
    assert(areThereAnyTownsLeft(towns, n) == true);

    Country* c = createCountry(1);
    countryAddTown(c, towns[0]);
    countryAddTown(c, towns[1]);
    assert(areThereAnyTownsLeft(towns, n) == true);
    countryAddTown(c, towns[2]);
    assert(areThereAnyTownsLeft(towns, n) == false);
    for (int i = 0; i < n; i++) {
        freeTown(towns[i]);
    }
}

int main(void)
{
    testTownCreate();
    testCountryCreate();
    testCountryAddTown();
    testBelongsToThisCountry();
    testBelongsToAnyCountry();
    testTownConnectedToTown();
    testGetLength();
    testTownConnectedToCountryTowns();
    testEdgeCases();
    testIsConnectedToCountry();
    testCountryAndTownMiniFunctions();
    testHeapCreateAndFree();
    testSinglePushAndPop();
    testHeapOrder();
    testHeapNullCases();
    printf("ВСЕ ТЕСТЫ ПРОЙДЕНЫ УСПЕШНО!\n");
    return 0;
}
