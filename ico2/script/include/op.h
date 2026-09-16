/*
 * ico2/script/include/op.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what op.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef OP_H
#define OP_H

void actOpDemo01_2Chk(volatile int a0);
void actOpDemo03Chk(volatile int a0);
void actSt13aConte01_3(volatile int a0);
void actSt24aConte01_2(volatile int a0);

#endif /* OP_H */
