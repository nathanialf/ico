#include "common.h"

int Draw2DLine(void *a0) {
    int rv = 0;
    char *p = *(char **)((char *)a0 + 0x15C);
    char *q = *(char **)(p + 0x7F0);
    if (*(int *)((char *)a0 + 0x16C) == 0) {
        goto end;
    }
    if (*(long long *)(q + 8) != 0) {
        goto end;
    }
    rv = *(int *)(q + 0x48) < 2;
end:
    return rv;
}

int Draw2DLineSeg_Start(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    int *q = *(int **)((char *)p + 0x7F0);
    return q[1];
}

int Draw2DLineSeg_Loop(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    int *q = *(int **)((char *)p + 0x7F0);
    return q[0] == 0;
}

int Draw2DLineG(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    int *q = *(int **)((char *)p + 0x7F0);
    return q[0x12] == 2;
}

int _getLine(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    int *q = *(int **)((char *)p + 0x7F0);
    int t = q[1] ^ 1;
    if (t) goto zero;
    return q[0x10];
zero:
    return 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/lineManager", DrawLine);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/lineManager", DrawLineG);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/lineManager", func_001D1310);

int func_001D1438(char *self) {
    char *a = *(char **)(self + 0x15C);
    int *b = *(int **)(a + 0x7F0);
    int ret = 0;
    if (*b != 1) {
        if (*(int *)(self + 0x16C) != 0) {
            goto end;
        }
    }
    ret = 1;
end:
    return ret;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/lineManager", func_001D1470);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/lineManager", func_001D1508);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/lineManager", func_001D15C0);
