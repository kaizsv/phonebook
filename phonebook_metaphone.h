#define TRUE 1
#define FALSE 0

char VOWELS[] = "AEIOU";
char FRONTV[] = "EIY";   /* special cases for letters in FRONT of these */
char VARSON[] = "CSPTG"; /* variable sound--those modified by adding an "h" */
char DOUBLE[] = ".";     /* let these double letters through */

char excepPAIR[] = "AGKPW"; /* exceptions "ae-", "gn-", "kn-", "pn-", "wr-" */
char excepNEXT[] = "ENNNR";

void metaphone(char *lastName, char *metaph, int metalen)
{
    size_t string_length, last_char, metaph_length = 0;
    char next1char, next2char, next3char;
    char *chrptr, *chrptr1;
    int silent;
    if ((string_length = strlen(lastName)) == 0)
        return;

    // XXX : change to lower

    /* Drop the first letter if ae, gn, kn, pn, wr */
    if ((chrptr = strchr(excepPAIR, lastName[0])) != 0) {
        chrptr1 = excepNEXT + (chrptr - excepPAIR);
        if (chrptr1[0] == lastName[1]) {
            strcpy(lastName, &lastName[1]);
            string_length--;
        }
    }

    /* Change first character from X to S */
    if (lastName[0] == 'x')
        lastName[0] = 's';

    /* change wh- to w- */
    if (lastName[0] == 'w' && lastName[1] == 'h') {
        strcpy(&lastName[1], &lastName[2]);
        string_length--;
    }

    /* remove an 's' from the end of the string */
    if (lastName[string_length - 1] == 's')
        lastName[--string_length] = '\0';

    last_char = string_length - 1;

    for (int i = 0; ((i < string_length) && (metaph_length < metalen)); i++) {
        if (i == 0 && (strchr(VOWELS, lastName[i]) != 0)) {
            strncat(metaph, &lastName[i], 1);
            metaph_length++;
            continue;
        }

        next1char = i < last_char ? lastName[i+1] : ' ';
        next2char = i < (last_char-1) ? lastName[i+2] : ' ';

        silent = FALSE;

        switch (lastName[i]) {
            case 'b':
                if (!(i > 0 && i == last_char &&
                        lastName[last_char - 1] == 'm'))
                    strncat(metaph, "b", 1);
                else
                    silent = TRUE;
                break;
            case 'c':
                if (i > 1 && lastName[i-1] == 's' &&
                        strchr(FRONTV, next1char) != 0)
                    silent = TRUE;
                else if (i > 0 && next1char == 'i' && next2char == 'a')
                    strncat(metaph, "x", 1);
                else if (i == 0 && next1char == 'h' &&
                         strchr(VOWELS, next2char) == 0)
                    strncat(metaph, "x", 1);
                else if (strchr(FRONTV, next1char) != 0)
                    strncat(metaph, "s", 1);
                else if (i > 0 && lastName[i-1] == 'c')
                    strncat(metaph, "c", 1);
                else
                    strncat(metaph, "k", 1);
                break;
            case 'd':
                if (next1char == 'g' && strchr(FRONTV, next2char) != 0)
                    strncat(metaph, "j", 1);
                else
                    strncat(metaph, "t", 1);
                break;
            case 'g':
                next3char = i < (last_char-2) ? lastName[i+3] : ' ';
                if (next1char == 'h' && strchr(VOWELS, next2char) == 0)
                    silent = TRUE;
                else if (i == last_char - 3 && next1char == 'n' &&
                         next2char == 'e' && next3char == 'd')
                    silent = TRUE;
                else if (i == last_char - 1 && next1char == 'n')
                    silent = TRUE;
                else if (i > 0 && strchr(FRONTV, next1char) != 0) {
                    if (lastName[i-1] == 'd')
                        silent = TRUE;
                    if (!silent && lastName[i-1] != 'g')
                        strncat(metaph, "j", 1);
                }

                if (!silent)
                    strncat(metaph, "k", 1);
                break;
            case 'h':
                if (i == 0)
                    silent = FALSE;
                else if (strchr(VARSON, lastName[i-1]) != 0)
                    silent = TRUE;
                else if (strchr(VOWELS, lastName[i-1]) != 0 &&
                         strchr(VOWELS, next1char) == 0)
                    silent = TRUE;
                if (!silent)
                    strncat(metaph, "h", 1);
                break;
            case 'f':
            case 'j':
            case 'l':
            case 'm':
            case 'n':
            case 'r':
                strncat(metaph, &lastName[i], 1);
                break;
            case 'k':
                if (i > 0 && lastName[i-1] != 'c')
                    strncat(metaph, "k", 1);
                else
                    silent = TRUE;
                break;
            case 'p':
                if (next1char == 'h')
                    strncat(metaph, "f", 1);
                else
                    strncat(metaph, "p", 1);
                break;
            case 'q':
                strncat(metaph, "k", 1);
                break;
            case 's':
                if (i > 0 && next1char == 'i' &&
                        (next2char == 'o' || next2char == 'a'))
                    strncat(metaph, "x", 1);
                else if (next1char == 'h')
                    strncat(metaph, "x", 1);
                else
                    strncat(metaph, "s", 1);
                break;
            case 't':
                if (i > 0 && next1char == 'i' &&
                        (next2char == 'o' || next2char == 'a'))
                    strncat(metaph, "x", 1);
                else if (next1char == 'h' &&
                         (i > 0 || strchr(VOWELS, next2char) != 0))
                    strncat(metaph, "0", 1);
                else if (!(i < last_char - 2 &&
                           next1char == 'c' && next2char == 'h'))
                    strncat(metaph, "t", 1);
                else
                    silent = TRUE;
                break;
            case 'v':
                strncat(metaph, "f", 1);
                break;
            case 'w':
            case 'y':
                if (strchr(VOWELS,next1char) != 0)
                    strncat(metaph, "y", 1);
                else
                    silent = TRUE;
                break;
            case 'x':
                strncat(metaph, "ks", 2);
                break;
            case 'z':
                strncat(metaph, "s", 1);
                break;
        }
        if (!silent) {
            metaph_length++;
            if (lastName[i] == 'x')
                metaph_length++;
        }
    }
}
 