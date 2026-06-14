#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04c", actSt04cEnd);

extern void actInitialize(int a0);
extern void _ACTWait(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void actSt04cDoorDownChk(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    stage_KillPlayBgAnimation(0x101, 0, 0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04c", actSt04lDoorChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04c", actSt04cSolarXL);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04c", actSt04lDoor);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04c", actSt04cIntro);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04c", actSt04cDoorDown);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04c", actSt04cEne);

typedef struct { long long q[8]; } Mtx64;
extern Mtx64 D_004CC120;
extern int D_00271C00[];
extern void func_00118A70(int *a0, int a1, void *a2);
extern void _SetCurrentMatrix(void *a0, int *a1);

void actSt04cEnemy1(void *a0) {
    int m[4];
    int i;
    func_00118A70(m, *(int *)((char *)*(void **)((char *)a0 + 0x15C) + 0xC), D_00271C00);
    m[1] = 0;
    _SetCurrentMatrix((char *)*(void **)((char *)a0 + 0x15C) + 0x510, m);
    for (i = 0; i < *(int *)((char *)*(void **)((char *)a0 + 0x15C) + 0x88); i++) {
        ((Mtx64 *)*(void **)((char *)*(void **)((char *)a0 + 0x15C) + 0x7CC))[i] = D_004CC120;
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04c", actSt04cEnemy2);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04c", actSt04cWaterXL);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04c", actSt04cDoorDownEvent);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04c", actSt04cDoorDownEffect);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04c", actSt04cEneChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04c", actSt04cIntroChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04c", actSt04lDoorEvent);

void func_00215CD0(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    stage_KillPlayBgAnimation(0xDC, 0, 0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04c", func_00215D10);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04c", func_00215D70);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04c", func_00215E30);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04c", func_00215EA8);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04c", func_00215F48);
