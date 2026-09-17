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

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order StageAnimation.c's inline tail has. */
int stage_CheckAnimationFinish(int a0);
int stage_CheckAnimationFrame(int a0, int a1, int a2);
void stage_SetLoopFlag(int key, int a1);
void stage_SetFrameStep(int target, int val);
void stage_SetParentOfGObj(int a0, void *a1);
void stage_SetParentOfGObjWithLocalRotationFlag(int a0, void *a1, int a2);
void stage_SetLocalizeGeometry(int key, int arg1, int arg2);
void stage_KillPlayBgAnimationIfOverMaxCount(int a0, int a1);
int stage_CheckAnimationFrameIn(int a0, int a1, int a2);

void stage_ApplyData(char *name, char *data);
int stage_ContinueAnimation(int a0, int a1);
void stage_DispAnimation(void);
int stage_DispBgAnimation(void *p);
void stage_DispBgAnimationNoFinish(char **slot);
void stage_KillPlayBgAnimation(int **self);
int *stage_MakePlayBgAnimation(int key);
float stage_PlayBgAnimation(int key, float t, void *v, void *q);
float stage_PlayBgAnimationDissolve(int key, float t, float d, void *a, void *b);
void stage_SetAnimation(int a0, int a1, int a2);
void stage_SetScale(int id, float s);

#endif /* STAGEANIMATION_H */
