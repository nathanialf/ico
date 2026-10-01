/*
 * ico2/omori/include/generator.h
 *
 * The declarations of what generator.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef GENERATOR_H
#define GENERATOR_H

struct GVGeo2;
struct GenWork *InitGeneratorGeo(char *gobj, struct GVGeo2 *src);
void Generator_Call(char *a0);
void Generator_ResetCount(char *a0);
void Generator_Mask(char *a0);
void Generator_MaskOff(char *a0);
void SetMotherGenerator(int no, int label);
void Generator_Init(void);
int *GetbufpGeneratorPacket(void);
int GetsizeGeneratorPacket(void);
int RestoreGeneratorGeo(float *dst, float *src);
int RestoreGeneratorExtGeo(char *a0, short *a1);
int MemoryGenerator(short *a0, char *a1);
void *IsEnableCallEnemy(char *self);
char *DirectCallEnemy(char *gobj, char *mother, float *pos, float *dir, int a4);
void LockEnemyGenerate(int *self);
void UnlockEnemyGenerate(void *a0);
void RestoreReviveCount(char *gobj);
void ReturnEnemyToGenerator(int a0);
int GeneratorWorkEnd(char *a0);
int SearchActiveGenerator(void);
void ResetReviveCountEnemy(int a0);
void SetInfoSpKidnapGenerator(short *a0);
void SetInfoSpKidnapEnemy(void);
int IsOpenGenerator(char *gobj);
int IsEnableCallEnemyByTargetGObj(void *a0);

int CheckGeneratorCollision(char *gobj, float *dir);
void Generator_Delete(void *a0);
void Generator_QuickCall(char *gobj);
void GetGeneratorSafePosition(float *dst, char *gobj);
int GetMotherGenerator(int label);
/* K&R, unprototyped on purpose: generator.c defines it with one parameter and
   calls it with none at its own line 196, so only this form serves both. */
char *IsNeedGeneratorHard();
void MakeGeneratorPacket(void);
void ReadGeneratorPacket(void);
void endfunc_BGA(char *gobj);

#endif /* GENERATOR_H */
