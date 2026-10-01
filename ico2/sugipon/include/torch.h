/*
 * ico2/sugipon/include/torch.h
 *
 * The declarations of what torch.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef TORCH_H
#define TORCH_H

#include "sceneManager.h"

struct GObj;

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order torch.c's inline tail has. */
char *InitTorchGeo(struct GObj *a0, SObjSimpleSetting *a1);
void TorchDL(void);
int IsTorchLightOn(struct GObj *a0);
char *CheckTorchChainReaction(struct GObj *a0, float dist);
void SetTorchLife(struct GObj *a0, int a1, int a2);
void SetTorchChainReactionFlag(struct GObj *a0, int a1);
void UpdateRealTimeGeometryValue(struct GObj *a0);
void LightTorchOff(struct GObj *gobj);
void LightTorchOn(struct GObj *gobj);
void torchOffSE(struct GObj *a0);
void TorchGeo(struct GObj *gobj);

#endif /* TORCH_H */
