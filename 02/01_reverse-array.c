#include <assert.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#define XOR 1

void reverse_array(size_t, uint32_t *);
uint8_t *s_var_from_stdin (uint8_t, size_t *, size_t *);
uint32_t *from_cmdline(int, char **, size_t *);
uint32_t *from_string(size_t, uint8_t *, size_t *);

int main(int argc, char **argv)
{
    uint8_t cmdline = 0;
    if (argc < 2) {
        printf("Please enter your numbers: ");
        size_t len = 0;
        size_t size = 0;
        uint32_t *input = v_var_from_stdin(1, &len, &size);
        if (input == NULL) {
            printf("PIC, OOM!\n");
            return 2;
        }
    } else {
        printf("Using arguments supplied.\n");
        cmdline = 1;
    }

    size_t count = 0;

    // PROCESS DATA HERE CORRECTLY
    if (cmdline) {
        uint32_t *data = from_cmdline(argc, **argv, &count);
    } else {
        uint32_t *data = from_string(len, *input, &count);
    }

    reverse_array(XOR, count, &data);

    return 0;
}

/*
 ** This function reverses inplace using either XOR or a temporary variable.
 ** (xor == 1 -> use xor, else use temporary)
 */
void reverse_array_xor(uint8_t xor, size_t len, uint32_t *array)
{
    if (xor) {
        for (size_t i = 0; i < (len >> 1); ++i) {
            *(array + i) ^= *(array + len - i - 1);
            *(array + len - i - 1) ^= *(array + i);
            *(array + i) ^= *(array + len - i - 1);
        }
    } else {
        for (size_t = 0; i < (len >> 1); ++i) {
            uint32_t temp = *(array + i);
            *(array + i) = *(array + len - i - 1);
            *(array + len - i - 1) = temp;
        }
    }
}
