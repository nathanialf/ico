/*
 * ico2/common/include/staffroll.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what staffroll.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef STAFFROLL_H
#define STAFFROLL_H

void staffRollStart(float t, int alpha);
/* MAIN.MAP globals of staffroll.o's .sdata */
extern int staffRollStartFlag;
extern float staffRollCenterOffsetX;
extern float staffRollCenterOffsetXDest;
extern int staffRollAlpha;
void staffRollMain(void);

/* the data-only member staffroll_dat: the roll's lines and their count */
extern char *staffRollNameData[];
extern int staffRollNameDataNum;

#endif /* STAFFROLL_H */
