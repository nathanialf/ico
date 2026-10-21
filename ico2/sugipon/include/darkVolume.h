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
int InitDarkVolumeGeo(struct GObj *self);
void DarkVolumeDL(void);
void ExecGameOverEffect(void);
void DispGameOverEffect(void);
void InitGameOverEffect(void);

#endif /* DARKVOLUME_H */
