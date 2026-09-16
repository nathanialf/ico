/*
 * ico2/sugipon/include/frameDependSequence.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what frameDependSequence.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef FRAMEDEPENDSEQUENCE_H
#define FRAMEDEPENDSEQUENCE_H

extern int ExecuteDirectSE(void *gobj, int id);
extern void ExecuteSEPackage(int a0, int a1);
extern void ExecuteSEPackageWithGroupVariation(void *a0, int a1, int a2);
extern void ExecuteSEPackageWithVolumeRate(int a0, int a1, float f);
extern void InitFrameDependSequence(void *a0);
extern void StopFDSVibration(void *a0);
extern void StopSEPackage(int a0);
extern void StopSEPackageWithGroupVariation(int a0, int a1);
extern int checkModelDataID(void *a0, int a1);
extern int checkWaterDepth(void *a0, int a1);
extern int checkWeaponType(void *a0, int a1);
extern int execSE(int a0, void *a1);
extern int execVib(int a0, void *a1);
extern int execWeaponLightOff(void);
extern void executeSEPackageByGObj(void *gobj, int no, int grp);
extern void executeSEPackageWithNoGObj(int no);
extern int playSE(int no);
extern int playSERandomID(int no, void *entry);

#endif /* FRAMEDEPENDSEQUENCE_H */
