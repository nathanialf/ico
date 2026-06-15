#include "common.h"

/* lineManager 0x7F0 view (local) */
typedef struct { int f_0; int f_4; char _pad8[0x38]; int f_40; char _pad44[4]; int f_48; } LineGeo;

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
    LineGeo *q = *(LineGeo **)((char *)p + 0x7F0);
    return q->f_4;
}

int Draw2DLineSeg_Loop(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    LineGeo *q = *(LineGeo **)((char *)p + 0x7F0);
    return q->f_0 == 0;
}

int Draw2DLineG(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    LineGeo *q = *(LineGeo **)((char *)p + 0x7F0);
    return q->f_48 == 2;
}

int _getLine(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    LineGeo *q = *(LineGeo **)((char *)p + 0x7F0);
    int t = q->f_4 ^ 1;
    if (t) goto zero;
    return q->f_40;
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

extern void gif_SpriteOrg(int a0, long long a1);
extern int D_0062B704;

void func_001D15C0(int *a0, int *a1, int *a2, int a3) {
    gif_SpriteOrg(0, D_0062B704);
    gif_SpriteOrg(1, a2[0] | ((long long)a2[1] << 8) | ((long long)a2[2] << 16) | ((long long)a2[3] << 24));
    if (a3 == 0) {
        gif_SpriteOrg(5, a0[0] | ((long long)a0[1] << 16) | ((long long)a0[2] << 32));
        gif_SpriteOrg(5, a1[0] | ((long long)a1[1] << 16) | ((long long)a1[2] << 32));
    } else {
        gif_SpriteOrg(5, a0[0] | ((long long)a0[1] << 16) | ((long long)a3 << 32));
        gif_SpriteOrg(5, a1[0] | ((long long)a1[1] << 16) | ((long long)a3 << 32));
    }
}
