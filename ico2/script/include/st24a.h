/*
 * ico2/script/include/st24a.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what st24a.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef ST24A_H
#define ST24A_H

extern void actSt24aDemoCamChk(volatile int a0);
extern void actSt24aSwordChk(volatile int self);
extern void actSt24aSwordSub(volatile int a0);

#endif /* ST24A_H */
