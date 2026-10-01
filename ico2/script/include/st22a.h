/*
 * ico2/script/include/st22a.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what st22a.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef ST22A_H
#define ST22A_H

#include "typedef.h"

/* st22a.o's .sdata globals (MAIN.MAP) */
extern int lightning;
void actSt22aIntroSub(GObj *volatile a0);

#endif /* ST22A_H */
