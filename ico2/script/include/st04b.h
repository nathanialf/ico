/*
 * ico2/script/include/st04b.h
 *
 * The declarations of what st04b.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef ST04B_H
#define ST04B_H

#include "typedef.h"

/* st04b.o's .sdata globals */
extern char *sekizo4b;
extern int sekizo_4b;
extern unsigned char sekizo_4b_vol;
void actSt04bEne1Chk(GObj *volatile a0);
void actSt04bGirlWay(GObj *volatile a0);
void actSt04bSekizoChk(GObj *volatile a0);

#endif /* ST04B_H */
