/*
 * ico2/sugipon/include/tableSin.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what tableSin.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef TABLESIN_H
#define TABLESIN_H

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order tableSin.c's inline tail has. */
float GetTableSin(short a0);
float GetTableCos(short a0);
void InitTableSin(void);
int GetTableArcSin(float x);
int GetTableArcCos(float x);
short GetTableArcTan2(float f12, float f13);

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order tableSin.c's inline tail has. */

#endif /* TABLESIN_H */
