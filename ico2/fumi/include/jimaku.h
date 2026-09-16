/*
 * ico2/fumi/include/jimaku.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what jimaku.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef JIMAKU_H
#define JIMAKU_H

extern void jimakuBegin(int a0);
extern void jimakuEnd(void);
extern void jimakuJump(int a0);
extern void jimakuUndisp(void);

#endif /* JIMAKU_H */
