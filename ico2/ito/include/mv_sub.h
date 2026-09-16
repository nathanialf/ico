/*
 * ico2/ito/include/mv_sub.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what mv_sub.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef MV_SUB_H
#define MV_SUB_H

void ErrMessage(int a0);
int copy2area(char *a0, int a1, char *a2, int a3, char *a4, int a5, char *a6, int a7);

#endif /* MV_SUB_H */
