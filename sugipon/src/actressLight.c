#include "common.h"

extern void SetAP1DeadStatus(int a0, int a1);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/actressLight", SetActressLight);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/actressLight", func_001B7E50);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/actressLight", func_001B7ED8);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/actressLight", func_001B8090);

extern void *D_004BA2B8[];
extern void debug_assertMessage(void *a0);
void func_001B8408(void *a0) {
    void *p = *(void **)((char *)a0 + 0x164);
    debug_assertMessage(D_004BA2B8[*(int *)((char *)p + 0x30)]);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/actressLight", func_001B8428);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/actressLight", func_001B8470);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/actressLight", func_001B84F8);

void func_001B88B8(int a0) {
    SetAP1DeadStatus(a0, 5);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/actressLight", func_001B88C0);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/actressLight", func_001B8908);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/actressLight", func_001B8BD8);

int func_001B8D08(void *a0) {
    int *p = *(int **)((char *)a0 + 0x164);
    long long v = ((unsigned int *)p)[7];
    return ((int)v & 1) ^ 1;
}

void func_001B8D28(int **a0, int a1) {
    int *p = a0[0x59];
    p[0x22] = a1;
}

void func_001B8D38(int **a0, int a1) {
    int *p = a0[0x59];
    p[0x23] = a1;
}


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_004BA2B8;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_004BA2A0;  /* stride 0x4 */

/* end struct shapes */
