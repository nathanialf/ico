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

#include "typedef.h"

/* op.o's .sdata globals (MAIN.MAP) */
extern char *op2;
extern char *adpcm_conte01_sea;
extern int opTitleLogoMode;
extern char *titleAdpcm;
/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order op.c's inline tail has. */
void actOpDemo03(GObj *volatile a0);
inline void actSubMpegReturnPreload(GObj *volatile a0);
inline void actSt26aConte01_1_newgame(GObj *volatile a0);
inline void actOpDemo02Chk(GObj *volatile a0);
inline void actSt24aConte01_2_Jimaku(GObj *volatile a0);
void actOpDemo01_2Chk(GObj *volatile a0);
void actOpDemo03Chk(GObj *volatile a0);
void actSt13aConte01_3(GObj *volatile a0);
void actSt24aConte01_2(GObj *volatile a0);

#endif /* OP_H */
