/*
 * ico2/script/include/st17a.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what st17a.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef ST17A_H
#define ST17A_H

#include "typedef.h"

/* st17a.o's .sdata globals (MAIN.MAP) */
extern char *cam;
void actLinkTestChk(GObj *volatile a0);
void actSt17aDoorDownChk(GObj *volatile a0);
void actSt17aDoorDownEffect(GObj *volatile a0);
void actSt17aDoorUpChk(GObj *volatile a0);
void actSt17aDoorUpEffect(GObj *volatile a0);
void actSt17aFallChk(GObj *volatile a0);
void actSt17aHasiChk(GObj *volatile a0);
void actSt17aHasiEffect(GObj *volatile a0);
void actSt17aHint1Chk(GObj *volatile a0);
void actSt17aIntroCancel(GObj *volatile a0);
void actSt17aIntroChk(GObj *volatile a0);

#endif /* ST17A_H */
