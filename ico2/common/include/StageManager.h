/*
 * ico2/common/include/StageManager.h
 *
 * The declarations of what StageManager.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef STAGEMANAGER_H
#define STAGEMANAGER_H

/* StageManager.c's `inline` functions, in the order of their definitions'
 * out-of-line copies at the end of the object (first-declaration order). */
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

#endif /* STAGEMANAGER_H */
