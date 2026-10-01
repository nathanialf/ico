/*
 * ico2/sugipon/include/darkVolume.h
 *
 * The declarations of what darkVolume.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef DARKVOLUME_H
#define DARKVOLUME_H

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order darkVolume.c's inline tail has. */
int InitDarkVolumeGeo(char *a0);
void DarkVolumeDL(void);
void ExecGameOverEffect(void);
void StartGameOverEffect(float *center, float speed);
void StartQueenAttackEffect(float *center, float speed);
void ResetGameOverEffect(void);
void DispGameOverEffect(void);
void GetGameOverEffectCenterPosition(float *pos);
void InitGameOverEffect(void);
void SetupDarkVolume(void *a0, float a1, float a2);
void darkVolume(void *a0, float a1, float a2, float a3);
void sonic(void *pos, float t);
void SetDarkVolumeEffect(float *pos, float size);

#endif /* DARKVOLUME_H */
