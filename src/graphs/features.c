#include "TownsCountries.h"
#include "minHeap.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

printCountryTowns(Country** arrWithCountries, int quantity)
{
    for (int i = 0; i < quantity; i++) {
        int cSize = getCountrySize(arrWithCountries[i]);
        if (cSize != -1) {
            print("Государство № %d содержит города: ", countryGetNumber(arrWithCountries[i]));
            // проверки на корректно полученне значения
            for (int j = 0; j < cSize; j++) {
                print("%d ", getTownNumber(getCountryTowns(arrWithCountries[i])[j]));
            }
            printf("\n");
        }
    }
}

void algorithm(Country** allCountries, Town** allTowns, int quantityOfCountries, int quantityOftowns)
{
    while (allTowns) {
        for (int i = 0; i < quantityOfCountries; i++) {

            MinHeap* tempHeap = heapCreate(4);

            for (int j = 0; j < quantityOftowns; j++) {
                // проверяем, что город никому не принадлежит
                if (!belongsToAnyCountry(allTowns[j])) {

                    // проверяем, что он связан хоть с одним городом этой страны
                    if (isConnectedToCountry(allCountries[i], allTowns[j])) {
                        // получаем список всех городов страны, с которыми связан текущий город
                        Town** townsConnected = townsConnectedToCountryTowns(allCountries[i], allTowns[j]);
                        // смотрим, какая минимальная длина дороги от этого города до какого-н. города гос-ва
                        int min = 100000;
                        int k = 0;
                        while (townsConnected[k] != NULL) {
                            int len = getLength(allTowns[j], townsConnected[k]);
                            if (len <= min) {
                                min = len;
                            }
                            k++;
                        }
                        HeapNode* newHeapNode = createNode(allTowns[j], min);
                        heapPush(tempHeap, newHeapNode);
                    }
                }
            }

            // добавляем ближаший город и чистим кучу
            countryAddTown(allCountries[i], heapPop(tempHeap));
            heapFree(tempHeap);
        }
    }
}
