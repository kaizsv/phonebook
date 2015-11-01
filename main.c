#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <ctype.h>

#include IMPL

#define DICT_FILE "./dictionary/words.txt"

static double diff_in_msecond(struct timespec t1, struct timespec t2)
{
    struct timespec diff;
    if (t2.tv_nsec-t1.tv_nsec < 0) {
        diff.tv_sec  = t2.tv_sec - t1.tv_sec - 1;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec + 1000000000;
    } else {
        diff.tv_sec  = t2.tv_sec - t1.tv_sec;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec;
    }
    return (diff.tv_sec + diff.tv_nsec / 1000000.0);
}

int main(int argc, char *argv[])
{
    FILE *fp;
    int i = 0;
    char line[MAX_LAST_NAME_SIZE];
    char input[MAX_LAST_NAME_SIZE] = "zyxel";
    struct timespec start, end;
    double cpu_time1, cpu_time2;

    /* check file opening */
    fp = fopen(DICT_FILE, "r");
    if (fp == NULL) {
        printf("cannot open the file\n");
        return -1;
    }

    /* build the entry */
    entry *pHead, *e;
    entry **ht = NULL;
    pHead = (entry *) malloc(sizeof(entry));
    printf("size of entry : %lu bytes\n", sizeof(entry));
    e = pHead;
    e->pNext = NULL;
    ht = imple_hash_table(ht);

#if defined(__GNUC__)
    __builtin___clear_cache((char *) pHead, (char *) pHead + sizeof(entry));
#endif
    clock_gettime(CLOCK_REALTIME, &start);
    while (fgets(line, sizeof(line), fp)) {
        while (line[i] != '\0')
            i++;
        line[i - 1] = '\0';
        i = 0;
        e = append(line, e, ht);
    }
    clock_gettime(CLOCK_REALTIME, &end);
    cpu_time1 = diff_in_msecond(start, end);

    /* close file as soon as possible */
    fclose(fp);

    /* the givn last name to find */
    printf("last name search: ");
    scanf("%s", input);
    while (input[i] != '\0') {
        if (isalpha(input[i])) {
            if (isupper(input[i]))
                input[i] = tolower(input[i]);
        } else {
            printf("\nerr: alphabetic only.");
            return -1;
        }
        i++;
    }

    e = pHead;

    /*assert(findName(input, e, ht) &&
           "Did you implement findName() in " IMPL "?");
    assert(0 == strcmp(findName(input, e, ht)->lastName, input));*/

    clock_gettime(CLOCK_REALTIME, &start);
    if (findName(input, e, ht) == NULL) {
        printf("err: string not found.\n");
        clock_gettime(CLOCK_REALTIME, &end);
        return -1;
    }

#if defined(__GNUC__)
    __builtin___clear_cache((char *) pHead, (char *) pHead + sizeof(entry));
#endif

    /* compute the execution time */
    clock_gettime(CLOCK_REALTIME, &start);
    findName(input, e, ht);
    clock_gettime(CLOCK_REALTIME, &end);
    cpu_time2 = diff_in_msecond(start, end);

    printf("last name found!!\n");
    printf("execution time of append() : %lf msec\n", cpu_time1);
    printf("execution time of findName() : %lf msec\n", cpu_time2);
    display_hash_imformation(ht);

    /* release all allocated entries */
    freeNode(pHead, ht);

    return 0;
}
