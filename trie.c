#include "trie.h"
#include <stdio.h>
#include <stdlib.h>

struct Trie* trieCreate()
{
    struct Trie* node = (struct Trie*)malloc(sizeof(struct Trie));
    node->isLeaf = 0;
    node->value = 0;
    for (int i = 0; i < ALPHABET; i++)
    {
        node->character[i] = NULL;
    }
    return node;
}

int isLeaf(struct Trie* node)
{
    return node->isLeaf;
}

void Print(struct Trie* root, char str[], int level)
{
    if (root == NULL)
    {
        printf("Дерево пустое\n");
        return;
    }
    if (isLeaf(root))
    {
        str[level] = '\0';
        printf("%s = %d\n", str, root->value);
    }
    for (int i = 0; i < ALPHABET; i++)
    {
        if (root->character[i])
        {
            str[level] = i + 'a';
            Print(root->character[i], str, level + 1);
        }
    }
}

// Аргумент по умолчанию
void triePrint(struct Trie* root, char str[])
{
    int level = 0;
    Print(root, str, level);
}

int trieLookup(struct Trie* root, char* str)
{
    if (root == NULL)
    {
        printf("Дерево пустое: ");
        return 0;
    }
    struct Trie* curr = root;
    while (*str)
    {
        curr = curr->character[*str - 'a'];
        if (curr == NULL)
        {
            printf("Ключ не найден: ");
            return 0;
        }
        str++;
    }
    return curr->value;
}

void trieInsert(struct Trie** root, char* str, int value)
{
    if (*root == NULL)
    {
        *root = trieCreate();
    }
    struct Trie* curr = *root;
    while (*str)
    {
        // Добавление узла в массив
        if (curr->character[*str - 'a'] == NULL)
        {
            curr->character[*str - 'a'] = trieCreate();
        }
        // Переход к след. узлу
        curr = curr->character[*str - 'a'];
        // Переход к след. букве
        str++;
    }
    curr->isLeaf = 1;
    curr->value = value;
}

int hasChildren(struct Trie* curr)
{
    for (int i = 0; i < ALPHABET; i++)
    {
        if (curr->character[i])
        {
            return 1; // Дочерний узел найден
        }
    }
    return 0;
}

int trieDelete(struct Trie** curr, char* str)
{
    // Дерево пустое
    if (*curr == NULL)
    {
        return 0;
    }
    // Пока не достигнут конец строки
    if (*str)
    {
        // Доходим до конца строки, встречаем '\0', переходим к следующему if-у,
        // в зависимости от того, что получили в if-е (при конце строки) удаляем
        // узлы до того момента, пока у узла не будет ещё одного дочернего узла
        if (*curr != NULL && (*curr)->character[*str - 'a'] != NULL && trieDelete(&((*curr)->character[*str - 'a']), str + 1) && (*curr)->isLeaf == 0)
        {
            if (!hasChildren(*curr))
            {
                free(*curr);
                (*curr) = NULL;
                return 1;
            }
            else
            {
                return 0;
            }
        }
    }
    // Попадаем сюда когда доходим до '\0'
    if (*str == '\0' && (*curr)->isLeaf)
    {
        // Если текущий узел - лист, и не имеет дочерних узлов
        if (!hasChildren(*curr))
        {
            free(*curr); // Удаляем текущий узел
            (*curr) = NULL;
            return 1; // Получив 1, в предыдущем if-е также будем
                      // удалять рекурсивно узлы без дочерних узлов
        }
        // Если текущий узел листовой и имеет дочерние узлы
        else
        {
            // Помечаем узел как не листовой и зануляем его значение
            (*curr)->isLeaf = 0;
            (*curr)->value = 0;
            return 0; // Не удаляем узел в предыдущем if-е, т.к. данное
                      // слово является частью другого
        }
    }
    return 0;
}