#include "matching.h"
#include "regpin.h"

struct E36 { char pad[0xC]; int field; char pad2[0x14]; };
extern struct E36 D_006124F8[];

float func_001F42E8(char *a0)
{
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x800);
    int idx = *(int *)p;
    register float v REG("$f0");
    v = (float)D_006124F8[idx].field;
    __asm__ __volatile__("" : "+f"(v));
    NOP();
    return v;
}
