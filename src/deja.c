#include "common.h"

/* PAL listing rows: every instruction of actDeja is attributed to
 * script/src/deja.c lines 170-189 -- no inlined helper bodies.
 *
 * actDejaChk is this TU's own first function (the PAL listing names it
 * actDejaChk, deja.c:196); actDeja installs it as the actor's next mail
 * handler.  D_004F7988 is the 2-entry mail table that lives in the shared
 * src/cod .data carve, so it stays extern here. */
extern void _ACTWait(int a0);
extern int gflagChk(int a0);
extern void lt_switch_layout(int a0);
extern void scpFadeOut(float a0, int a1, int a2, int a3);
extern void stage_SetAnimation(int a0, int a1, int a2);
extern void actDejaChk(int a0);
extern int D_0063AA08;
typedef struct ActMail {
    int mail;                   /* 0x00 */
    void (*func)(int);          /* 0x04 */
    int unk08;                  /* 0x08 */
    int unk0C;                  /* 0x0C */
} ActMail;
typedef struct Act {
    char unk00[0xD4];           /* 0x00 */
    ActMail *mail;              /* 0xD4 */
} Act;
extern ActMail D_004F7988[];
extern Act *actInitialize(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern void scpSleepEnemyAll(void);
/* prototypes: their order is the inline tail's emission order */
void actDeja(volatile int a0);
void actEnemySleep(volatile int a0);
inline void actEnemySleep(volatile int a0) {
    while (1) {
        scpSleepEnemyAll();
        _ACTWait(1);
    }
}
inline void actDeja(volatile int a0) {
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(6) == 0) {
        lt_switch_layout(0x37);
        D_0063AA08 = 1;
        scpFadeOut(255.0f, 0, 0, 0);
        stage_SetAnimation(0x48, 0, 0);
        D_004F7988[0].func = actDejaChk;
        self->mail = D_004F7988;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}
INCLUDE_ASM("asm/nonmatchings/src/deja", actDejaChk);
INCLUDE_ASM("asm/nonmatchings/src/deja", actDejaDemo);
INCLUDE_ASM("asm/nonmatchings/src/deja", actDejaAfter);
INCLUDE_ASM("asm/nonmatchings/src/deja", actDejaAfterChk);
