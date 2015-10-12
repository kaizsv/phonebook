#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "phonebook_opt.h"

entry *findName(char lastname[], entry *pHead)
{
    /* implement */
    entry *e = pHead;
    int a = 0;
    while (e != NULL) {
        if ((a = strcasecmp(lastname, e->lastName)) == 0)
            return e;
        e = (a > 0) ? e->pRight : e->pLeft;
    }
    return NULL;
}

entry *append(char lastName[], entry *pHead)
{
    entry *temp;
    temp = malloc(sizeof(entry));
    strcpy(temp->lastName, lastName);
    pHead = insert_rbtree(pHead, temp);
    return pHead;
}

entry *leftRotate(entry *pHead, entry *x)
{
    entry *y;
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

entry *rightRotate(entry *pHead, entry *x)
{
    entry *y;
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

entry *insert_rbtree(entry *pHead, entry *newEntry)
{
    entry *y = NULL;
    entry *x = pHead;
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
        strcpy(pHead->lastName, newEntry->lastName);
        return pHead;
    } else if (strcasecmp(newEntry->lastName, y->lastName) < 0) {
        y->pLeft = newEntry;
    } else {
        y->pRight = newEntry;
    }
    newEntry->pLeft = NULL;
    newEntry->pRight = NULL;
    newEntry->red = true;
    pHead = fixContinuousRed(pHead, newEntry);
    return pHead;
}

entry *fixContinuousRed(entry *pHead, entry *z)
{
    entry *y = NULL;
    bool zParent_is_left_node;
    bool z_is_left_node;
    while (z->pParent->red) {
        zParent_is_left_node = (z->pParent == z->pParent->pParent->pLeft);
        y = zParent_is_left_node ? z->pParent->pParent->pRight : z->pParent->pParent->pLeft;
        if (y == NULL || !y->red) {
            z_is_left_node = (z == z->pParent->pLeft) ? true : false;
            if (zParent_is_left_node && !z_is_left_node) {
                z = z->pParent;
                pHead = leftRotate(pHead, z);
            } else if (!zParent_is_left_node && z_is_left_node) {
                z = z->pParent;
                pHead = rightRotate(pHead, z);
            }
            z->pParent->red = false;
            z->pParent->pParent->red = true;
            pHead = zParent_is_left_node ?
                    rightRotate(pHead, z->pParent->pParent) : leftRotate(pHead, z->pParent->pParent);
        } else {
            z->pParent->red = false;
            y->red = false;
            z->pParent->pParent->red = true;
            z = z->pParent->pParent;
        }
        if (z->pParent == NULL)
            break;
    }
    pHead->red = false;
    return pHead;
}

void freeNodepHead(entry *pHead)
{
    entry *e, *curr;
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

entry *imple_pHead(entry *pHead)
{
    pHead->pLeft = NULL;
    pHead->pRight = NULL;
    pHead->red = false;
    return pHead;
}

entry *pointer2pHead(entry *pHead, entry *e)
{
    return e;
}
