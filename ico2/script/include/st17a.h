/*
 * ico2/script/include/st17a.h
 *
 * The declarations of what st17a.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef ST17A_H
#define ST17A_H

#include "typedef.h"

/* st17a.o's .sdata globals */
extern char *cam;
void actLinkTestChk(GObj *volatile a0);
void actSt17aDoorDownChk(GObj *volatile a0);
void actSt17aDoorDownEffect(GObj *volatile a0);
void actSt17aDoorUpChk(GObj *volatile a0);
void actSt17aDoorUpEffect(GObj *volatile a0);
void actSt17aHasiChk(GObj *volatile a0);
void actSt17aHasiEffect(GObj *volatile a0);
void actSt17aIntroChk(GObj *volatile a0);

#endif /* ST17A_H */
