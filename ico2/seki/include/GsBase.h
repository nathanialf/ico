/*
 * ico2/seki/include/GsBase.h
 *
 * The declarations of what GsBase.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef GSBASE_H
#define GSBASE_H

/* GsBase.c's globals */
extern int currentFocusDistance;
extern int fbKeep;
extern int fbClear;
extern float center_X;
extern float center_Y;
extern int ScreenWidth;
extern int ScreenHeight;
extern int currentScreenWidth;
#ifdef VERSION_AUG6
extern int currentScreenHeight;
#else
#ifndef VERSION_NTSC
extern int currentScreenHeight;
extern int screenOffsetX;
extern int screenOffsetY;
#endif
extern int vsWidth;
extern int vsHeight;
#endif
/* GsBase.c's `inline` functions, in the order of their definitions'
 * out-of-line copies at the end of the object (first-declaration order). */
void gsb_SetBGColor(void *db, int r, int g, int b);
void gsb_GetBGColor(unsigned char *col);
#if !defined(VERSION_NTSC) && !defined(VERSION_AUG6)
void gsb_ResetFilmNoise(void);
#endif
void gsb_SetZoom(float target, float speed);
int gsb_SyncGSSystem(void);
int gsb_LoadStageSettings(void);
int gsb_SaveStageSettings(void);
void gsb_ClearFrameBuffer(void);
#if !defined(VERSION_NTSC) && !defined(VERSION_AUG6)
#if !defined(VERSION_JPN) && !defined(VERSION_KOR)
int gsb_ResetSnap(void);
int gsb_TakeSnap(void);
#endif
int lockOtherEditing(void);
int unlockOtherEditing(void);
#endif
int gsb_ClipBox(float *p);
void gsb_Init(void *db);
void gsb_InitGSSystem(void);
void gsb_MakeCommonMatrix(void);
void gsb_Reduction(void);
void gsb_ResetGSSystem(void);
#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
void gsb_SetVSMatrix(int w, int h, float d);
void gsb_UpdateGSSystem(void);
#else
void gsb_SetMotionBlur(void);
void gsb_SetVSMatrix(int w, int h, float d);
void gsb_UpdateGSSystem(int keep);
#endif
int gsb_StageSetting(void);

#endif /* GSBASE_H */
