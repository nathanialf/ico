/*
 * ico2/omori/include/brain.h
 *
 * The declarations of what brain.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef BRAIN_H
#define BRAIN_H

#include "typedef.h"

/* the girl's brain record */
extern Brain brainGirl;
void OverrideBrainStatusByGObj(Brain *b, int gobj, float f8, float f10, float fC);
void brainAddLevelGirl(float lv);
int brainCheckView(int *a0, int *a1);
void brainClsTargetLevel(Brain *b);
void brainInit(void);
void brainInitGirlSet(void *a0, int a1);
void brainLockGirl(void);
void brainSetLevelGop(int gobj, int a1, int a2, float lv);
void brainSetSpMode(void);
void brainStatusDefaultSet(Brain *b, int gobj, int idx);
void brainSubLevelGop(int gobj, float lv);
void brainUnlockGirl(void);

#endif /* BRAIN_H */
