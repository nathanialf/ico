/*
 * ico2/script/include/st05c.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what st05c.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef ST05C_H
#define ST05C_H

extern void actSt04rDoor2Chk(volatile int a0);
extern void actSt04rDoor2Sub(volatile int a0);
extern void actSt04rDoorChk(volatile int a0);
extern void actSt04rDoorSub(volatile int a0);
extern void actSt05cCrestHintChk(volatile int a0);
extern void actSt05cDoorDownChk(volatile int a0);
extern void actSt05cDoorDownEffect(volatile int a0);
extern void actSt05cEneChk(volatile int a0);

#endif /* ST05C_H */
