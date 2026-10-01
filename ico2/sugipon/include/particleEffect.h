/*
 * ico2/sugipon/include/particleEffect.h
 *
 * The declarations of what particleEffect.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef PARTICLEEFFECT_H
#define PARTICLEEFFECT_H

struct IosMemPart;

struct PEGeo;

struct PEPackage;

/* particle-effect: one particle effect file, 0x50 bytes. Readers:
 * ico2/common/src/icoMisc.c, ico2/sugipon/src/effectTool.c (the path at
 * 0x20), particleEffect.c. */
typedef struct {      /* field names derived */
    char name[32];    /* 0x00 */
    char path[48];    /* 0x20 */
} ParticleEffectFile; /* derived name */

/* the 61 particle effect files (the particle-effect data member) */
extern const ParticleEffectFile particleEffectFile[];
void DeleteParticleEffect(int no);
void DisableParticleEffectGeometryControl(int a0);
void DispParticleEffects(void);
void ExecParticleEffect(int no);
void ExecParticleEffects(void);
int GetParticleEffectData(int a0);
int *GetParticleEffectPackage(int idx);
int GetParticleIDWithName(char *name);
int GetParticleLoopFlag(int a0);
void InitParticleEffects(void);
void ParticleEffects_SetAllGoal(void *goal);
void ResetParticleEffectPackages(int *pkg);
int SetParticleEffect(int id, void *pos, void *quat);
int SetParticleEffectActiveSensing(int id, void *pos, void *quat);
int SetParticleEffectByPartition(int id, void *pos, void *quat, struct IosMemPart *part);
void SetParticleEffectDrainLevel(int a0, float f);
void SetParticleEffectGeometry(int id, void *pos, void *quat);
void SetParticleEffectPackage(int a0, int *a1, int a2);
void SetParticleEffectPauseFlag(int a0, int a1);
void SetParticleEffectUpperLimit(int no, float f);
void SetParticleEffectClipEnableFlag(int a0, int a1);
void DeleteParticleEffectsByPackage(int *pkg);
void DeleteParticleEffectsByID(int id);

#endif /* PARTICLEEFFECT_H */
