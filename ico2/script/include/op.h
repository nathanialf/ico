/*
 * ico2/script/include/op.h
 *
 * The declarations of what op.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef OP_H
#define OP_H

#include "typedef.h"

/* op.o's .sdata globals */
extern char *op2;
extern char *adpcm_conte01_sea;
extern int opTitleLogoMode;
extern char *titleAdpcm;
/* op.c's `inline` functions, in the order of their definitions'
 * out-of-line copies at the end of the object (first-declaration order). */
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
