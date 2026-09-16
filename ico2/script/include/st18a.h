/*
 * ico2/script/include/st18a.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what st18a.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef ST18A_H
#define ST18A_H

void actSt18aDoorChk(volatile int a0);
void actSt18aDoorChkSub(volatile int a0);
void actSt18aDoorDownChk(volatile int a0);
void actSt18aEne2Chk(volatile int a0);
void actSt18aEneChk(volatile int a0);
void actSt18aIntroChk(volatile int a0);
void actSt18aSwitchLChk(volatile int a0);
void actSt18aSwitchLUpChk(volatile int a0);
void actSt18aSwitchRChk(volatile int a0);
void actSt18aSwitchRUpChk(volatile int a0);

#endif /* ST18A_H */
