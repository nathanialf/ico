/*
 * ico2/seki/include/StageAnimation.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what StageAnimation.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef STAGEANIMATION_H
#define STAGEANIMATION_H

void stage_ApplyData(int id, void *buf);
int stage_CheckAnimationFinish(int a0);
int stage_CheckAnimationFrame(int a0, int a1, int a2);
int stage_ContinueAnimation(int a0, int a1);
void stage_DispAnimation(void);
int stage_DispBgAnimation(void *p);
void stage_DispBgAnimationNoFinish(char **slot);
void stage_KillPlayBgAnimation(int **self);
void stage_KillPlayBgAnimationIfOverMaxCount(int a0, int a1);
int *stage_MakePlayBgAnimation(int key);
float stage_PlayBgAnimation(int key, float t, void *v, void *q);
float stage_PlayBgAnimationDissolve(int key, float t, float d, void *a, void *b);
void stage_SetAnimation(int a0, int a1, int a2);
void stage_SetFrameStep(int target, int val);
void stage_SetLoopFlag(int key, int a1);
void stage_SetParentOfGObj(int a0, void *a1);
void stage_SetParentOfGObjWithLocalRotationFlag(int a0, void *a1, int a2);
void stage_SetScale(int id, float s);

#endif /* STAGEANIMATION_H */
