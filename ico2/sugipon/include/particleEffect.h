/*
 * ico2/sugipon/include/particleEffect.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what particleEffect.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef PARTICLEEFFECT_H
#define PARTICLEEFFECT_H

extern void DeleteParticleEffect(int no);
extern void DisableParticleEffectGeometryControl(int a0);
extern void DispParticleEffects(void);
extern void ExecParticleEffect(int no);
extern int GetParticleEffectData(int a0);
extern int *GetParticleEffectPackage(int idx);
extern int GetParticleIDWithName(char *name);
extern int GetParticleLoopFlag(int a0);
extern void ParticleEffects_SetAllGoal(void *goal);
extern void ResetParticleEffectPackages(int *pkg);
extern int SetParticleEffect(int id, void *pos, void *quat);
extern int SetParticleEffectActiveSensing(int id, float *pos, int *quat);
extern int SetParticleEffectByPartition(int id, float *pos, void *geo, int part);
extern void SetParticleEffectDrainLevel(int a0, float f);
extern void SetParticleEffectGeometry(int a0, int a1, int a2);
extern void SetParticleEffectPackage(int a0, int *a1, int a2);
extern void SetParticleEffectPauseFlag(int a0, int a1);
extern void SetParticleEffectUpperLimit(int no, float f);
extern int execParticleEffect(void *a0);
extern int setParticleEffect(int geo, int *pkg, int part);

#endif /* PARTICLEEFFECT_H */
