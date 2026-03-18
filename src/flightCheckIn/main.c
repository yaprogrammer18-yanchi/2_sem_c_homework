#include "AVLtree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// подразумевается, что данные в файле корректны.
// Предусмотрена только ситуация, когда нет ":", одновременно обрабатывает пустые строки
AVL* loadBase(const char* filename)
{
    AVL* tree = avlCreate();
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Файл не найден\n");
        return NULL;
    }
    char buffer[100] = { 0 };
    while ((fgets(buffer, sizeof(buffer), file) != NULL)) {
        size_t indexOfLineBreak = strcspn(buffer, "\n");
        if (indexOfLineBreak < sizeof(buffer)) {
            buffer[indexOfLineBreak] = '\0';
        } else {
            buffer[sizeof(buffer) - 1] = '\0';
        }
        char* colon = strchr(buffer, ':');
        if (colon == NULL) {
            continue;
        }
        *colon = '\0';
        char* code = buffer;
        char* name = colon + 1;
        avlPush(tree, code, name);
    }
    fclose(file);
    return tree;
}

// просто перепись всего дерева
void save(AVL* tree, const char* filename)
{
    avlSave(tree, filename);
}

void interface(AVL* tree)
{
    printf("Вы работаете с базой аэропортов\n");
    printf("Вводите команды по следующим шаблонам. После ввода команды нажмите Enter\n");
    printf("find <код>	     - Найти название аэропорта по коду IATA\n");
    printf("add <код>:<название> - Добавить новый аэропорт в базу\n");
    printf("delete <код>         - Удалить аэропорт из базы\n");
    printf("save                 - Сохранить текущее состояние базы\n");
    printf("quit                 - Завершить работу программы\n");
    char buffer[100] = { 0 };
    while (fgets(buffer, sizeof(buffer), stdin)) {
        size_t indexOfLineBreak = strcspn(buffer, "\n");
        if (indexOfLineBreak < sizeof(buffer)) {
            buffer[indexOfLineBreak] = '\0';
        } else {
            buffer[sizeof(buffer) - 1] = '\0';
        }

        if ((strcmp(buffer, "quit") == 0)) {
            printf("Работа с базой завершена.\n");
            break;
        } else if (strcmp(buffer, "save") == 0) {
            save(tree, "src/flightCheckIn/airports.txt");
            int quantity = avlSize(tree);
            printf("База сохранена: %d аэропортов.\n", quantity);
        } else {
            char* emptySpace = strchr(buffer, ' ');
            if (emptySpace == NULL) {
                printf("Команда не распознана\n");
                continue;
            }
            *emptySpace = '\0';
            char* args = emptySpace + 1;

            if (strcmp(buffer, "find") == 0) {
                char* name = find(tree, args);
                if (name != NULL) {
                    printf("%s → %s\n", args, name);
                } else {
                    printf("Аэропорт с кодом %s не найден в базе.\n", args);
                }

            } else if (strcmp(buffer, "delete") == 0) {

                if (find(tree, args)) {
                    avlDeleteNode(tree, args);
                    printf("Аэропорт %s удален из базы.\n", args);
                } else {
                    printf("Аэропорт с кодом %s не найден в базе.\n", args);
                }

            } else if (strcmp(buffer, "add") == 0) {
                char* colon = strchr(args, ':');
                if (colon == NULL) {
                    continue;
                }
                *colon = '\0';
                char* code = args;
                char* name = colon + 1;
                avlPush(tree, code, name);
                printf("Аэропорт %s добавлен в базу.\n", args);
            }
        }
    }
}

int main()
{
    AVL* tree = loadBase("src/flightCheckIn/airports.txt");
    interface(tree);
    avlFree(tree);
    return 0;
}