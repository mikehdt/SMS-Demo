// To test SDCC works (from their docs):
// $ sdcc --version :: check that SDCC is working
// $ sdcc -c test.c :: test compiler (should make an ASM file, amongst others)
// $ sdcc test.c :: test linker (should make an IHX file, amongst others)

#include <stdio.h>

int main()
{
    printf("Hello World !\n");
    return 0;
}
