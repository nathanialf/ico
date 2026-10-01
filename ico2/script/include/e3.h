/*
 * ico2/script/include/e3.h
 *
 * The declarations of what e3.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef E3_H
#define E3_H

#include "typedef.h"

/* e3.o's .sdata globals */
extern char *e3capsule;
extern char *e3gate1st;
extern char *sekizo_e3;
extern int sekizo_e3_vol;
/* e3.c's `inline` functions, in the order of their definitions'
 * out-of-line copies at the end of the object (first-declaration order). */
inline void actE3CapsuleDemoEnd(GObj *volatile self);
inline void actE3DoorMain(GObj *volatile self);
inline void actE3DoorSwitch(GObj *volatile self);
inline void actE3DoorUp(GObj *volatile self);
inline void actE3St13cIntroChk(GObj *volatile self);
inline void actE3CageFallReadyChk(GObj *volatile self);
inline void actE3St01bEneChk(GObj *volatile self);
void actE3St09aGirlWay(GObj *volatile self);
inline void actE3St09aBrgMain(GObj *volatile self);
void actE3CageFallChk(GObj *volatile self);
void actE3CageFallDemo(GObj *volatile self);
void actE3CageFallEffect(GObj *volatile self);
void actE3CapsuleChk(GObj *volatile self);
void actE3CapsuleDemo(GObj *volatile self);
void actE3GateChk(GObj *volatile self);
void actE3GateDemo(GObj *volatile self);
void actE3GateJimaku(GObj *volatile self);
void actE3Inst1Chk(GObj *volatile self);
void actE3St09aSekizoChk(GObj *volatile self);
void actE3TitleChk(GObj *volatile self);
void actE3TitleFrameChk(GObj *volatile self);

#include "jimaku.h"

/* an effect argument: four floats, or the same 16 bytes as two doublewords */
typedef union EffectArg { /* field names derived */
    float f[4];

    struct {
        long long lo; /* 0x00 */
        long long hi; /* 0x08 */
    } d;
} EffectArg; /* derived name */

#endif /* E3_H */
