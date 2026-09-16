/*
 * ico2/script/include/st17a.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what st17a.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef ST17A_H
#define ST17A_H

void actLinkTestChk(volatile int a0);
void actSt17aDoorDownChk(volatile int a0);
void actSt17aDoorDownEffect(volatile int a0);
void actSt17aDoorUpChk(volatile int a0);
void actSt17aDoorUpEffect(volatile int a0);
void actSt17aFallChk(volatile int a0);
void actSt17aHasiChk(volatile int a0);
void actSt17aHasiEffect(volatile int a0);
void actSt17aHint1Chk(volatile int a0);
void actSt17aIntroCancel(volatile int a0);
void actSt17aIntroChk(volatile int a0);

#endif /* ST17A_H */
