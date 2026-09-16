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

extern void stage_ApplyData(int id, void *buf);
extern int stage_CheckAnimationFinish(int a0);
extern int stage_CheckAnimationFrame(int a0, int a1, int a2);
extern int stage_ContinueAnimation(int a0, int a1);
extern void stage_DispAnimation(void);
extern int stage_DispBgAnimation(void *p);
extern void stage_DispBgAnimationNoFinish(char **slot);
extern void stage_KillPlayBgAnimation(int **self);
extern void stage_KillPlayBgAnimationIfOverMaxCount(int a0, int a1);
extern int *stage_MakePlayBgAnimation(int key);
extern float stage_PlayBgAnimation(int key, float t, void *v, void *q);
extern float stage_PlayBgAnimationDissolve(int key, float t, float d, void *a, void *b);
extern void stage_SetAnimation(int a0, int a1, int a2);
extern void stage_SetFrameStep(int target, int val);
extern void stage_SetLoopFlag(int key, int a1);
extern void stage_SetParentOfGObj(int a0, void *a1);
extern void stage_SetParentOfGObjWithLocalRotationFlag(int a0, void *a1, int a2);
extern void stage_SetScale(int id, float s);

#endif /* STAGEANIMATION_H */
