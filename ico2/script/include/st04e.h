/*
 * ico2/script/include/st04e.h
 *
 * The declarations of what st04e.c defines, for the files that use
 * them.  The file name is derived.
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
