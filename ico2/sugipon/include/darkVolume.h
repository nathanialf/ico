/*
 * ico2/sugipon/include/darkVolume.h
 *
 * The declarations of what darkVolume.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef DARKVOLUME_H
#define DARKVOLUME_H

struct GObj;

int InitDarkVolumeGeo(struct GObj *self);
void DarkVolumeDL(void);
void ExecGameOverEffect(void);
void DispGameOverEffect(void);
void InitGameOverEffect(void);

#endif /* DARKVOLUME_H */
