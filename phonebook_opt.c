#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "phonebook_opt.h"
#include "phonebook_metaphone.h"

entry *findName(char lastname[], entry *pHead, entry **ht)
{
    entry *temp;
    int value = hash(lastname);
    temp = ht[value];
    while(temp != NULL) {
        if (strcmp(lastname, temp->lastName) == 0)
            return temp;
        temp = temp->pNext;
    }
    return NULL;
}

entry *append(char lastName[], entry *pHead, entry **ht)
{
    int value = hash(lastName);
    entry *e = ht[value];

    if (e) {
        while (e->pNext != NULL) {
            e = e->pNext;
        }
        e->pNext = (entry *) malloc(sizeof(entry));
        strcpy(e->pNext->lastName, lastName);
        metaphone(lastName, e->metaph, 16);
    } else {
        e = (entry *) malloc(sizeof(entry));
        strcpy(e->lastName, lastName);
        metaphone(lastName, e->metaph, 16);
        ht[value] = e;
    }
    return NULL;
}

entry **imple_hash_table(entry **ht)
{
    ht = malloc(HASH_SIZE * sizeof(entry *));
    for (int i = 0; i < HASH_SIZE; i++) {
        ht[i] = NULL;
    }
    return ht;
}

int hash(char *key)
{
    int value = 0;
    while (*key != '\0') {
        value = (value >> 4) + ((value & 15) << 14);
        value += *key;
        value &= 0x3ffff;
        key++;
    }
    return value;
}

void freeNode(entry *pHead, entry **ht)
{
    for (int i = 0; i < HASH_SIZE; i++) {
        if (ht[i] != NULL)
            free(ht[i]);
    }
    free(ht);
}

int count_hash_buckets(entry **ht)
{
    int count = 0;
    for (int i = 0; i < HASH_SIZE; i++) {
        if (ht[i]) {
            count++;
        }
    }
    return count;
}

void display_hash_imformation(entry **ht)
{
    float loadFactor = (float)count_hash_buckets(ht) / (float)HASH_SIZE;
    printf("there are %d out of %d NULL buckets in hash table: %f\n",
           HASH_SIZE - count_hash_buckets(ht), HASH_SIZE, loadFactor);
}
