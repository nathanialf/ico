/*
 * ico2/common/include/backStage.h
 *
 * The declarations of what backStage.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef BACKSTAGE_H
#define BACKSTAGE_H

/* backStage.c's `inline` functions, in the order of their definitions'
 * out-of-line copies at the end of the object (first-declaration order). */
void backStageProcessInit(void);
void backStageDebugTimeZero(void);
void backStageTsuresariReturn(void);
void backStageProcessInStage(float arg);
void backStageProcessOutStage(void);
void backStageProcessMain(void);
void routeSetPos(int gobj0, int gobj1, float *out, float ratio);
/* The enemy carrying the heroine off, which sceneManager sets when it takes her. */
extern int backStageGirlTargetEnemyGop;

/* the gamesys object-info record */
typedef struct GamesysObjInfo { /* field names derived */
    short flag;
    unsigned short no;
    unsigned short stage;
    short pad06;
    int time;
    int uniq;
    float pos[3];
    float pad1C;
    float rot[3];
    float pad2C;
    int work[4];
} GamesysObjInfo;

void backStageSave(void *a0);
void backStageLoad(void *a0);

#endif /* BACKSTAGE_H */
