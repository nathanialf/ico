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
void OverrideBrainStatusByGObj(Brain *b, int gobj, float levelCap, float rate, float capStep);
void brainAddLevelGirl(float lv);
int brainCheckView(Brain *b, BrainTarget *t);
void brainClsTargetLevel(Brain *b);
void brainInit(void);
void brainInitGirlSet(void *girl, int cur);
void brainLockGirl(void);
void brainSetLevelGop(int gobj, int lookOnly, int alwaysSeen, float lv);
void brainSetSpMode(void);
void brainStatusDefaultSet(Brain *b, int gobj, int idx);
void brainSubLevelGop(int gobj, float lv);
void brainUnlockGirl(void);

#endif /* BRAIN_H */
