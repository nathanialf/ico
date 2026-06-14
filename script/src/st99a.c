#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st99a", actExplode);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st99a", actSplash1);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st99a", actSplash2);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st99a", actWave);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st99a", actSpider);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st99a", actDevilLightning);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st99a", actQueenLightning);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st99a", actSt27aWave);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st99a", actExplodeChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st99a", actSplash1Chk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st99a", actSplash2Chk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st99a", actWaveChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st99a", actWave1);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st99a", actSt27aWaveChk);

extern int func_00178DB0(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern void AddWayPointTop(int a0, int a1);

void actSt27aWave1(void) {
    if (func_00178DB0(0x11F) == 0) {
        stage_KillPlayBgAnimation(0x7F, 0, 0);
        AddWayPointTop(4, 0);
    } else {
        stage_KillPlayBgAnimation(0x7F, 0, -1);
        AddWayPointTop(4, 1);
    }
}

extern int D_00629DE8;
extern int func_00178DB0(int a0);
extern void func_00178DD8(int a0);

void actSpiderChk(void) {
    if (D_00629DE8) {
        if (func_00178DB0(0x11F)) {
            if (!func_00178DB0(0x122)) {
                func_00178DD8(0x165);
            }
        }
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st99a", func_002343C0);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st99a", func_002344C0);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st99a", func_00234640);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st99a", func_002347A8);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st99a", func_002348D8);
