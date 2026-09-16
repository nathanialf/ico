/*
 * ico2/omori/include/generator.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what generator.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef GENERATOR_H
#define GENERATOR_H

extern int CheckGeneratorCollision(char *gobj, float *dir);
extern char *DirectCallEnemy(char *gobj, char *mother, float *pos, float *dir, int a4);
extern void Generator_Call(char *a0);
extern void Generator_Delete(void *a0);
extern void Generator_Init(void);
extern void Generator_Mask(char *a0);
extern void Generator_MaskOff(char *a0);
extern void Generator_QuickCall(char *gobj);
extern void Generator_ResetCount(char *a0);
extern void GetGeneratorSafePosition(float *dst, char *gobj);
extern int GetMotherGenerator(int label);
extern int *GetbufpGeneratorPacket(void);
extern int GetsizeGeneratorPacket(void);
extern char *IsNeedGeneratorHard(char *mother);
extern int IsOpenGenerator(char *gobj);
extern void LockEnemyGenerate(int *self);
extern void MakeGeneratorPacket(void);
extern void ReadGeneratorPacket(void);
extern void RestoreReviveCount(char *gobj);
extern void SetInfoSpKidnapEnemy(void);
extern void SetInfoSpKidnapGenerator(short *a0);
extern void UnlockEnemyGenerate(void *a0);
extern void endfunc_BGA(char *gobj);

#endif /* GENERATOR_H */
