#pragma once
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Town Town;

typedef struct Country Country;

Town* townCreate(int number);
Country* createCountry(int number);
void countryAddTown(Country* country, Town* town);
bool belongsToThisCountry(Town* town, int numberOfCountry);
bool belongsToAnyCountry(Town* town);
bool townConnectedToTown(Town* town1, Town* town2);

// функция получения длины между двумя городами
// принимает два города, возвращает длину между ними
// если города не связаны дорогой или хотя бы 1 из них NULL возвращает -1
int getLength(Town* town1, Town* town2);

// функция, возвращающая города страны, которые связаны с данным городом
// на вход принимает страну и город
// возвращает указатель на NULL-терминированный массив
Town** townsConnectedToCountryTowns(Country* country, Town* town);
void townAddNeighbour(Town* town, Town* neighbour, int length);
// void freeTown(Town* town);
// void freeCountry(Country* country);
int getCountrySize(Country* country);
int countryGetNumber(Country* country);
Town** getCountryTowns(Country* country);
int getTownNumber(Town* town);
bool isConnectedToCountry(Country* country, Town* town);
