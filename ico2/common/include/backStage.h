/*
 * ico2/common/include/backStage.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what backStage.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef BACKSTAGE_H
#define BACKSTAGE_H

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order backStage.c's inline tail has. */
void backStageProcessInit(void);
void backStageDebugTimeZero(void);
void backStageTsuresariReturn(void);

void backStageProcessInStage(float arg);
void backStageProcessOutStage(void);
void routeSetPos(int gobj0, int gobj1, float *out, float ratio);

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: one record for 3 TUs that carried 2 divergent local copies; this body is the one the ROM's bytes accept in the most of them. */
typedef struct {
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

#endif /* BACKSTAGE_H */
