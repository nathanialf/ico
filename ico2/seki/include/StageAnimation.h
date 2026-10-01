/*
 * ico2/seki/include/StageAnimation.h
 *
 * The declarations of what StageAnimation.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef STAGEANIMATION_H
#define STAGEANIMATION_H

/* stage-anim: one stage animation, 0x5C bytes. Reader: ico2/seki/src/
 * StageAnimation.c (stage_ApplyData, the BGA set-up, (r - table) / 0x5C). */
typedef struct {          /* field names derived */
    char path[64];        /* 0x00, the .bga file, "NULL" for none */
    int objFirst;         /* 0x40, the objTableScene range */
    int objLast;          /* 0x44 */
    int group;            /* 0x48, copied into the BGA header's group */
    unsigned char cut;    /* 0x4C, copied into the BGA header's cut flag */
    char pad4D[3];
    int loop;   /* 0x50, the loop flag the animation calls take */
    void *data; /* 0x54, the loaded BGA data or the data pointer */
    int no;     /* 0x58, the row's own index, -1 for none */
} StageAnimDef; /* derived name */

/* stage-anim-model: one stage animation object, 8 bytes, the objTableScene
   range a stage animation's 0x40 and 0x44 words bound: the object kind and
   its argument. */
typedef struct { /* field names derived */
    int kind;    /* 0x00 */
    int aux;     /* 0x04 */
} StgObjDat; /* derived name */

extern const StgObjDat objTableScene[];
/* StageAnimation.c's `inline` functions, in the order of their definitions'
 * out-of-line copies at the end of the object (first-declaration order). */
int stage_CheckAnimationFinish(int a0);
int stage_CheckAnimationFrame(int a0, int a1, int a2);
void stage_SetLoopFlag(int key, int a1);
void stage_SetFrameStep(int target, int val);
void stage_SetParentOfGObj(int a0, void *a1);
void stage_SetParentOfGObjWithLocalRotationFlag(int a0, void *a1, int a2);
void stage_SetLocalizeGeometry(int key, float *pos, float *rot);
void stage_KillPlayBgAnimationIfOverMaxCount(int a0, int a1);
int stage_CheckAnimationFrameIn(int a0, int a1, int a2);
void stage_ApplyData(char *name, char *data);
int stage_ContinueAnimation(int a0, int a1);
void stage_DispAnimation(void);
int stage_DispBgAnimation(void *p);
int stage_DispBgAnimationNoFinish(char **slot);
void stage_KillPlayBgAnimation(int **self);
int *stage_MakePlayBgAnimation(int key);
float stage_PlayBgAnimation(int key, float t, void *v, void *q);
float stage_PlayBgAnimationDissolve(int key, void *a, void *b, float t, float d);
void stage_SetAnimation(int a0, int a1, int a2);
void stage_SetScale(int id, float s);
void stage_ResetAnimation(void);
void stage_CalcAnimationNoParent(void);
void stage_CalcAnimationParent(void);

#endif /* STAGEANIMATION_H */
