/*
 * ico2/omori/include/chain.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what chain.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef CHAIN_H
#define CHAIN_H

extern void ChainGeo(int a0);
extern void ChainPositionReset(char *a0);
extern int CheckChainClimbablePos(char *a0);
extern void EnableChainHang(char *a0);
extern void GetChainClimbCollision(void *out, int chain);
extern void GetChainClimbOrient(float *dst, char *a0);
extern int GetChainDirCorrectVal(char *a0, int *a1);
extern float GetChainHangRange(char *a0);
extern float GetChainLength(char *a0);
extern void GetChainPendulum(char *a0, float *a, float *b, float *c);
extern void GetRootPositionHandExtra(void *a0, float *a1);
extern void HoldChain(char *a0);
extern void LockChainGeo(char *a0);
extern void PlumbOrientUpdateChain(char *a0, float *src);
extern void ReleaseChain(char *a0);
extern void SetChainParentGObj(char *a0, void *a1);
extern void SetChainRootUpdateMode(char *gobj, int mode, float *pos);
extern void UnLockChainGeo(char *a0);
extern void UnableChainHang(char *a0);
extern void chain_simulate_term_simple(int a0);
extern void chain_sub_pendulum(char *base, int n, void *a2);
extern int collisionCheck(char *gobj);
extern void pendulum_Process(void *a0, int a1);

#endif /* CHAIN_H */
