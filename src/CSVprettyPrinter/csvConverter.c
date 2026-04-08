#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Table {
    char** data;
    int rows;
    int cols;
    int* colWidths;
} Table;

void freeArrInArr(char** arr, int len)
{
    if (arr == NULL) {
        return;
    }
    for (int i = 0; i < len; i++) {
        free(arr[i]);
    }
    free(arr);
}

void freeTable(Table* table)
{
    if (table == NULL) {
        return;
    }
    freeArrInArr(table->data, table->rows);
    free(table->colWidths);
    free(table);
}

Table* readCsv(const char* filepath)
{
    Table* table = calloc(1, sizeof(Table));
    if (table == NULL) {
        return NULL;
    }

    table->data = calloc(100, sizeof(char*));
    if (table->data == NULL) {
        free(table);
        return NULL;
    }
    table->cols = 0;
    table->rows = 0;
    table->colWidths = NULL;

    FILE* file = fopen(filepath, "r");
    if (file == NULL) {
        freeTable(table);
        return NULL;
    }
    int linesRead = 0;
    char temporaryBuffer[256] = { 0 };
    while ((linesRead < 100) && (fgets(temporaryBuffer, sizeof(temporaryBuffer), file) != NULL)) {
        size_t indexOfLineBreak = strcspn(temporaryBuffer, "\n");
        if (indexOfLineBreak < sizeof(temporaryBuffer)) {
            temporaryBuffer[indexOfLineBreak] = '\0';
        } else {
            temporaryBuffer[sizeof(temporaryBuffer) - 1] = '\0';
        }
        char* buffer = malloc(strlen(temporaryBuffer) + 1);
        if (buffer == NULL) {
            fclose(file);
            freeTable(table);
            return NULL;
        }
        strlcpy(buffer, temporaryBuffer, 256);
        table->data[linesRead] = buffer;
        linesRead++;
    }
    fclose(file);
    table->rows = linesRead;
    return table;
}

void quantityOfCols(Table* table)
{
    if (table == NULL || table->rows == 0) {
        table->cols = 0;
        return;
    }
    int columsQuantity = 0;
    if (table->data[0] == NULL) {
        return;
    }
    size_t len = strlen(table->data[0]);
    for (size_t i = 0; i < len; i++) {
        if (table->data[0][i] == ',') {
            columsQuantity += 1;
        }
    }
    columsQuantity += 1;
    table->cols = columsQuantity;
}

int arrWithAllTheWords(char** data, char** allWords, int rows, int maxWords)
{
    /*
      Здесь формируется массив из указателей, которые
      указывают на массивы из символов (слова).
    */

    int wordIndex = 0;
    for (int row = 0; row < rows; row++) {
        int i = 0;
        int j = 0;
        char tempWordBuf[100] = { 0 };
        while (data[row][i] != '\0') {
            if (data[row][i] != ',') {
                tempWordBuf[j] = data[row][i];
                j++;
                i++;
            } else {
                tempWordBuf[j] = '\0';
                if (wordIndex >= maxWords) {
                    return -1;
                }
                allWords[wordIndex] = malloc(sizeof(char) * (j + 1));
                if (allWords[wordIndex] != NULL) {
                    strncpy(allWords[wordIndex], tempWordBuf, j + 1);
                } else {
                    return -2;
                }
                j = 0;
                i++;
                wordIndex++;
            }
        }
        if (j > 0) {
            tempWordBuf[j] = '\0';
            if (wordIndex >= maxWords) {
                return -1;
            }
            allWords[wordIndex] = malloc(sizeof(char) * (j + 1));
            strncpy(allWords[wordIndex], tempWordBuf, j + 1);
            wordIndex++;
        }
    }
    return 0;
}

void getMaxLengthOfColInArr(char** allWords, int quantityOfCols, int quantityOfRows, int* maxLengthArr)
{
    int step = quantityOfCols;
    for (int col = 0; col < quantityOfCols; col++) {
        int maxLength = 0;
        for (int word = col; word < quantityOfRows * quantityOfCols; word += step) {
            if (allWords[word] == NULL) {
                continue;
            }
            int len = (int)strlen(allWords[word]);
            if (len > maxLength) {
                maxLength = len;
            }
        }
        maxLengthArr[col] = maxLength;
    }
}

void drawLines(char symbol, FILE* outputFile, int cols, const int* maxLengths)
{
    fprintf(outputFile, "+");
    for (int col = 0; col < cols; col++) {
        for (int i = 0; i < maxLengths[col] + 2; i++) {
            fputc(symbol, outputFile);
        }
        fprintf(outputFile, "+");
    }
    fprintf(outputFile, "\n");
}

bool isNumber(const char* num)
{
    if (num == NULL || *num == '\0') {
        return false;
    }
    int i = 0;
    if (num[0] == '-') {
        i++;
        if (num[i] == '\0') {
            return false;
        }
    }
    while (num[i] != '\0') {
        if (!isdigit((unsigned char)num[i])) {
            return false;
        }
        i++;
    }
    return true;
}

bool writeTableInFile(char** allWords, const int* maxLengths, int cols, int rows, const char* filepath)
{
    if (rows == 0) {
        return false;
    }
    FILE* out = fopen(filepath, "w");
    if (out == NULL) {
        return false;
    }
    int currentWord = 0;
    // заголовок
    drawLines('=', out, cols, maxLengths);
    fprintf(out, "|");
    for (int col = 0; col < cols; col++) {
        char* word = allWords[currentWord];
        if (word != NULL && isNumber(word)) {
            fprintf(out, " %*s ", maxLengths[col], word);
        } else {
            fprintf(out, " %-*s ", maxLengths[col], word);
        }
        fprintf(out, "|");
        currentWord++;
    }
    fprintf(out, "\n");
    drawLines('=', out, cols, maxLengths);
    // обычные данные
    for (int row = 0; row < rows - 1; row++) {
        fprintf(out, "|");
        for (int col = 0; col < cols; col++) {
            char* word = allWords[currentWord];
            if (word != NULL && isNumber(word)) {
                fprintf(out, " %*s ", maxLengths[col], word);
            } else {
                fprintf(out, " %-*s ", maxLengths[col], word);
            }
            fprintf(out, "|");
            currentWord++;
        }
        fprintf(out, "\n");
        drawLines('-', out, cols, maxLengths);
    }
    fclose(out);
    return true;
}

bool printTable(const char* filepathInput, const char* filepathOutput)
{
    Table* table = readCsv(filepathInput);

    if (table == NULL) {
        printf("file not found!\n");
        freeTable(table);
        return false;
    }
    if (table->rows <= 0) {
        printf("Ошибка\n");
        freeTable(table);
        return false;
    }

    quantityOfCols(table);

    if (table->cols <= 0) {
        printf("Ошибка\n");
        freeTable(table);
        return false;
    }

    int words = table->rows * table->cols;
    char** allWords = calloc(words, sizeof(char*));

    if (allWords == NULL) {
        printf("Ошибка\n");
        freeTable(table);
        return false;
    }
    int res = arrWithAllTheWords(table->data, allWords, table->rows, words);
    if (res != 0) {
        printf("Ошибка при разборе CSV\n");
        free(allWords);
        freeTable(table);
        return false;
    }

    int* maxLengthArr = malloc(sizeof(int) * table->cols);

    if (maxLengthArr == NULL) {
        printf("Ошибка\n");
        freeTable(table);
        freeArrInArr(allWords, words);
        return false;
    }
    getMaxLengthOfColInArr(allWords, table->cols, table->rows, maxLengthArr);
    writeTableInFile(allWords, maxLengthArr, table->cols, table->rows, filepathOutput);
    free(maxLengthArr);
    freeArrInArr(allWords, words);
    freeTable(table);
    return true;
}

// функции для тестов

int tableGetCols(Table* table)
{
    if (table == NULL) {
        return -1;
    }
    return table->cols;
}

int tableGetRows(Table* table)
{
    if (table == NULL) {
        return -1;
    }
    return table->rows;
}

char** tableGetData(Table* table)
{
    if (table == NULL) {
        return NULL;
    }
    return table->data;
}
