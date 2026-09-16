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

extern void actE3CageFallChk(volatile int a0);
extern void actE3CageFallDemo(volatile int a0);
extern void actE3CageFallEffect(volatile int a0);
extern void actE3CageFallReadyChk(volatile int a0);
extern void actE3CapsuleChk(volatile int a0);
extern void actE3CapsuleDemo(volatile int a0);
extern void actE3CapsuleDemoEnd(volatile int a0);
extern void actE3DoorMain(volatile int a0);
extern void actE3DoorSwitch(volatile int a0);
extern void actE3DoorUp(volatile int a0);
extern void actE3GateChk(volatile int a0);
extern void actE3GateDemo(volatile int a0);
extern void actE3GateJimaku(volatile int a0);
extern void actE3Inst1Chk(volatile int a0);
extern void actE3St01bEneChk(volatile int a0);
extern void actE3St09aBrgDown(volatile int a0);
extern void actE3St09aBrgMain(volatile int a0);
extern void actE3St09aBrgSwitch(volatile int a0);
extern void actE3St09aGirlWay(volatile int a0);
extern void actE3St09aSekizoChk(volatile int a0);
extern void actE3St13cIntroChk(volatile int a0);
extern void actE3TitleChk(volatile int a0);
extern void actE3TitleFrameChk(volatile int a0);

#endif /* E3_H */
