/*
 * ico2/common/include/staffroll.h
 *
 * The declarations of what staffroll.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef STAFFROLL_H
#define STAFFROLL_H

void staffRollStart(float t, int alpha);
/* staffroll.o's .sdata globals */
extern int staffRollStartFlag;
extern float staffRollCenterOffsetX;
extern float staffRollCenterOffsetXDest;
extern int staffRollAlpha;
void staffRollMain(void);

/* the data-only member staffroll_dat: the roll's lines and their count */
extern char *staffRollNameData[];
extern int staffRollNameDataNum;

#endif /* STAFFROLL_H */
