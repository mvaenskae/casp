#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct complex_number_s {
    double real;
    double complex;
} cmp_num;

cmp_num *add (cmp_num a, cmp_num b)
{
    cmp_num *result = malloc(sizeof(cmp_num));
    result->real = a.real + b.real;
    result->complex = a.complex + b.complex;
    return result;
}

cmp_num *subtract (cmp_num a, cmp_num b)
{
    b.real = -b.real;
    b.complex = -b.complex;
    return add(a, b);
}

cmp_num *multiply (cmp_num a, cmp_num b)
{
    cmp_num *result = malloc(sizeof(cmp_num));
    result->real = (a.real * b.real - a.complex * b.complex);
    result->complex = (a.real * b.complex + a.complex * b.real);
    return result;
}

cmp_num *divide (cmp_num a, cmp_num b)
{
    cmp_num *result = malloc(sizeof(cmp_num));
    cmp_num *numerator = malloc(sizeof(cmp_num));
    cmp_num *denominator = malloc(sizeof(cmp_num));
    cmp_num *b_conj = malloc(sizeof(cmp_num));
    b_conj->real = b.real;
    b_conj->complex = -b.complex;
    numerator = multiply(a, *b_conj);
    denominator = multiply(b, *b_conj);
    result->real = numerator->real / denominator->real;
    result->complex = numerator->complex / denominator->real;
    free(numerator);
    free(denominator);
    return result;
}

void print_struct (cmp_num *a, cmp_num *b, cmp_num *res, char c)
{
    printf("(%f + %fi) %c (%f + %fi) = (%f + %fi)\n", a->real, a->complex, c, b->real, b->complex, res->real, res->complex);
}
