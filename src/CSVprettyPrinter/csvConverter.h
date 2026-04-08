#pragma once
#include <stdbool.h>
#include <stdio.h>
typedef struct Table Table;
Table* readCsv(const char* filepath);
int quantityOfCols(Table* table);
int arrWithAllTheWords(char** data, char** allWords, int rows, int maxWords);
void getMaxLengthOfColInArr(char** allWords, int quantityOfCols, int quantityOfRows, int* maxLengthArr);
void drawLines(char symbol, FILE* outputFile, int cols, const int* maxLengths);
bool isNumber(const char* num);
bool writeTableInFile(char** allWords, const int* maxLengths, int cols, int rows, const char* filepath);
bool freeArrInArr(char** arr, int len);
bool printTable(const char* filepathInput, const char* filepathOutput);
int tableGetCols(Table* table);
int tableGetRows(Table* table);
char** tableGetData(Table* table);
void freeTable(Table* table);
