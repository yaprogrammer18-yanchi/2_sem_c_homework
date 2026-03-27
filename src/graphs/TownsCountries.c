#include "TownsCountries.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Town {
    int number;
    bool belongsToCountry;
    int country;
    struct Town** neighbours;
    int* lengthToNeighbours;
    int size;
} Town;

typedef struct Country {
    int number;
    struct Town** towns;
    int size;

} Country;

Town* townCreate(int number)
{
    Town* newTown = calloc(1, sizeof(Town));
    if (newTown == NULL) {
        return NULL;
    }
    newTown->number = number;
    newTown->belongsToCountry = false;
    newTown->size = 0;
    return newTown;
}

Country* createCountry(int number)
{
    Country* newCountry = calloc(1, sizeof(Country));
    if (newCountry == NULL) {
        return NULL;
    }
    newCountry->number = number;
    return newCountry;
}

void countryAddTown(Country* country, Town* town)
{
    if (country == NULL || town == NULL) {
        return;
    }

    if (country->size == 0) {
        country->towns = calloc(1, sizeof(Town*));
        if (country->towns == NULL) {
            return;
        }
    } else {
        Town** tmp = realloc(country->towns, (country->size + 1) * sizeof(Town*));
        if (tmp == NULL) {
            return;
        }
        country->towns = tmp;
    }
    country->towns[country->size] = town;
    country->size++;
    town->belongsToCountry = true;
    town->country = country->number;
}

bool belongsToThisCountry(Town* town, int numberOfCountry)
{
    if (town->belongsToCountry) {
        return town->country == numberOfCountry;
    }
    return false;
}

bool belongsToAnyCountry(Town* town)
{
    if (town == NULL) {
        return false;
    }
    return town->belongsToCountry;
}

bool townConnectedToTown(Town* town1, Town* town2)
{
    if (town1 == NULL || town2 == NULL) {
        return false;
    }
    int size = town1->size;
    for (int i = 0; i < size; i++) {
        if ((town1->neighbours)[i]->number == town2->number) {
            return true;
        }
    }
    return false;
}

// функция получения длины между двумя городами
// принимает два города, возвращает длину между ними
// если города не связаны дорогой или хотя бы 1 из них NULL возвращает -1
int getLength(Town* town1, Town* town2)
{
    if (town1 == NULL || town2 == NULL) {
        return -1;
    }
    int size = town1->size;
    for (int i = 0; i < size; i++) {
        if ((town1->neighbours)[i]->number == town2->number) {
            return town1->lengthToNeighbours[i];
        }
    }
    // а что если дорога из другого города в первый короче?
    return -1;
}

void townAddNeighbour(Town* town, Town* neighbour, int length)
{
    if (town == NULL || neighbour == NULL) {
        return;
    }
    if (town->size == 0) {
        town->neighbours = calloc(1, sizeof(Town*));
        if (town->neighbours == NULL) {
            return;
        }
        town->neighbours[town->size] = neighbour;

        town->lengthToNeighbours = calloc(1, sizeof(int));
        if (town->lengthToNeighbours == NULL) {
            return;
        }
        town->lengthToNeighbours[town->size] = length;
        town->size++;
    } else {
        Town** tmp = realloc(town->neighbours, sizeof(Town*) * (town->size + 1));
        if (tmp == NULL) {
            return;
        }
        town->neighbours = tmp;
        int* lenTmp = realloc(town->lengthToNeighbours, sizeof(int) * (town->size + 1));
        if (lenTmp == NULL) {
            return;
        }
        town->lengthToNeighbours = lenTmp;
        town->lengthToNeighbours[town->size] = length;
        town->neighbours[town->size] = neighbour;
        town->size++;
    }
}

// функция, возвращающая города страны, которые связаны с данным городом
// на вход принимает страну и город
// возвращает указатель на NULL-терминированный массив
Town** townsConnectedToCountryTowns(Country* country, Town* town)
{
    if (country == NULL || town == NULL || town->neighbours == NULL) {
        return NULL;
    }
    int size = country->size;
    Town** arr = calloc(size, sizeof(Town*));

    if (arr == NULL) {
        free(arr);
        return NULL;
    }
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (townConnectedToTown(town, country->towns[i])) {
            arr[count] = country->towns[i];
            count++;
        }
    }
    if (count > 0) {
        Town** reallocatedArr = realloc(arr, (count + 1) * (sizeof(Town*)));
        if (reallocatedArr == NULL) {
            free(arr);
            return NULL;
        }
        arr = reallocatedArr;
        // это нужно чтобы  найти размер этого массива, если понадобится
        arr[count] = NULL;
    }
    return arr;
}

bool isConnectedToCountry(Country* country, Town* town)
{
    if (country == NULL || town == NULL || town->neighbours == NULL) {
        return false;
    }
    int size = country->size;
    for (int i = 0; i < size; i++) {
        if (townConnectedToTown(town, country->towns[i])) {
            return true;
        }
    }
    return false;
}

// void freeTown(Town* town);

// void freeCountry(Country* country);

int getCountrySize(Country* country)
{
    if (country == NULL) {
        return -1;
    }
    return country->size;
}

int countryGetNumber(Country* country)
{
    {
        if (country == NULL) {
            return -1;
        }
        return country->number;
    }
}

Town** getCountryTowns(Country* country)
{
    {
        if (country == NULL) {
            return NULL;
        }
        return country->towns;
    }
}

int getTownNumber(Town* town)
{
    if (town == NULL) {
        return -1;
    }

    return town->number;
}
