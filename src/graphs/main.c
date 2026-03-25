#include "TownsCountries.h"
#include "features.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct container {
    Town** allTowns;
    Country** allCountries;
    int quantityOfTowns;
    int quantityOfCountries;
} container;

bool alreadyCreatedTown(Town** allTowns, int num, int quantityOfTowns)
{
    for (int i = 0; i < quantityOfTowns; i++) {
        if (getTownNumber(allTowns[i]) == num) {
            return true;
        }
    }
    return false;
}

Town* getTown(Town** allTowns, int num, int quantityOfTowns)
{
    for (int i = 0; i < quantityOfTowns; i++) {
        if (getTownNumber(allTowns[i]) == num) {
            return allTowns[i];
        }
    }
    return NULL;
}

container* readFileAndInitialize(char* filename)
{
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Ошибка открытия файла\n");
        return NULL;
    }
    int quantityOfTowns = 0;
    int quantityOfConections = 0;
    if (!(fscanf(file, "%d %d", &quantityOfTowns, &quantityOfConections) == 2)) {
        return NULL;
    }
    Town** allTowns = calloc(quantityOfTowns, sizeof(Town*));
    int size = 0;
    int townNum1 = 0;
    int townNum2 = 0;
    int roadLen = 0;
    for (int i = 0; i < quantityOfConections; i++) {
        if (fscanf(file, "%d %d %d", &townNum1, &townNum2, &roadLen) == 3) {
            Town* newT1 = NULL;
            Town* newT2 = NULL;
            if (!alreadyCreatedTown(allTowns, townNum1, quantityOfTowns)) {
                newT1 = townCreate(townNum1);
                allTowns[size] = newT1;
                size++;
            } else {
                newT1 = getTown(allTowns, townNum1, quantityOfTowns);
            }
            if (!alreadyCreatedTown(allTowns, townNum2, quantityOfTowns)) {
                newT2 = townCreate(townNum2);
                allTowns[size] = newT2;
                size++;
            } else {
                newT2 = getTown(allTowns, townNum2, quantityOfTowns);
            }
            townAddNeighbour(newT1, newT2, roadLen);
            townAddNeighbour(newT2, newT1, roadLen);
        } else {
            printf("Ошибка чтения чисел\n");
        }
    }
    int quantityOfCountries = 0;

    if (!(fscanf(file, "%d", &quantityOfCountries) == 1)) {
        return NULL;
    }
    Country** allCountries = calloc(quantityOfCountries, sizeof(Country*));
    int cSize = 0;
    int capitalNum = 0;
    for (int j = 0; j < quantityOfCountries; j++) {
        if (fscanf(file, "%d", &capitalNum) == 1) {
            Country* newCountry = createCountry(j + 1);
            countryAddTown(newCountry, getTown(allTowns, capitalNum, quantityOfTowns));
            allCountries[cSize] = newCountry;
            cSize++;
        }
    }
    container* res = calloc(1, sizeof(container));
    res->allTowns = allTowns;
    res->quantityOfTowns = quantityOfTowns;
    res->quantityOfCountries = quantityOfCountries;
    res->allCountries = allCountries;
    fclose(file);
    return res;
}

void completeTask(container* cont)
{
    algorithm(cont->allCountries, cont->allTowns, cont->quantityOfCountries, cont->quantityOfTowns);
    printCountryTowns(cont->allCountries, cont->quantityOfCountries);
}

int main(void)
{
    container* cont = readFileAndInitialize("/home/yanchi/2_sem_repo/src/graphs/matrix.txt");
    completeTask(cont);
    return 0;
}
