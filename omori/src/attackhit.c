#include "common.h"

/* attackhit 0x164 actor-state view (local) */
typedef struct { char _0[0x130]; int f_130; } AtkState;

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/attackhit", MakeAttackPack_Actor);

void AttackCheckSameGroup(int a0) {
    int buf[4];
    buf[0] = a0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/attackhit", AttackMail);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/attackhit", func_0017E160);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/attackhit", AttackCheckHit);

extern int D_0062A8E0;

void AttackGenerate(void) {
    D_0062A8E0 = 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/attackhit", EnemyAttackCenter);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/attackhit", BoyAttackCenter);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/attackhit", CommonAttackCenter);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/attackhit", AttackCenter);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/attackhit", AttackCenter_WithDir);

void func_0017F0D0(void) {
}

void func_0017F0D8(void) {
}

extern void EnemyAttackCenter(void *a0, void *a1, int a2);
extern void AttackCenter_WithDir(void *a0);

void func_0017F0E0(void *a0) {
    char buf[0x70];
    AtkState *p = *(AtkState **)((char *)a0 + 0x164);
    EnemyAttackCenter(buf, a0, p->f_130);
    AttackCenter_WithDir(buf);
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/attackhit", func_0017F110);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/attackhit", func_0017F2A0);

extern void *D_00286A94[];
extern void saveEditedData(void *a0);
void func_0017F450(void) {
    if (D_00286A94[0]) {
        saveEditedData(D_00286A94[0]);
    }
}

extern char D_00286A90[];
extern void func_0018F1A8(void);

void func_0017F470(void)
{
    char *new_var;
    char *p = D_00286A90;
    char *q;
    int i = 0x13;
    *((int *) (p + 0)) = 0;
    *((int *) (p + 0x4)) = 0;
    new_var = p;
    q = new_var + 0x23C;
    *((int *) (p + 0xC)) = 0;
    *((int *) (p + 0x10)) = 0;
    do {
        *((int *) q) = 0;
        i--;
        q -= 0x1C;
    } while (i >= 0);
    *((int *) (new_var + 0x8)) = 0;
    *((short *) (new_var + 0x24)) = (short) (-1);
    *((int *) (new_var + 0x14)) = 0;
    do { } while (0);
    *((short *) (new_var + 0x1C)) = 0;
    func_0018F1A8();
}

extern char D_00554728[];
extern void debug_assertMessage(char *a0);

typedef struct {
    int key;
    int f4;
    float f8, fC, f10;
    int f14, f18;
} AtkEnt;

typedef struct {
    char _0[0x28];
    AtkEnt arr[20];
} AtkCont;

void func_0017F4C8(AtkCont *a0, int a1, float b, float c, float d) {
    int i;
    for (i = 0; i < 20; i++) {
        if (a0->arr[i].key == a1) {
            AtkEnt *e = &a0->arr[i];
            e->f8 = b;
            e->fC = d;
            e->f10 = c;
            e->f4 = 0;
            return;
        }
    }
    debug_assertMessage(D_00554728);
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/attackhit", func_0017F518);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/attackhit", func_0017F670);
