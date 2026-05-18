#include "matching.h"
#include "regpin.h"

extern void func_001E3FC8(int *self);

void func_001CE6F0(int *self)
{
    register int *alias REG("$5");
    alias = self;
    MATERIALIZE(alias);
    *(int volatile *)((char *)*(int * volatile *)((char *)alias + 0x15C) + 0x2B0) = 0;
    *(int volatile *)((char *)*(int * volatile *)((char *)alias + 0x15C) + 0x310) = 0;
    *(int volatile *)((char *)*(int * volatile *)((char *)alias + 0x15C) + 0x3B8) = 0;
    *(int volatile *)((char *)*(int * volatile *)((char *)alias + 0x15C) + 0x3BC) = 0;
    func_001E3FC8(self);
}
