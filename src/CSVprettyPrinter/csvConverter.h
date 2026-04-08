#pragma once
#include <stdbool.h>
#include <stdio.h>
typedef struct Table Table;
Table* readCsv(const char* filepath);
bool printTable(const char* filepathInput, const char* filepathOutput);
void freeTable(Table* table);

// функции, которые нужны для тестов
int quantityOfCols(Table* table);
int arrWithAllTheWords(char** data, char** allWords, int rows, int maxWords);
void getMaxLengthOfColInArr(char** allWords, int quantityOfCols, int quantityOfRows, int* maxLengthArr);
bool freeArrInArr(char** arr, int len);
int tableGetCols(Table* table);
int tableGetRows(Table* table);
char** tableGetData(Table* table);
