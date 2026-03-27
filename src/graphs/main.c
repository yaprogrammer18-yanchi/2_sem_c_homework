#include "TownsCountries.h"
#include "features.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Container {
    Town** allTowns;
    Country** allCountries;
    int quantityOfTowns;
    int quantityOfCountries;
} Container;

void containerFree(Container* cont)
{
    freeTownArr(cont->allTowns, cont->quantityOfTowns);
    freeCountryArr(cont->allCountries, cont->quantityOfCountries);
    free(cont);
}

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

Container* readFileAndInitialize(char* filename)
{
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Ошибка открытия файла\n");
        return NULL;
    }
    int quantityOfTowns = 0;
    int quantityOfConections = 0;
    if (!(fscanf(file, "%d %d", &quantityOfTowns, &quantityOfConections) == 2)) {
        fclose(file);
        return NULL;
    }

    if (quantityOfTowns <= 0 || quantityOfTowns > 1000000 || quantityOfConections < 0 || quantityOfConections > 1000000) {
        fclose(file);
        return NULL;
    }

    Town** allTowns = calloc(quantityOfTowns, sizeof(Town*));
    if (allTowns == NULL) {
        fclose(file);
        return NULL;
    }
    int size = 0;
    int townNum1 = 0;
    int townNum2 = 0;
    int roadLen = 0;
    for (int i = 0; i < quantityOfConections; i++) {
        if (fscanf(file, "%d %d %d", &townNum1, &townNum2, &roadLen) == 3) {
            Town* newT1 = NULL;
            Town* newT2 = NULL;

            if (!alreadyCreatedTown(allTowns, townNum1, size)) {
                if (size < quantityOfTowns) {
                    newT1 = townCreate(townNum1);
                    allTowns[size] = newT1;
                    size++;
                }
            } else {
                newT1 = getTown(allTowns, townNum1, size);
            }

            if (!alreadyCreatedTown(allTowns, townNum2, size)) {
                if (size < quantityOfTowns) {
                    newT2 = townCreate(townNum2);
                    allTowns[size] = newT2;
                    size++;
                }
            } else {
                newT2 = getTown(allTowns, townNum2, size);
            }
            townAddNeighbour(newT1, newT2, roadLen);
            townAddNeighbour(newT2, newT1, roadLen);
        } else {
            fclose(file);
            return NULL;
        }
    }
    int quantityOfCountries = 0;

    if (!(fscanf(file, "%d", &quantityOfCountries) == 1)) {
        fclose(file);
        freeTownArr(allTowns, quantityOfTowns);
        return NULL;
    }
    if (quantityOfCountries <= 0 || quantityOfCountries > quantityOfTowns || quantityOfCountries > 1000000) {
        fclose(file);
        freeTownArr(allTowns, quantityOfTowns);
        return NULL;
    }

    Country** allCountries = calloc(quantityOfCountries, sizeof(Country*));
    if (allCountries == NULL) {
        freeTownArr(allTowns, quantityOfTowns);
        fclose(file);
        return NULL;
    }
    int cSize = 0;
    int capitalNum = 0;
    for (int j = 0; j < quantityOfCountries; j++) {
        if (fscanf(file, "%d", &capitalNum) == 1) {
            Country* newCountry = createCountry(j + 1);
            countryAddTown(newCountry, getTown(allTowns, capitalNum, quantityOfTowns));
            allCountries[cSize] = newCountry;
            cSize++;
        } else {
            freeTownArr(allTowns, quantityOfTowns);
            freeCountryArr(allCountries, quantityOfCountries);
            fclose(file);
            return NULL;
        }
    }
    Container* res = calloc(1, sizeof(Container));
    if (res == NULL) {
        freeTownArr(allTowns, quantityOfTowns);
        freeCountryArr(allCountries, quantityOfCountries);
        fclose(file);
        return NULL;
    }
    res->allTowns = allTowns;
    res->quantityOfTowns = quantityOfTowns;
    res->quantityOfCountries = quantityOfCountries;
    res->allCountries = allCountries;
    fclose(file);
    return res;
}

void completeTask(Container* cont)
{
    if (cont == NULL) {
        return;
    }
    algorithm(cont->allCountries, cont->allTowns, cont->quantityOfCountries, cont->quantityOfTowns);
    printCountryTowns(cont->allCountries, cont->quantityOfCountries);
}
int main(int argc, char* argv[])
{
    if (argc < 2) {
        return 1;
    }

    Container* cont = readFileAndInitialize(argv[1]);
    completeTask(cont);
    containerFree(cont);
    return 0;
}
