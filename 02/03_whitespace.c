#include <assert.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct string_with_length{
    uint8_t *str;
    size_t len;
} strlen;

uint8_t *s_var_from_stdin (uint8_t, size_t *, size_t *);
uint8_t get_and_create_word (strlen *, int, uint8_t *);
void print_strlen (strlen *);


int main (int argc, char **argv)
{
    uint8_t failure = 0;
    size_t len = 0;
    size_t size = 0;

    printf("Please enter your string of characters (Enter/EOF to confirm: ");
    uint8_t *input = s_var_from_stdin(1, &len, &size);
    if (input == NULL) {
        printf("PIC, OOM!\n");
        return 2;
    }
    strlen *res = malloc(sizeof(strlen));
    assert(res != NULL);
    
    failure = get_and_create_word(res, len, input);
    free(input);
    
    if (failure) {
        printf("Oops, something broke during string creation. Halting execution and cleaning up...\n");
        free(res);
        return 1;
    } else {
        print_strlen(res);
        return 0;
    }
}

/*
 ** Function which reads from stdin and tries to intelligently realloc enough
 ** memory to store the input without blowing up on memory and too many
 ** unneccessary realloc operations.
 ** Returns a NUL-terminated char array on success, on failure NULL.
 */
uint8_t *s_var_from_stdin (uint8_t cleanup, size_t *len, size_t *size)
{
    const double FACTOR = 1.5;
    uint8_t *tmp = NULL;
    uint8_t *ret = NULL;
    size_t i = 0;
    size_t c = EOF;
    size_t sz = 127;

    ret = malloc(sizeof(uint8_t) * sz);
    if (ret == NULL) {
        goto fail;
    }

    for (i = 0, sz = 127; (c = getchar()) != '\n' && c != EOF; ++i) {
        if (i == sz - 1) {
            size_t sz_old = sz;
            sz = (size_t) (sz * FACTOR);
            assert(sz > sz_old);

            tmp = realloc(ret, sz);
            if (tmp == NULL) {
                free(ret);
                goto fail;
            }
            ret = tmp;
        }
        *(ret + i) = (uint8_t) c;
    }
    *(ret + i) = '\0';

    if (cleanup) {
        tmp = realloc(ret, (i+1) * sizeof(uint8_t));
        if (tmp == NULL) {
            goto fail;
        }
        ret = tmp;
        sz = i + i;
    }

    if (len) {
        *len = i;
    }
    if (size) {
        *size = sz;
    }

    return ret;

fail:
    if (len) {
        *len = 0;
    }
    if (size) {
        *size = 0;
    }
    return NULL;
}

/*
 ** Function which takes an input a string and its length and finds the first
 ** substring from index to to n, where at the n-th position a whitespace is
 ** encountered.
 ** Return 0 if all went well, else return 1.
 */
uint8_t get_and_create_word (strlen *res, int len, uint8_t *str)
{
    // get the length of the substring in question by simple iteration
    for ((*res).len = 0; (*res).len < len; ++((*res).len)) {
        if (*(str + (*res).len) == ' ' || *(str + (*res).len) == '\0') {
            break;
        }
    }

    // increment by one to have space for '\0'
    (*res).str = malloc(sizeof(uint8_t) * ((*res).len + 1));
    if ((*res).str == NULL) {
       return 1;
    } 

    // copy again the string to the malloced memory segment
    for (size_t i = 0; i < (*res).len; ++i) {
        *((*res).str + i) = *(str + i);
    }
    *((*res).str + (*res).len) = '\0';

    return 0;
}

/*
 ** Function which prints the struct string_with_length.
 */
void print_strlen (strlen *res)
{
    printf("String length: %" PRIu64"\nString content: ", (*res).len);
    for (size_t i = 0; i < (*res).len; ++i)
    {
        putchar(*((*res).str + i));
    }
    putchar(0x0A);
}
