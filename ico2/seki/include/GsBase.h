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
extern int currentScreenHeight;
extern int screenOffsetX;
extern int screenOffsetY;
extern int vsWidth;
extern int vsHeight;
void appendLogFile(void);
void gsb_ClearFrameBuffer(void);
int gsb_ClipBox(void *pk);
void gsb_Init();
void gsb_InitGSSystem(void);
void gsb_MakeCommonMatrix(void);
int gsb_PostEffect(void);
void gsb_Reduction(void);
void gsb_ResetGSSystem(void);
void gsb_SetBGColor(void *a0, int r, int g, int b);
void gsb_SetMotionBlur(void);
void gsb_SetVSMatrix(int a0, int a1, float f);
void gsb_SetZoom(float a, float b);
int gsb_SyncGSSystem(void);
void gsb_UpdateGSSystem(int a0);
void updateOtherEditingLockFlag(void);
void gsb_KeepFrameBuffer(void);
void gsb_fade(void);
void gsb_scissorOnDemo(void);
void gsb_antiAlias(void);
void gsb_SetVSMatrixSub(float *a, float *b, float *c, float *d, float *vs);

#endif /* GSBASE_H */
