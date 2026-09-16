/*
 * ico2/script/include/st99a.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what st99a.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef ST99A_H
#define ST99A_H

void actExplodeChk(volatile int a0);
void actSpiderChk(volatile int a0);
void actSplash1Chk(volatile int a0);
void actSplash2Chk(volatile int a0);
void actSt17aTestChk(volatile int a0);
void actSt27aWave1(volatile int a0);
void actSt27aWaveChk(volatile int a0);
void actWave1(volatile int a0);
void actWaveChk(volatile int a0);

#endif /* ST99A_H */
