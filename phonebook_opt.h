#ifndef _PHONEBOOK_OPT_H
#define _PHONEBOOK_OPT_H

#define MAX_LAST_NAME_SIZE 16
#define HASH_SIZE 262147

/* original version */
typedef struct __PHONE_BOOK_ENTRY {
    char lastName[MAX_LAST_NAME_SIZE];
    int hashvalue;
    struct __PHONE_BOOK_DETIAL *pDetial;
    struct __PHONE_BOOK_ENTRY *pNext;
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

entry *findName(char lastname[], entry *pHead, entry **ht);
entry *append(char lastName[], entry *pHead, entry **ht);
entry **imple_hash_table(entry **ht);
int hash(char *lastName);
void freeNode(entry *pHead, entry **ht);
int count_hash_buckets(entry **ht);
void display_hash_imformation(entry **ht);

#endif
