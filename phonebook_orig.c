#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "phonebook_orig.h"

/* original version */
entry *findName(char lastname[], entry *pHead, entry **ht)
{
    while (pHead != NULL) {
        if (strcasecmp(lastname, pHead->lastName) == 0)
            return pHead;
        pHead = pHead->pNext;
    }
    return NULL;
}

entry *append(char lastName[], entry *e, entry **ht)
{
    /* allocate memory for the new entry and put lastName */
    e->pNext = (entry *) malloc(sizeof(entry));
    e = e->pNext;
    strcpy(e->lastName, lastName);
    e->pNext = NULL;

    return e;
}

entry **imple_hash_table(entry **ht)
{
    return NULL;
}

void freeNode(entry *pHead, entry **ht)
{
    entry *temp = pHead;
    while (temp) {
        pHead = pHead->pNext;
        free(temp);
        temp = pHead;
    }
}

void display_hash_imformation(entry **ht)
{
    //NOTHING TO DO
}
