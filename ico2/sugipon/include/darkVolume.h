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

extern void DispGameOverEffect(void);
extern void GetGameOverEffectCenterPosition(int a0);
extern void InitGameOverEffect(void);
extern void SetupDarkVolume(void *a0, float a1, float a2);
extern void darkVolume(void *a0, float a1, float a2, float a3);
extern void sonic(void *pos, float t);

#endif /* DARKVOLUME_H */
