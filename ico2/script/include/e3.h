/*
 * ico2/script/include/e3.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what e3.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef E3_H
#define E3_H

#include "typedef.h"

/* e3.o's .sdata globals (MAIN.MAP) */
extern char *e3capsule;
extern char *e3gate1st;
extern char *sekizo_e3;
extern int sekizo_e3_vol;
/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order e3.c's inline tail has. */
void actE3CapsuleDemoEnd(GObj *volatile a0);
void actE3DoorMain(GObj *volatile a0);
void actE3DoorSwitch(GObj *volatile a0);
void actE3DoorUp(GObj *volatile a0);
void actE3St13cIntroChk(GObj *volatile a0);
void actE3CageFallReadyChk(GObj *volatile a0);
void actE3St01bEneChk(GObj *volatile a0);
void actE3St09aGirlWay(GObj *volatile a0);
void actE3St09aBrgMain(GObj *volatile a0);
void actE3St09aBrgSwitch(GObj *volatile a0);
void actE3CageFallChk(GObj *volatile a0);
void actE3CageFallDemo(GObj *volatile a0);
void actE3CageFallEffect(GObj *volatile a0);
void actE3CapsuleChk(GObj *volatile a0);
void actE3CapsuleDemo(GObj *volatile a0);
void actE3GateChk(GObj *volatile a0);
void actE3GateDemo(GObj *volatile a0);
void actE3GateJimaku(GObj *volatile a0);
void actE3Inst1Chk(GObj *volatile a0);
void actE3St09aBrgDown(GObj *volatile a0);
void actE3St09aSekizoChk(GObj *volatile a0);
void actE3TitleChk(GObj *volatile a0);
void actE3TitleFrameChk(GObj *volatile a0);

#include "jimaku.h"

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: one record for 3 TUs that carried 2 divergent local copies; this body is the one the ROM's bytes accept in the most of them. */
typedef union EffectArg {
    float f[4];

    struct {
        long long lo; /* 0x00 */
        long long hi; /* 0x08 */
    } d;
} EffectArg;

#endif /* E3_H */
