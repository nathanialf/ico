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

void appendLogFile(void);
void gsb_ClearFrameBuffer(void);
int gsb_ClipBox(void *pk);
void gsb_Init();
void gsb_InitGSSystem(void);
void gsb_MakeCommonMatrix(void);
void gsb_PostEffect(void);
void gsb_Reduction(void);
void gsb_ResetGSSystem(void);
void gsb_SetBGColor(void *a0, int r, int g, int b);
void gsb_SetMotionBlur(void);
void gsb_SetVSMatrix(int a0, int a1, float f);
void gsb_SetZoom(float a, float b);
int gsb_SyncGSSystem(void);
void gsb_UpdateGSSystem(int a0);
void updateOtherEditingLockFlag(void);

#endif /* GSBASE_H */
