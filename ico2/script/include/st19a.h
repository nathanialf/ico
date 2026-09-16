/*
 * ico2/script/include/st19a.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what st19a.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef ST19A_H
#define ST19A_H

extern void actSt19aChainDown(volatile int a0);
extern void actSt19aChainDownSub(volatile int a0);
extern void actSt19aChainMain(volatile int a0);
extern void actSt19aChainSwitch(volatile int a0);
extern void actSt19aHagurumaChk(volatile int a0);
extern void actSt19aOriMain(volatile int a0);
extern void actSt19aOriSwitch(volatile int a0);
extern void actSt19aOriUp(volatile int a0);
extern void actSt19aPipeChk(volatile int a0);

#endif /* ST19A_H */
