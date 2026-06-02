#include "matching.h"

extern char D_007097F0[];
extern void func_001E80D8(int);

void func_001E8A60(void)
{
    char *p = D_007097F0;
    char *end = p + 0xC00;
    do {
        if (*(int *)p != 0) {
            func_001E80D8(*(int *)(p + 0x14));
        }
        p += 0x18;
    } while ((int)p < (int)end);
}
