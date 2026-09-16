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

extern int IsTorchLightOn(char *a0);
extern void LightTorchOff(char *gobj);
extern void LightTorchOn(char *gobj);
extern void SetTorchChainReactionFlag(char *a0, int a1);

#endif /* TORCH_H */
