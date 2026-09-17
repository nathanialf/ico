/*
 * ico2/sugipon/include/darkVolume.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what darkVolume.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef DARKVOLUME_H
#define DARKVOLUME_H

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order darkVolume.c's inline tail has. */
int InitDarkVolumeGeo(char *a0);
void DarkVolumeDL(void);
void ExecGameOverEffect(void);
void StartGameOverEffect(int a0, float t);
void StartQueenAttackEffect(int a0, float t);
void ResetGameOverEffect(void);

void DispGameOverEffect(void);
void GetGameOverEffectCenterPosition(int a0);
void InitGameOverEffect(void);
void SetupDarkVolume(void *a0, float a1, float a2);
void darkVolume(void *a0, float a1, float a2, float a3);
void sonic(void *pos, float t);

#endif /* DARKVOLUME_H */
