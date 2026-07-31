#include "common.h"

/* lineManager 0x800 view (local) */
typedef struct { int f_0; int f_4; char _pad8[0x38]; int f_40; char _pad44[4]; int f_48; } LineGeo;

int Draw2DLine(void *a0) {
    int rv = 0;
    char *p = *(char **)((char *)a0 + 0x15C);
    char *q = *(char **)(p + 0x800);
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
    LineGeo *q = *(LineGeo **)((char *)p + 0x800);
    return q->f_4;
}

int Draw2DLineSeg_Loop(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    LineGeo *q = *(LineGeo **)((char *)p + 0x800);
    return q->f_0 == 0;
}

int Draw2DLineG(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    LineGeo *q = *(LineGeo **)((char *)p + 0x800);
    return q->f_48 == 2;
}

int _getLine(int a0)
{
    int new_var2;
    int v1 = *((int *)((*((int *)(a0 + 0x15C))) + 0x800));
    int new_var;
    int new_var3;
    int new_var4;
    new_var2 = v1 + 0x4;
    new_var3 = *((int *)new_var2);
    new_var4 = new_var3 == 1;
    if (new_var4) {
        new_var = *((int *)(v1 + 0x40));
        return new_var;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/src/lineManager", DrawLine);

INCLUDE_ASM("asm/nonmatchings/src/lineManager", DrawLineG);

INCLUDE_ASM("asm/nonmatchings/src/lineManager", func_001D3F78);

int func_001D40A0(char *a0)
{
    void *p = *(void **)(a0 + 0x15C);
    int *q = *(int **)((char *)p + 0x800);
    int r = 0;
    if (q[0] == 1 || *(int *)(a0 + 0x16C) == 0) {
        r = 1;
    }
    return r;
}

INCLUDE_ASM("asm/nonmatchings/src/lineManager", func_001D40D8);

INCLUDE_ASM("asm/nonmatchings/src/lineManager", func_001D4170);

INCLUDE_ASM("asm/nonmatchings/src/lineManager", func_001D4228);

