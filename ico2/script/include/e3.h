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

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order e3.c's inline tail has. */
void actE3CapsuleDemoEnd(volatile int a0);
void actE3DoorMain(volatile int a0);
void actE3DoorSwitch(volatile int a0);
void actE3DoorUp(volatile int a0);
void actE3St13cIntroChk(volatile int a0);
void actE3CageFallReadyChk(volatile int a0);
void actE3St01bEneChk(volatile int a0);
void actE3St09aGirlWay(volatile int a0);
void actE3St09aBrgMain(volatile int a0);
void actE3St09aBrgSwitch(volatile int a0);

void actE3CageFallChk(volatile int a0);
void actE3CageFallDemo(volatile int a0);
void actE3CageFallEffect(volatile int a0);
void actE3CapsuleChk(volatile int a0);
void actE3CapsuleDemo(volatile int a0);
void actE3GateChk(volatile int a0);
void actE3GateDemo(volatile int a0);
void actE3GateJimaku(volatile int a0);
void actE3Inst1Chk(volatile int a0);
void actE3St09aBrgDown(volatile int a0);
void actE3St09aSekizoChk(volatile int a0);
void actE3TitleChk(volatile int a0);
void actE3TitleFrameChk(volatile int a0);

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: one record, previously repeated character for character in 7 TUs. */
typedef struct JimakuSub {
    char unk00[0x2C]; /* 0x0C */
    int unk2C;        /* 0x38 */
    int n;            /* 0x3C */
    int unk34;        /* 0x40 */
    int unk38;        /* 0x44 */
    void *unk3C;      /* 0x48 */
    void *unk40;      /* 0x4C */
} JimakuSub;

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: one record, previously repeated character for character in 7 TUs. */
typedef struct JimakuArg {
    int cmd;       /* 0x00 */
    int unk04;     /* 0x04 */
    int done;      /* 0x08 */
    JimakuSub sub; /* 0x0C */
} JimakuArg;

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: one record for 3 TUs that carried 2 divergent local copies; this body is the one the ROM's bytes accept in the most of them. */
typedef union EffectArg {
    float f[4];

    struct {
        long long lo; /* 0x00 */
        long long hi; /* 0x08 */
    } d;
} EffectArg;

#endif /* E3_H */
