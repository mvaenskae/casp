#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include "01_complex_numbers.h"

int main(int argc, char **argv)
{
    cmp_num a = {5.5, 1.25};
    cmp_num b = {2.75, 3.25};
    cmp_num *ad = add(a, b);
    cmp_num *sub = subtract(a, b);
    cmp_num *mult = multiply(a, b);
    cmp_num *div = divide(a, b);
    print_struct(a, b, *ad, '+');
    free(ad);
    print_struct(a, b, *sub, '-');
    free(sub);
    print_struct(a, b, *mult, '*');
    free(mult);
    print_struct(a, b, *div, '/');
    free(div);
    return 0;
}
