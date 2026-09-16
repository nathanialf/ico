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

void DeleteParticleEffect(int no);
void DisableParticleEffectGeometryControl(int a0);
void DispParticleEffects(void);
void ExecParticleEffect(int no);
int GetParticleEffectData(int a0);
int *GetParticleEffectPackage(int idx);
int GetParticleIDWithName(char *name);
int GetParticleLoopFlag(int a0);
void ParticleEffects_SetAllGoal(void *goal);
void ResetParticleEffectPackages(int *pkg);
int SetParticleEffect(int id, void *pos, void *quat);
int SetParticleEffectActiveSensing(int id, float *pos, int *quat);
int SetParticleEffectByPartition(int id, float *pos, void *geo, int part);
void SetParticleEffectDrainLevel(int a0, float f);
void SetParticleEffectGeometry(int a0, int a1, int a2);
void SetParticleEffectPackage(int a0, int *a1, int a2);
void SetParticleEffectPauseFlag(int a0, int a1);
void SetParticleEffectUpperLimit(int no, float f);
int execParticleEffect(void *a0);
int setParticleEffect(int geo, int *pkg, int part);

#endif /* PARTICLEEFFECT_H */
