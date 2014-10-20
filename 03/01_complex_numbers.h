#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct imaginary_number_s {
    double real;
    double imaginary;
} cmp_num;

cmp_num *add(cmp_num *, cmp_num *);
cmp_num *subtract(cmp_num *, cmp_num *);
cmp_num *multiply(cmp_num *, cmp_num *);
cmp_num *divide(cmp_num *, cmp_num *);
void print_struct(cmp_num *, cmp_num *, cmp_num *, char);

cmp_num *add (cmp_num *a, cmp_num *b)
{
    cmp_num *result = malloc(sizeof(cmp_num));
    result->real = a->real + b->real;
    result->imaginary = a->imaginary + b->imaginary;
    return result;
}

cmp_num *subtract (cmp_num *a, cmp_num *b)
{
    cmp_num *b_neg = malloc(sizeof(cmp_num));
    cmp_num *result = malloc(sizeof(cmp_num));
    b_neg->real = -(b->real);
    b_neg->imaginary = -(b->imaginary);
    result = add(a, b_neg);
    free(b_neg);
    return result;
}

cmp_num *multiply (cmp_num *a, cmp_num *b)
{
    cmp_num *result = malloc(sizeof(cmp_num));
    result->real = (a->real * b->real - a->imaginary * b->imaginary);
    result->imaginary = (a->real * b->imaginary + a->imaginary * b->real);
    return result;
}

cmp_num *divide (cmp_num *a, cmp_num *b)
{
    cmp_num *result = malloc(sizeof(cmp_num));
    cmp_num *numerator = malloc(sizeof(cmp_num));
    cmp_num *denominator = malloc(sizeof(cmp_num));
    cmp_num *b_conj = malloc(sizeof(cmp_num));
    b_conj->real = b->real;
    b_conj->imaginary = -(b->imaginary);
    numerator = multiply(a, b_conj);
    denominator = multiply(b, b_conj);
    free(b_conj);
    result->real = numerator->real / denominator->real;
    result->imaginary = numerator->imaginary / denominator->real;
    free(numerator);
    free(denominator);
    return result;
}

void print_struct (cmp_num *a, cmp_num *b, cmp_num *res, char c)
{
    printf("(%f + %fi) %c (%f + %fi) = (%f + %fi)\n", a->real, a->imaginary, c, b->real, b->imaginary, res->real, res->imaginary);
}
