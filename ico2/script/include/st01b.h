/*
 * ico2/script/include/st01b.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what st01b.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef ST01B_H
#define ST01B_H

void actSt01bEneChk(volatile int a0);
void actSt01bFloorChk(volatile int a0);
void actSt01bFloorChkSub(volatile int a0);
void actSt01bWayOffChk(volatile int a0);
void actSt01bWayOnChk(volatile int a0);

#endif /* ST01B_H */
