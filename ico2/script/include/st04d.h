/*
 * ico2/script/include/st04d.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what st04d.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef ST04D_H
#define ST04D_H

void actSt04dDoor1DownChk(volatile int a0);
void actSt04dDoor1UpChk(volatile int a0);
void actSt04dDoor2DownChk(volatile int a0);
void actSt04dDoor2UpChk(volatile int a0);

#endif /* ST04D_H */
