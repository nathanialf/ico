/*
 * ico2/script/include/st04e.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what st04e.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef ST04E_H
#define ST04E_H

#include "typedef.h"

void actSt04eFuchi1Chk(GObj *volatile a0);
void actSt04eFuchi2Chk(GObj *volatile a0);
void actSt04eFuchi3Chk(GObj *volatile a0);
void actSt04eHint1Chk(GObj *volatile a0);
void actSt04eHint1WakeUpChk(GObj *volatile a0);
void actSt04eSeChk(GObj *volatile a0);
void actSt04eWaterFlagOn(GObj *volatile a0);
void actSt04eWaterMain(GObj *volatile a0);
void actSt04eWaterStop(GObj *volatile a0);
void actSt04eWaterStopSub(GObj *volatile a0);
void actSt04eWaterSwitch(GObj *volatile a0);

#endif /* ST04E_H */
