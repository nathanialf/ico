#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st07a", actSt07aInit);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st07a", actSt07aEnd);

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void actSt07aChanChk(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xDA) == 0) {
        stage_KillPlayBgAnimation(0x118, 0, 0);
    } else {
        stage_KillPlayBgAnimation(0x118, 0, -1);
    }
}

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void actSt07aChanEffect(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xDB) == 0) {
        stage_KillPlayBgAnimation(0x119, 0, 0);
    } else {
        stage_KillPlayBgAnimation(0x119, 0, -1);
    }
}

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void actSt07aTsuroChk(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xDC) == 0) {
        stage_KillPlayBgAnimation(0x11A, 0, 0);
    } else {
        stage_KillPlayBgAnimation(0x11A, 0, -1);
    }
}

extern void func_00178E08(int a0);
void actSt07aTsuroEffect(volatile int a0){ int x=a0; actInitialize(a0); _ACTWait(1);
if(func_00178DB0(0xE2)==0){ stage_KillPlayBgAnimation(0x11C,0,0); *(int*)(actSt25aQueenDeadChk(0x518) + 0x16C) = 0; *(int*)(actSt25aQueenDeadChk(0x519) + 0x16C) = 0; } else { stage_KillPlayBgAnimation(0x11C,0,-1); } }

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int actSt25aQueenDeadChk(int a0);
void actSt07aSekizoChk(volatile int a0){
 int x = a0;
 actInitialize(a0);
 _ACTWait(1);
 if(func_00178DB0(0xE3) == 0){
  stage_KillPlayBgAnimation(0x11D, 0, 0);
  *(int*)(actSt25aQueenDeadChk(0x5AD) + 0x16C) = 0;
  *(int*)(actSt25aQueenDeadChk(0x5AE) + 0x16C) = 0;
 } else {
  stage_KillPlayBgAnimation(0x11D, 0, -1);
 } }

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st07a", actSt07aEne);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st07a", actSt07aEneChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st07a", actSt07aChan);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st07a", actSt07aTsuro);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st07a", actSt07aIntro);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st07a", actSt07aSekizo);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st07a", actSt07aGene1);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st07a", actSt07aGene2);

void actSt07aGene3(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xF7)) {
        gflagInit(0x5AD);
    }
}

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void gflagInit(int a0);

void actSt07aEne2(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xF8)) {
        gflagInit(0x5AE);
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st07a", actSt07aGene2_1);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st07a", actSt07aGene2_2);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st07a", actSt07aGene2_3);

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern void BoxBarSoundOn(int a0, int a1);
extern int D_004CCDC0[];
extern void actSt06aSuimon(void);

typedef struct GObj {
    char pad[0xB4];
    int *unkB4;
} GObj;

void actSt07ChanEvent(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xFC) == 0) {
        stage_KillPlayBgAnimation(0x132, 0, 0);
        D_004CCDC0[1] = (int)actSt06aSuimon;
        gobj->unkB4 = D_004CCDC0;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0x132, 0, -1);
    }
}

