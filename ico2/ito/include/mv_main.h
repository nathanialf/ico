/*
 * ico2/ito/include/mv_main.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what mv_main.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef MV_MAIN_H
#define MV_MAIN_H

extern int initAll(int a0, int a1, int a2, int a3, int p4, int p5, int p6, int p7);
extern void switchThread(void);

#endif /* MV_MAIN_H */
