/*
 * ico2/sugipon/include/tableSin.h
 *
 * The declarations of what tableSin.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef TABLESIN_H
#define TABLESIN_H

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order tableSin.c's inline tail has. */
float GetTableSin(short a0);
float GetTableCos(short a0);
void InitTableSin(void);
short GetTableArcSin(float x);
short GetTableArcCos(float x);
short GetTableArcTan2(float f12, float f13);

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order tableSin.c's inline tail has. */

#endif /* TABLESIN_H */
