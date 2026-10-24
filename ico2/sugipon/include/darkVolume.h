/*
 * ico2/sugipon/include/darkVolume.h
 *
 * The declarations of what darkVolume.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef DARKVOLUME_H
#define DARKVOLUME_H

struct GObj;

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order darkVolume.c's inline tail has. */
#ifndef VERSION_NTSC
int InitDarkVolumeGeo(struct GObj *self);
#endif

void DarkVolumeDL(void);
void ExecGameOverEffect(void);

#ifdef VERSION_JUN26
void DispGameOverEffect(void);
void InitGameOverEffect(void);
#else
void StartGameOverEffect(float *center, float speed);
void StartQueenAttackEffect(float *center, float speed);
void ResetGameOverEffect(void);
void DispGameOverEffect(void);
void GetGameOverEffectCenterPosition(float *pos);
void InitGameOverEffect(void);

#if !defined(VERSION_NTSC) && !defined(VERSION_AUG6)
void SetupDarkVolume(void *pos, float radius, float edge);
#endif

void SetDarkVolumeEffect(float *pos, float size);
#endif

#endif /* DARKVOLUME_H */
