#include "matching.h"
#include "regpin.h"

typedef struct { long long ll; } __attribute__((packed)) Pack8;

void func_00190408(char *dst, int *self)
{
    int *q = (int *)self[0x57];
    char *p = (char *)q[0x200];
    register long long ll REG("$2");
    register int last;
    ll = ((Pack8 *)(p + 0xA4))->ll;
    last = *(int *)(p + 0xAC);
    ((Pack8 *)dst)->ll = ll;
    *(int *)(dst + 8) = last;
    NOP();
}
