/*
 * ico2/script/include/st05e.h
 *
 * The declarations of what st05e.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef ST05E_H
#define ST05E_H

#include "typedef.h"

/* st05e.o's .sdata globals */
extern char *solar;
void actSt05eSolarChk(GObj *volatile a0);
void actSt05eWaterFlagOn(GObj *volatile a0);
void actSt05eWaterMain(GObj *volatile a0);
void actSt05eWaterStop(GObj *volatile a0);
void actSt05eWaterSwitch(GObj *volatile a0);

#endif /* ST05E_H */
