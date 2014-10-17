#include <assert.h>
#include <stdio.h>

void increment(int i);
void mult(int i);

int main(int argc, char **argv)
{
    void (*foo)(int) = NULL;
    int i = 20;

    foo = &increment;
    assert(*foo != NULL);
    (*foo)(i);
    
    foo = &mult;
    assert(foo != NULL);
    (*foo)(i);
    
    return 0;
}

void increment(int i)
{
    int ii = ++i;
    printf("increment: %d + 1 = %d\n", i, ii);
}

void mult(int i)
{
    int ii = i << 1;
    printf("mult: %d * 2 = %d\n", i, ii);
}
