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

int GetTableArcCos(float x);
int GetTableArcSin(float x);
int GetTableArcTan2(float f12, float f13);
float GetTableCos(short a0);
float GetTableSin(short a0);
void InitTableSin(void);

#endif /* TABLESIN_H */
