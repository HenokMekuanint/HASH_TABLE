#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "hashtable.h"
#include <assert.h>

#define BUCKET_COUNT 1024
#define TABLE_SIZE 1024
#define MAX_NAME 1024

struct Binding
{
    const char *key;
    int value;
    struct Binding *next;
};

struct HashTable
{
    struct Binding *buckets[BUCKET_COUNT];
};
struct HashTable *create()
{
    struct HashTable *table;
    table = (struct HashTable *)calloc(1, sizeof(struct HashTable));
    return table;
};

unsigned int hash(const char *key)
{
    int length = strnlen(key, MAX_NAME);
    unsigned int hash_value = 0;
    for (int i = 0; i < length; i++)
    {
        hash_value += key[i];
        hash_value = (hash_value * key[i]) % TABLE_SIZE;
    }
    return hash_value;
};

bool add(struct HashTable *table, const char *key, int value)
{
    int h = hash(key);
    struct Binding *a;
    struct Binding* bd = table->buckets[h];
    if(bd == NULL){
        struct Binding *p = (struct Binding *)malloc(sizeof(struct Binding));
        p->key = key;
        p->value = value;
        p->next = NULL;
        table->buckets[h] = p;
        return true;
    }
    struct Binding* prev;
    for (a = table->buckets[h]; a != NULL; a = a->next)
    {
        if(a->key == key)
        {
            a->value = value;
            return false;
        };
        prev = a;
    }


    struct Binding *p = (struct Binding *)malloc(sizeof(struct Binding));
    p->key = key;
    p->value = value;
    p->next = NULL;
    prev->next = p;
    return true;
};

struct Binding *find(struct HashTable *table, char *key)
{
    struct Binding *p;
    int h = hash(key);
    if (table->buckets[h] == NULL)
        return NULL;
    for (p = table->buckets[h]; p != NULL; p = p->next)
    {         
        if(p->key == key)
        {
            return p;
        };
    };
    return NULL;
};

bool remove(struct HashTable *table, const char *key)
{

    struct Binding *p;
    int h = hash(key);
    if (table->buckets[h] == NULL)
        return false;
    if (table->buckets[h]->key == key)
    {
        struct Binding* bd = table->buckets[h];
        p = bd->next;
        free(bd);
        table->buckets[h] = p;
        return true;
    }

    for (p = table->buckets[h]; p != NULL; p = p->next)
    {
        if (p->next != NULL && strcmp(p->next->key, key) == 0)
        {
            struct Binding *old_bd = p->next;
            p->next = old_bd->next;
            free(old_bd);
            return true;
        }
    }
    return false;
};

void delete_table(struct HashTable *table)
{
    struct Binding *p;
    struct Binding *nextp;
    int b;
    for (b = 0; b < BUCKET_COUNT; b++)
        for (p = table->buckets[b]; p != NULL; p = nextp)
        {
            nextp = p->next;
            free(p);
        }
    free(table);
}