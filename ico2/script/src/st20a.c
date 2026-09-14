#include "common.h"

INCLUDE_ASM("asm/nonmatchings/ico2/script/src/st20a", actSt20aInit);
INCLUDE_ASM("asm/nonmatchings/ico2/script/src/st20a", actSt20aEnd);
INCLUDE_ASM("asm/nonmatchings/ico2/script/src/st20a", actSt20aBridgeDown);
INCLUDE_ASM("asm/nonmatchings/ico2/script/src/st20a", actSt20aGondolaDown);
INCLUDE_ASM("asm/nonmatchings/ico2/script/src/st20a", actSt20aGondolaUp);
INCLUDE_ASM("asm/nonmatchings/ico2/script/src/st20a", actSt20aFence);
INCLUDE_ASM("asm/nonmatchings/ico2/script/src/st20a", actSt20aFenceDownChk);
INCLUDE_ASM("asm/nonmatchings/ico2/script/src/st20a", actSt20aFenceUpChk);
INCLUDE_ASM("asm/nonmatchings/ico2/script/src/st20a", actSt20aFenceDownChk2);
INCLUDE_ASM("asm/nonmatchings/ico2/script/src/st20a", actSt20aFenceUpChk2);
INCLUDE_ASM("asm/nonmatchings/ico2/script/src/st20a", actSt20aBridge);
INCLUDE_ASM("asm/nonmatchings/ico2/script/src/st20a", actSt20aGondola);
INCLUDE_ASM("asm/nonmatchings/ico2/script/src/st20a", actSt20aExit);
INCLUDE_ASM("asm/nonmatchings/ico2/script/src/st20a", actSt20aElv);
INCLUDE_ASM("asm/nonmatchings/ico2/script/src/st20a", actSt20aEne);
INCLUDE_ASM("asm/nonmatchings/ico2/script/src/st20a", actSt20aEnemy1);
INCLUDE_ASM("asm/nonmatchings/ico2/script/src/st20a", actSt20aEnemy2);
INCLUDE_ASM("asm/nonmatchings/ico2/script/src/st20a", actSt20aEnemy3);
INCLUDE_ASM("asm/nonmatchings/ico2/script/src/st20a", actSt20aHint1);
INCLUDE_ASM("asm/nonmatchings/ico2/script/src/st20a", actSt20aGirlPos);
INCLUDE_ASM("asm/nonmatchings/ico2/script/src/st20a", actSt20aBridgeMain);
INCLUDE_ASM("asm/nonmatchings/ico2/script/src/st20a", actSt20aBridgeSwitch);
INCLUDE_ASM("asm/nonmatchings/ico2/script/src/st20a", actSt20aBridgeDownSub);
INCLUDE_ASM("asm/nonmatchings/ico2/script/src/st20a", actSt20aGondolaSwitch);
INCLUDE_ASM("asm/nonmatchings/ico2/script/src/st20a", actSt20aExitChk);
INCLUDE_ASM("asm/nonmatchings/ico2/script/src/st20a", actSt20aEneChk);
INCLUDE_ASM("asm/nonmatchings/ico2/script/src/st20a", actSt20aGirlPosChk);
INCLUDE_ASM("asm/nonmatchings/ico2/script/src/st20a", actSt20aHint1Chk);
/* This stub is not st20a.c's: it spans two functions of st22a.o -- the
   actSt22aLightningVolime loop at 0x00252418 (MAIN.MAP st22a.o base) and
   actSt22aIntro after it.  config/ico.pal.yaml starts ico2/script/src/st22a at
   0x252700, so the two names wait on that subsegment boundary moving to
   0x252418. */
INCLUDE_ASM("asm/nonmatchings/ico2/script/src/st20a", func_00252418);
