/*
 * ico2/script/include/st04c.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what st04c.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef ST04C_H
#define ST04C_H

extern void actSt04cDoorDownChk(volatile int a0);
extern void actSt04cDoorDownEffect(volatile int a0);
extern void actSt04cEneChk(volatile int a0);
extern void actSt04cIntroChk(volatile int a0);
extern void actSt04cIntroChkSub(volatile int a0);
extern void actSt04lDoorChk(volatile int a0);

#endif /* ST04C_H */
