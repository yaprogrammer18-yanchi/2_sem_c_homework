#include "csvConverter.h"
#include "tests.h"
#include <stdbool.h>
#include <string.h>

/*
Ограничения для пользователя:
        по кол-ву строк  в input.csv - 100
        по длине строки  в input.csv - 256
        по длине 1 слова в input.csv - 99
В input.csv данные записаны корректно и без ошибок
отсутствие пустых ячеек ",," в заголовках
*/

int main(int argc, char* argv[])
{
    if (argc > 1 && strcmp(argv[1], "--test") == 0) {
        printf("Запуск тестов...\n");
        tests();
        return 0;
    }
    // пример работы (из условия задачи)
    printTable("src/CSVprettyPrinter/testInput2.csv", "src/CSVprettyPrinter/output.txt");
    return 0;
}
