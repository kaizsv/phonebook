#ifndef _PHONEBOOK_OPT_H
#define _PHONEBOOK_OPT_H
#include <stdbool.h>

#define MAX_LAST_NAME_SIZE 16

/* original version */
typedef struct __PHONE_BOOK_ENTRY {
    char lastName[MAX_LAST_NAME_SIZE];
    bool red;
    struct __PHONE_BOOK_ENTRY *pDetail;
    struct __PHONE_BOOK_ENTRY *pLeft;
    struct __PHONE_BOOK_ENTRY *pRight;
    struct __PHONE_BOOK_ENTRY *pParent;
} entry;

typedef struct __PHONE_BOOK_DETIAL {
    char firstName[16];
    char email[16];
    char phone[10];
    char cell[10];
    char addr1[16];
    char addr2[16];
    char city[16];
    char state[2];
    char zip[5];
} detial;

entry *findName(char lastname[], entry *pHead);
entry *append(char lastName[], entry *pHead);
entry *leftRotate(entry *pHead, entry *x);
entry *rightRotate(entry *pHead, entry *x);
entry *insert_rbtree(entry *pHead, entry *newEntry);
entry *fixContinuousRed(entry *pHead, entry *z);
void freeNodepHead(entry *pHead);
entry *imple_pHead(entry *pHead);
entry *pointer2pHead(entry *pHead, entry *e);
#endif
