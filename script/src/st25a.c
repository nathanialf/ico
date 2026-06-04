#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st25a", actSt25aQueenAppear);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st25a", actSt25aQueenAppearChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st25a", actConte11);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st25a", actSt25aQueenTalkChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st25a", actConte12);

void actConte12Jimaku(void *a0) {
    int *p = *(int **)((char *)a0 + 0x164);
    *(int *)((char *)p + 0x33C) = 0;
    *(int *)((char *)p + 0x100) = 0;
    *(int *)((char *)p + 0x104) = 0;
    *(int *)((char *)p + 0x108) = 0;
    *(int *)((char *)p + 0x32C) = 0x7F;
    *(int *)((char *)p + 0x328) = 0x7F;
}

extern int isysGObjAddHead(void);

int actSt25aQueenDeadChk(void) {
    return isysGObjAddHead();
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st25a", actConte13Jimaku);

extern int ExecMotionOrient(void *a0, int a1, void *a2);

void BoySekikaTexScroll(void *a0, int a1) {
    char *p = *(char **)((char *)a0 + 0x164);
    *(int *)(p + 0x110) = ExecMotionOrient(a0, a1, p + 0x610);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st25a", actSt25aGenerator);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st25a", actSt25aQueenBefore);

extern int D_0062C030;

void actSt25aQueenTalk(void) {
    D_0062C030 = 0;
}

extern int actItouQueenAttack(int a0, int a1, int a2, int a3, int a4, int a5);
int actSt25aQueenDead(int a0, int a1, int a2) {
    return actItouQueenAttack(a0, a1, a2, 0, 0, 0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st25a", actItouQueenAttack);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st25a", actSwordEff);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st25a", actSwordEffXL);

extern float D_0062BA7C;
extern int D_0062BA80, D_0062BA78;
extern unsigned char D_0062BA88, D_0062BA89, D_0062BA8A;

void actSt25aQueenBeforeChk(float a0, int a1, int a2, int a3) {
    D_0062BA78 = 1;
    D_0062BA7C = a0;
    D_0062BA80 = 1;
    D_0062BA88 = a1;
    D_0062BA89 = a2;
    D_0062BA8A = a3;
}

extern int D_0062BA78;
extern float D_0062BA7C;
extern int D_0062BA80;

void actConte11Jimaku(float a0) {
    D_0062BA78 = 1;
    D_0062BA7C = -a0;
    D_0062BA80 = 0;
}

extern int D_0062BA78;
int actSt25aQueenDeadEvent(void) {
    int g = D_0062BA78;
    if (g == 0) {
        goto ret0;
    }
    if (g != 3) {
        goto ret1;
    }
ret0:
    return 0;
ret1:
    return 1;
}

extern int *D_00629DE4;
extern int checkHit(int a0);

int actItouQueenAttackChk(void) {
    int *p = (int *)D_00629DE4[0x59];
    int v = p[0x4C];
    if (v == 0) {
        return 0;
    }
    return checkHit(v);
}

extern int func_001BDF80(void);

int func_0017BCC0(void) {
    return func_001BDF80();
}

extern int ACTGameCollisionOn(void);

int func_0017BCE0(void) {
    return ACTGameCollisionOn() != 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st25a", func_0017BD00);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st25a", func_0017BD40);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st25a", func_0017BE60);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st25a", func_0017BF18);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st25a", func_0017BF50);
