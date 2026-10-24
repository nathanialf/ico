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

struct TorchGeoWork;

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order torch.c's inline tail has. */
struct TorchGeoWork *InitTorchGeo(struct GObj *self, SObjSimpleSetting *lay);
void TorchDL(void);
int IsTorchLightOn(struct GObj *torch);
struct GObj *CheckTorchChainReaction(struct GObj *self, float dist);
struct GObj *CheckTorchChainReactionReverse(struct GObj *self, float dist);

#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
void SetTorchLife(struct GObj *torch, int life);
#else
void SetTorchLife(struct GObj *torch, int life, int fadeTime);
#endif

void SetTorchChainReactionFlag(struct GObj *torch, int flag);
void UpdateRealTimeGeometryValue(struct GObj *self);
void LightTorchOff(struct GObj *gobj);
void LightTorchOn(struct GObj *gobj);
void torchOffSE(struct GObj *torch);
void TorchGeo(struct GObj *gobj);

#endif /* TORCH_H */
