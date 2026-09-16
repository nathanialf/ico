/*
 * ico2/seki/include/GsBase.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what GsBase.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef GSBASE_H
#define GSBASE_H

extern void appendLogFile(void);
extern void gsb_ClearFrameBuffer(void);
extern int gsb_ClipBox(void *pk);
extern void gsb_Init();
extern void gsb_InitGSSystem(void);
extern void gsb_MakeCommonMatrix(void);
extern void gsb_PostEffect(void);
extern void gsb_Reduction(void);
extern void gsb_ResetGSSystem(void);
extern void gsb_SetBGColor(void *a0, int r, int g, int b);
extern void gsb_SetMotionBlur(void);
extern void gsb_SetVSMatrix(int a0, int a1, float f);
extern void gsb_SetZoom(float a, float b);
extern int gsb_SyncGSSystem(void);
extern void gsb_UpdateGSSystem(int a0);
extern void updateOtherEditingLockFlag(void);

#endif /* GSBASE_H */
