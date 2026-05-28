#include "matching.h"
#include "regpin.h"

extern int *D_00631AE4;
extern unsigned short D_00565060[];

int func_0014A560(void)
{
    int *player = D_00631AE4;
    int state;
    int *sub;
    char *entry;
    register int rv REG("$2");
    if (player == 0) {
        goto ret0;
    }
    state = *(int *)(*(char **)((char *)player + 0x164) + 0x30);
    if (state == 0x4B) {
        goto have_sub;
    }
    if (state != 0x55) {
        rv = 0;
        goto end;
    }
have_sub:
    sub = *(int **)((char *)player + 0x15C);
    entry = (char *)D_00565060 + *(int *)((char *)sub + 0x4A0) * 0x190;
    rv = 1;
    if (*(int *)(entry + 0x15C) == 1) {
        goto end;
    }
ret0:
    rv = 0;
end:
    return rv;
}
