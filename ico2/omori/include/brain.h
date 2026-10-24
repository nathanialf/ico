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

#ifdef VERSION_JUN26
void brainAddLevelGirl(float lv);
void brainAddLevelGop(GObj *gobj, float lv);
#else
void OverrideBrainStatusByGObj(Brain *b, GObj *gobj, float levelCap, float rate, float capStep);
void brainAddLevelGirl(float lv);

#if !defined(VERSION_NTSC) && !defined(VERSION_AUG6)
void brainAddLevelGirlDetail(int flag, float lv);
#endif

void brainAddLevelGop(GObj *gobj, float lv);
int brainCheckView(Brain *b, BrainTarget *t);
#endif

void brainClsTargetLevel(Brain *b);
float brainGetLevel(Brain *b, BrainTarget *t);
void brainGetTarget(Brain *b);
int brainDecTargetTimer(GObj *gobj);
void brainInit(void);
void brainInitGirlSet(GObj *girl, GObj *cur);
void brainLevelProcess(Brain *b);
void brainLockGirl(void);
void brainSetLevelGop(GObj *gobj, float lv, int lookOnly, int alwaysSeen);
void brainSetSpMode(void);
void brainStatusDefaultSet(Brain *b, GObj *gobj, int idx);

#if defined(VERSION_NTSC) || defined(VERSION_JUN26)
BrainTarget *brainStatusSet(Brain *b, GObj *gobj, float levelCap, float capStep, float rate);
#endif

void brainSubLevelGop(GObj *gobj, float lv);
void brainUnlockGirl(void);

#endif /* BRAIN_H */
