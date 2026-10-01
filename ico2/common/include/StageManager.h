/*
 * ico2/common/include/StageManager.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what StageManager.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef STAGEMANAGER_H
#define STAGEMANAGER_H

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order StageManager.c's inline tail has. */
void stgmgrNextStagePreLoadForceStageSet(int val);
void stgmgrNextStagePreLoadDistBoyMode(void);
void stgmgrNextStagePreLoadForceNoCancel(int val);
void CheckPoint(void);
void stgmgrForceSwitch(int stage);
void stgmgrForceSwitchWithFade(int stage, float fadeIn, float fadeOut);

void stgmgrForceSwitchWithFadeColor(int stage, float fadeIn, float fadeOut, unsigned char r,
                                    unsigned char g, unsigned char b);

/* The stage thread's entry point, the fifth thread main.c's idle creates. */
void StageManager(void);

/* The preload buffer cdvd.c's stream reads the next stage's file through. */
extern char stagePreLoadBuff[];

/* The movie switches main.c's loop reads and the stage thread sets: the movie
   playing, its decoder started, the stage it returns to, its first colour,
   resources being freed, and the stage thread's wakeup request. */
extern int mpegPlay;
extern int mpegInitDone;
extern int mpegPlayReturnStage;
extern unsigned int mpegPlayInitColor;
extern int stageManagerFreeResourceFlag;
extern int stgMgrWakeupRequest;

/* The next stage's preload, cdvd.c's stream reads it back. */
extern int stagePreLoadStageNo;
extern int stagePreLoadReadOffset;
extern int stagePreLoad2ndReadOffset;
extern int stagePreLoadLsn;
extern int stagePreLoadSectorCnt;

/* The fade-in speed main.c hands the switch after a movie, and the number of
   exits stgmgrNextStagePreLoadEntry collected. */
extern float mpegPlayFadeInSpeed;
extern int stageExitDataCnt;

struct CdvdBgReq;
int stgmgrNextStagePreLoad(struct CdvdBgReq *bg);

#endif /* STAGEMANAGER_H */
