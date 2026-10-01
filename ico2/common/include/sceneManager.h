/*
 * ico2/common/include/sceneManager.h
 *
 * The declarations of what sceneManager.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <libvu0.h>

struct GObj;

/* the 0x40-byte layout record CSVSYSTEM_InitDObj starts a scene object from
   and CreateLayoutedGObj hands to the kind's constructor: position, rotation
   and scale as VU0 vectors, then the object word (the generator's word at
   0x30); 0x34..0x3F is the alignment tail, copied but never written.  With
   exactly these four members initSceneGObj's constructor fills a temporary
   without clearing it first, as the ROM does. */
typedef struct {         /* field names derived */
    sceVu0FVECTOR pos;   /* 0x00 */
    sceVu0FVECTOR rot;   /* 0x10 */
    sceVu0FVECTOR scale; /* 0x20 */
    int obj;             /* 0x30 */
} SObjSimpleSetting;     /* derived name */

/* sceneManager.c's .data global */
extern SObjSimpleSetting InitialSObjSimpleSetting;
/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order sceneManager.c's inline tail has. */
void ChangeStageStartInfo(int a0, int a1, int a2, int a3, int t0);
struct GObj *CreateLayoutedGObj(int id, int a1, int a2, int a3, void *lay, int a5, int a6, int a7);
void MoveNextStage_Set(float *a0, float *a1, int a2, int a3, int a4, int a5);
void test_nextstage_firstwalk_set(int unused, int a, int b, int c);
int GetStageStartInfo(struct GObj *a0, int a1, int a2, int *p, int *q, int *r);
void MoveNextStage_Clear(void);
void InitStageLight(int stage);
void initParentLink(int id);
void initSceneGObj(int stage, int id);
void InitSceneObjects(int stage);

/* enemy-model-grp: one enemy model group, 0x28 bytes. Reader:
 * ico2/common/src/sceneManager.c (EnemyMdlRec). Owner:
 * ico2/common/include/sceneManager.h. */
typedef struct {   /* field names derived */
    char name[32]; /* 0x00 */
    int first;     /* 0x20, the enemymodelTable range */
    int last;      /* 0x24 */
} EnemyMdlRec;     /* derived name */

extern const int
    enemymodelTable[]; /* enemy-model-tbl: the model ids enemymodelGroup ranges cover */
extern const EnemyMdlRec enemymodelGroup[];

#endif /* SCENEMANAGER_H */
