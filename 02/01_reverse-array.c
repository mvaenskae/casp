#include <assert.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

void reverse_array(size_t, uint32_t *);
uint32_t *s_var_from_stdin (uint32_t, size_t *, size_t *);

int main(int argc, char **argv)
{
    uint8_t cmdline = 0;
    if (argc < 2) {
        printf("Please enter your numbers: ");
        size_t len = 0;
        size_t size = 0;
        uint32_t *input = v_var_from_stdin(1, &len, &size);
        if (input = NULL) {
            printf("PIC, OOM!\n");
            return 2;
        }
    } else {
        printf("Using arguments supplied.\n");
        cmdline = 1;
    }

    // PROCESS DATA HERE CORRECTLY
    if (cmdline) {

    } else {

    }

    reverse_array(len, &data);

    return 0;
}

/*
 ** This function reverses inplace using XOR operations.
 */
void reverse_array_xor(size_t len, uint32_t *array)
{
    for (size_t i = 0; i < (len)>>1; ++i)
    {
        *(array + i) ^= *(array + len - i - 1);
        *(array + len - i - 1) ^= *(array + i);
        *(array + i) ^= *(array + len - i - 1);
    }
}
