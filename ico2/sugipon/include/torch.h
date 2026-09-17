/*
 * ico2/sugipon/include/torch.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what torch.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef TORCH_H
#define TORCH_H

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order torch.c's inline tail has. */
char *InitTorchGeo(char *a0, char *a1);
void TorchDL(void);
int IsTorchLightOn(char *a0);
char *CheckTorchChainReaction(char *a0, float dist);
void SetTorchLife(char *a0, int a1, int a2);
void SetTorchChainReactionFlag(char *a0, int a1);
void UpdateRealTimeGeometryValue(char *a0);

void LightTorchOff(char *gobj);
void LightTorchOn(char *gobj);

#endif /* TORCH_H */
