#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/stageSEProc", stageSEtaimatsu);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/stageSEProc", stageSE04eriver);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/stageSEProc", stageSE06ariver);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/stageSEProc", stageSE10lstrong2);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/stageSEProc", stageSE19ataki);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/stageSEProc", stageSE02astrong);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/stageSEProc", stageSE02ataki);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/stageSEProc", stageSE02atakib);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/stageSEProc", stageSE03tsuiro);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/stageSEProc", stageSE03tnotSuiro);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/stageSEProc", stageSE04agate);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/stageSEProc", stageSE04bstrong);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/stageSEProc", stageSE04ewind);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/stageSEProc", stageSE04eriverDown);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/stageSEProc", stageSE06astrong);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/stageSEProc", stageSE06abirdIn);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/stageSEProc", stageSE06abirdOut);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/stageSEProc", stageSE06ataimatsu);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/stageSEProc", stageSE08astrong);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/stageSEProc", stageSE08astrong2);

extern void actInitialize(int a0);
extern void _ACTWait(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void stageSE08anoise3(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    stage_KillPlayBgAnimation(0x82, 0, 0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/stageSEProc", stageSE08ataimatsu);
