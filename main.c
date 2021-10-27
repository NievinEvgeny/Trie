#include "trie.h"
#include <stdio.h>
#include <time.h>

void printMenu()
{
    printf("1. Добавить элемент\n");
    printf("2. Удалить элемент\n");
    printf("3. Вывести все элементы\n");
    printf("4. Значение по ключу\n");
    printf("5. Выход\n");
}

int main()
{
    FILE* stream;
    char* ewords;
    struct Trie* head = trieCreate();
    char words[50];
    stream = fopen("output.txt", "r");
    if (stream == NULL)
    {
        printf("Ошибка: не удалось открыть файл");
        return 0;
    }

    clock_t time_start;
    clock_t time_end;

    time_start = clock();
    for (int i = 0; i < 100000; i++)
    {
        ewords = fgets(words, sizeof(words), stream);
        if (ewords == NULL)
        {
            break;
        }
        trieInsert(&head, words, i);
        // printf("%s\n", words);
    }
    time_end = clock() - time_start;
    printf("insert = %lf\n", (double)time_end / CLOCKS_PER_SEC);

    rewind(stream);

    time_start = clock();
    for (int i = 0; i < 100000; i++)
    {
        ewords = fgets(words, sizeof(words), stream);
        if (ewords == NULL)
        {
            break;
        }
        trieLookup(head, words); //Без вывода
    }
    time_end = clock() - time_start;
    printf("lookup = %lf\n", (double)time_end / CLOCKS_PER_SEC);

    rewind(stream);

    time_start = clock();
    for (int i = 0; i < 100000; i++)
    {
        ewords = fgets(words, sizeof(words), stream);
        if (ewords == NULL)
        {
            break;
        }
        trieDelete(&head, words);
    }
    time_end = clock() - time_start;
    printf("delete = %lf\n", (double)time_end / CLOCKS_PER_SEC);

    /* User interface
    char key[30];
    int item;
    int value;
    system("clear");
    while (item != 5)
    {
        printMenu();
        scanf("%d", &item);
        switch (item)
        {
        case 1:
            system("clear");
            printf("Введите ключ (строчные буквы латинского алфавита)\n");
            scanf("%s", key);
            printf("Введите значение\n");
            scanf("%d", &value);
            trieInsert(&head, key, value);
            system("clear");
            break;
        case 2:
            system("clear");
            printf("Введите ключ\n");
            scanf("%s", key);
            trieDelete(&head, key);
            system("clear");
            break;
        case 3:
            system("clear");
            triePrint(head, words);
            break;
        case 4:
            system("clear");
            printf("Введите ключ\n");
            scanf("%s", key);
            system("clear");
            trieLookup(head, key);
            break;
        }
    }*/
}