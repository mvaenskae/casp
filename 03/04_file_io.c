#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct state_population_pair_s {
    char* state;
    size_t population;
} stapo;

typedef struct state_population_list_s {
    size_t count;
    stapo *element;
} stapo_list;

int main(int argc, char **argv)
{
    // Init of needed variables
    FILE *fp = NULL;
    const char *origin = "\"25\"";
    size_t total = 0;
    stapo_list *list = malloc(sizeof(stapo_list));
    list->element = malloc(sizeof(stapo));
    list->count = 0; // For init purposes...

    // Try opening the file for reading
    fp = fopen("stateoutflow0708.txt", "r");
    if (fp == NULL) {
        fprintf(stderr, "Unable to open input\n");
        exit(-1);
    }

    const uint8_t state = 5;
    const uint8_t population = 8;

    // More fun trying to decipher when drunk!
    for(char c = EOF; (c = getc(fp)) != EOF; ) {
        if (c == '\n') {
            char *t = NULL;
            if (fgets(t, 5, fp) != NULL) {
                if (strcmp(t, origin)) {
                    uint8_t i = 0;
                    stapo *elem = malloc(sizeof(stapo));
                    (list->count)++;
                    list->element[list->count - 1] = *elem;
                    for (; (c = getc(fp)) != EOF && c != '\n' && c != EOF; ) {
                        if (c == '\t') {
                            ++i;
                        }
                        if (i == state) {
                            uint8_t len = 0;
                            /*
                             ** This is a lazy init, Do NOT blindly copy this.
                             ** You have been warned!
                             */
                            char *s = malloc(sizeof(char) * 25);
                            for(; (c = getc(fp)) != '\t'; ++len) {
                                s[len] = c;
                            }
                            ++len;
                            s[len] = '\0';
                            elem->state = malloc(sizeof(char) * len);
                            for(int k = 0; k < len; ++k) {
                                elem->state[i] = s[i];
                            }
                            free(s);
                            ++i;
                        }
                        if (i == population) {
                            uint8_t len = 0;
                            /*
                             ** This is also a lazy init! Do NOT blindly copy
                             ** this either! You have been warned, again!
                             */
                            char *s = malloc(sizeof(char) * 11);
                            uint64_t temp = 0;
                            for(; (c = getc(fp)) != '\n'; ++len) {
                                s[len] = c;
                            }
                            temp = strtoull(s, NULL, 0);
                            if (temp < SIZE_MAX) {
                                elem->population = (size_t) temp;
                            }
                        }
                    }
                }
            }
        }
    }
    fclose(fp);

    /* This print is not completely safe but works for the assignment
     ** If I wanted to get it really safe I would waste some hours on
     ** researching and toying around with strings.
     */
    printf("%20s %5c %9s\n%34c\n", "STATE", ' ', "TOTAL", '-');
    for(size_t i = 0; i < list->count; ++i) {
        printf("%20s %5c %9zd\n", (list->element[i]).state, ' ', (list->element[i]).population);
        total += (list->element[i]).population;
        // free elements
        free((list->element[i]).state);
        free(&(list->element[i]));
    }
    free(list->element);
    free(list);
    printf("%34c\n%20s %5c %9zd\n", '-', "TOTAL", ' ', total);

   return 0;
}
