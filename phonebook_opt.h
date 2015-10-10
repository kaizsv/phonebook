#ifndef _PHONEBOOK_OPT_H
#define _PHONEBOOK_OPT_H
#include <stdbool.h>

#define MAX_LAST_NAME_SIZE 16

/* original version */
typedef struct __LAST_NAME_ENTRY {
    char lastName[MAX_LAST_NAME_SIZE];
    bool red;
    struct __PHONE_BOOK_ENTRY *pDetail;
    struct __LAST_NAME_ENTRY *pLeft;
    struct __LAST_NAME_ENTRY *pRight;
    struct __LAST_NAME_ENTRY *pParent;
} lastnameEntry;

typedef struct __PHONE_BOOK_ENTRY {
    char firstName[16];
    char email[16];
    char phone[10];
    char cell[10];
    char addr1[16];
    char addr2[16];
    char city[16];
    char state[2];
    char zip[5];
} entry;

lastnameEntry *findName(char lastname[], lastnameEntry *pHead);
lastnameEntry *append(char lastName[], lastnameEntry *pHead);
lastnameEntry *leftRotate(lastnameEntry *pHead, lastnameEntry *x);
lastnameEntry *rightRotate(lastnameEntry *pHead, lastnameEntry *x);
lastnameEntry *insertRBTree(lastnameEntry *pHead, lastnameEntry *newEntry);
lastnameEntry *insertFixUp(lastnameEntry *pHead, lastnameEntry *z);
void freeRBTree(lastnameEntry *pHead);

#endif
