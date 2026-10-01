/*
 * ico2/script/include/st05e.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what st05e.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef ST05E_H
#define ST05E_H

#include "typedef.h"

/* st05e.o's .sdata globals (MAIN.MAP) */
extern char *solar;
void actSt05eSolarChk(GObj *volatile a0);
void actSt05eWaterFlagOn(GObj *volatile a0);
void actSt05eWaterMain(GObj *volatile a0);
void actSt05eWaterStop(GObj *volatile a0);
void actSt05eWaterStopSub(GObj *volatile a0);
void actSt05eWaterSwitch(GObj *volatile a0);

#endif /* ST05E_H */
