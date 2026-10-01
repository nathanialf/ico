/*
 * ico2/script/include/st13a.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what st13a.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef ST13A_H
#define ST13A_H

/* st13a.o's .sdata globals (MAIN.MAP) */
extern int st13a_up;
extern int st13a_down;
extern int sekizo13a;
extern unsigned int st13a_yure;
extern unsigned char st13a_yure_vol;
extern int sekizo_13a;
extern unsigned char sekizo_13a_vol;

void actSt13aChainNG(volatile int a0);
void actSt13aChainOK(volatile int a0);
void actSt13aCheckChk(volatile int a0);
void actSt13aElevMain(volatile int a0);
void actSt13aElevSwitch(volatile int a0);
void actSt13aElevUp(volatile int a0);
void actSt13aSekizoChk(volatile int a0);

#endif /* ST13A_H */
