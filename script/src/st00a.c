#include "common.h"

extern void actEndDemo10(void);
extern void actSt00aEnd(void);

void actSt00aInit(volatile int a0) {
    actCreateSubThread(actEndDemo10, 0x15);
    actCreateSubThread(actSt00aEnd, 0x15);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st00a", actSt00aEnd);

extern void func_00178DD8(int a0);
extern void actCreateSubThread(void *entry, int a1);
extern void actConte14_13(void);

void actSt00aEneChk(volatile int a0) {
    func_00178DD8(0x140);
    actCreateSubThread(actConte14_13, 0x15);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st00a", actSt00aStairChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st00a", actSt00aDoor2);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st00a", actSt00aDoor2UpChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st00a", actSt00aDoor2DownChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st00a", actSt00aDoor1);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st00a", actSt00aDoor1UpChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st00a", actSt00aDoor1DownChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st00a", actSt00aEne);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st00a", actSt00aEnemy1);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st00a", actSt00aEnemy2);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st00a", actSt00aStair);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st00a", actSt00aAtr2);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st00a", actSt00aAtr2Chk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st00a", actSt00aDoor2Event);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st00a", actSt00aDoor2UpEffect);

extern int D_00629DE8;
extern int func_00178DB0(int a0);
extern void func_00178DD8(int a0);

void actSt00aDoor2DownEffect(void) {
    if (D_00629DE8 == 0) return;
    if (func_00178DB0(0x27) != 0) return;
    func_00178DD8(0x165);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st00a", actSt00aDoor1Event);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st00a", actSt00aDoor1UpEffect);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st00a", actSt00aDoor1DownEffect);


/* recovered struct shapes */
typedef struct {
    unsigned int       f_1C;  /* 0x1C */
    unsigned int       f_20;  /* 0x20 */
} S_0055A2D8;  /* stride 0x28 */

/* end struct shapes */
