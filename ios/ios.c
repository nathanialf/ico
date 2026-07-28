#include "common.h"


extern void iosMallocCheckLeak2();
int ios_init_plus(char *p)
{
    char *next;
    if (p == (char *)0) goto end;
    p -= 8;
    while (1) {
        next = *(char **)(p + 4);
        iosMallocCheckLeak2(p);
        p = next;
        if (p == (char *)0) break;
        p -= 8;
    }
end:
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/ios/ios", iosInitialize);

INCLUDE_ASM("asm/nonmatchings/ios/ios", iosSifAllocIopHeapDebug);

