#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "phonebook_opt.h"

/* FILL YOUR OWN IMPLEMENTATION HERE! */
lastnameEntry *findName(char lastname[], lastnameEntry *pHead)
{
    /* TODO: implement */
    lastnameEntry *e = pHead;
    int a = 0;
    while (e != NULL) {
        a = strcasecmp(lastname, e->lastName);
        if (a > 0) {
            e = e->pRight;
        } else if (a < 0) {
            e = e->pLeft;
        } else {
            return e;
        }
    }
    return NULL;
}

lastnameEntry *append(char lastName[], lastnameEntry *pHead)
{
    lastnameEntry *temp;
    temp = malloc(sizeof(lastnameEntry));
    strcpy(temp->lastName, lastName);
    pHead = insertRBTree(pHead, temp);
    return pHead;
}

lastnameEntry *leftRotate(lastnameEntry *pHead, lastnameEntry *x)
{
    lastnameEntry *y;
    y = x->pRight;
    x->pRight = y->pLeft;
    if (y->pLeft) {
        y->pLeft->pParent = x;
    }
    y->pParent = x->pParent;
    if (x->pParent == NULL) {
        pHead = y;
    } else if (x == x->pParent->pLeft) {
        x->pParent->pLeft = y;
    } else {
        x->pParent->pRight = y;
    }
    y->pLeft = x;
    x->pParent = y;
    return pHead;
}

lastnameEntry *rightRotate(lastnameEntry *pHead, lastnameEntry *x)
{
    lastnameEntry *y;
    y = x->pLeft;
    x->pLeft = y->pRight;
    if (y->pRight) {
        y->pRight->pParent = x;
    }
    y->pParent = x->pParent;
    if (x->pParent == NULL) {
        pHead = y;
    } else if (x == x->pParent->pLeft) {
        x->pParent->pLeft = y;
    } else {
        x->pParent->pRight = y;
    }
    y->pRight = x;
    x->pParent = y;
    return pHead;
}

lastnameEntry *insertRBTree(lastnameEntry *pHead, lastnameEntry *newEntry)
{
    lastnameEntry *y = NULL;
    lastnameEntry *x = pHead;
    while (x) {
        y = x;
        if (strcasecmp(newEntry->lastName, x->lastName) < 0) {
            x = x->pLeft;
        } else {
            x = x->pRight;
        }
    }
    newEntry->pParent = y;
    if (y == NULL) {
        pHead = newEntry;
        pHead->pLeft = NULL;
        pHead->pRight = NULL;
        pHead->red = false;
        return pHead;
    } else if (strcasecmp(newEntry->lastName, y->lastName) < 0) {
        y->pLeft = newEntry;
    } else {
        y->pRight = newEntry;
    }
    newEntry->pLeft = NULL;
    newEntry->pRight = NULL;
    newEntry->red = true;
    pHead = insertFixUp(pHead, newEntry);
    return pHead;
}

lastnameEntry *insertFixUp(lastnameEntry *pHead, lastnameEntry *z)
{
    lastnameEntry *y = NULL;
    while (z->pParent->red) {
        if (z->pParent == z->pParent->pParent->pLeft) {
            y = z->pParent->pParent->pRight;
            if (y == NULL || !y->red) {
                if (z == z->pParent->pRight) {
                    z = z->pParent;
                    pHead = leftRotate(pHead, z);
                }
                z->pParent->red = false;
                z->pParent->pParent->red = true;
                pHead = rightRotate(pHead, z->pParent->pParent);
            } else {
                z->pParent->red = false;
                y->red = false;
                z->pParent->pParent->red = true;
                z = z->pParent->pParent;
            }
        } else {
            y = z->pParent->pParent->pLeft;
            if (y == NULL || !y->red) {
                if (z == z->pParent->pLeft) {
                    z = z->pParent;
                    pHead = rightRotate(pHead, z);
                }
                z->pParent->red = false;
                z->pParent->pParent->red = true;
                pHead = leftRotate(pHead, z->pParent->pParent);
            } else {
                z->pParent->red = false;
                y->red = false;
                z->pParent->pParent->red = true;
                z = z->pParent->pParent;
            }
        }
        if (z->pParent == NULL) {
            break;
        }
    }
    pHead->red = false;
    return pHead;
}

void freeRBTree(lastnameEntry *pHead)
{
    lastnameEntry *e, *curr;
    e = pHead;
    while (e) {
        if (e->pLeft) {
            e = e->pLeft;
            continue;
        } else if (e->pRight) {
            e = e->pRight;
            continue;
        }
        curr = e;
        e = e->pParent;
        if (e) {
            if (e->pLeft == curr) {
                e->pLeft = NULL;
            } else {
                e->pRight = NULL;
            }
        }
        free(curr);
    }
}
