/*
 * ico2/seki/include/Shadow.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what Shadow.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef SHADOW_H
#define SHADOW_H

#include "typedef.h"

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order Shadow.c's inline tail has. */
void shadow_KillShadow(int val);
void shadow_DispCancel(int a0, int a1);
void shadow_SetLength(Sub15C *a0, float f);
void shadow_Init(void);
void shadow_Render(Sub15C *o);
void shadow_RenderVolume(Sub15C *o);
void shadow_RenderVolumeMulti(Sub15C *o, int idx);
void shadow_Reset(void);
void shadow_Draw(void);
int shadow_Tool(void);

#endif /* SHADOW_H */
