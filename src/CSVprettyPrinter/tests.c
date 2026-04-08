#include "csvConverter.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool convertCsvToPlainTextTable(const char* inputPath, const char* outputPath)
{
    return printTable(inputPath, outputPath);
}

bool testRowsQuantity(void)
{
    printf("Проверка кол-ва строк...");
    Table* table = readCsv("src/CSVprettyPrinter/testInput1.csv");
    if (table == NULL || tableGetRows(table) != 6) {
        freeTable(table);
        return false;
    }
    freeTable(table);

    table = readCsv("src/CSVprettyPrinter/testInput5.csv");
    if (table == NULL || tableGetRows(table) != 0) {
        freeTable(table);
        return false;
    }
    freeTable(table);

    printf("завершена успешно\n");
    return true;
}

bool testColumsQuantity(void)
{
    printf("Проверка кол-ва столбцов...");
    Table* table = readCsv("src/CSVprettyPrinter/testInput1.csv");
    if (table == NULL)
        return false;
    quantityOfCols(table);
    if (tableGetCols(table) != 5) {
        freeTable(table);
        return false;
    }
    freeTable(table);

    table = readCsv("src/CSVprettyPrinter/testInput5.csv");
    if (table == NULL)
        return false;
    quantityOfCols(table);
    if (tableGetCols(table) != 0) {
        freeTable(table);
        return false;
    }
    freeTable(table);

    printf("завершена успешно\n");
    return true;
}

bool testCheckMaxLenght(void)
{
    Table* table = readCsv("src/CSVprettyPrinter/testInput1.csv");
    if (table == NULL)
        return false;
    quantityOfCols(table);
    int words
        = tableGetRows(table) * tableGetCols(table);
    char** allWords = calloc(words, sizeof(char*));
    if (allWords == NULL) {
        freeTable(table);
        return false;
    }

    int res = arrWithAllTheWords(tableGetData(table), allWords, tableGetRows(table), words);
    if (res != 0) {
        free(allWords);
        freeTable(table);
        return false;
    }

    int* maxLengthArr = malloc(sizeof(int) * tableGetCols(table));
    if (maxLengthArr == NULL) {
        free(allWords);
        freeTable(table);
        return false;
    }

    getMaxLengthOfColInArr(allWords, tableGetCols(table), tableGetRows(table), maxLengthArr);

    int expected[5] = { 9, 6, 8, 7, 6 };
    for (int i = 0; i < tableGetCols(table); i++) {
        if (maxLengthArr[i] != expected[i]) {
            free(maxLengthArr);
            free(allWords);
            freeTable(table);
            return false;
        }
    }

    free(maxLengthArr);
    freeArrInArr(allWords, words);
    freeTable(table);
    return true;
}

bool testSimpleOccasion(void)
{
    printf("Проверка простого случая...");
    if (!convertCsvToPlainTextTable("src/CSVprettyPrinter/testInput2.csv",
            "src/CSVprettyPrinter/testOutput.txt")) {
        printf("Ошибка конвертации\n");
        return false;
    }

    const char* expected[7] = {
        "+====+========+========+\n",
        "| ID | Name   | Active |\n",
        "+====+========+========+\n",
        "|  1 | Item A | true   |\n",
        "+----+--------+--------+\n",
        "|  2 | Item B | false  |\n",
        "+----+--------+--------+\n"
    };

    FILE* file = fopen("src/CSVprettyPrinter/testOutput.txt", "r");
    if (file == NULL) {
        printf("file not found!\n");
        return false;
    }

    char buffer[256];
    int lineNum = 0;
    while (fgets(buffer, sizeof(buffer), file) != NULL && lineNum < 7) {
        if (strcmp(buffer, expected[lineNum]) != 0) {
            fclose(file);
            return false;
        }
        lineNum++;
    }
    fclose(file);

    printf("завершена успешно!\n");
    return true;
}

void tests(void)
{
    if (!testRowsQuantity()) {
        printf("Ошибка в подсчёте кол-ва строк\n");
        return;
    }
    if (!testColumsQuantity()) {
        printf("Ошибка в подсчёте кол-ва столбцов\n");
        return;
    }
    if (!testSimpleOccasion()) {
        printf("Ошибка в тестировании простого случая\n");
        return;
    }
    if (!testCheckMaxLenght()) {
        printf("Ошибка в тестировании полученных максимальных длин столбцов\n");
        return;
    }
    printf("Все тесты пройдены успешно!\n");
}