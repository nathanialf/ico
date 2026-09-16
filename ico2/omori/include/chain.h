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

void ChainGeo(int a0);
void ChainPositionReset(char *a0);
int CheckChainClimbablePos(char *a0);
void EnableChainHang(char *a0);
void GetChainClimbCollision(void *out, int chain);
void GetChainClimbOrient(float *dst, char *a0);
int GetChainDirCorrectVal(char *a0, int *a1);
float GetChainHangRange(char *a0);
float GetChainLength(char *a0);
void GetChainPendulum(char *a0, float *a, float *b, float *c);
void GetRootPositionHandExtra(void *a0, float *a1);
void HoldChain(char *a0);
void LockChainGeo(char *a0);
void PlumbOrientUpdateChain(char *a0, float *src);
void ReleaseChain(char *a0);
void SetChainParentGObj(char *a0, void *a1);
void SetChainRootUpdateMode(char *gobj, int mode, float *pos);
void UnLockChainGeo(char *a0);
void UnableChainHang(char *a0);
void chain_simulate_term_simple(int a0);
void chain_sub_pendulum(char *base, int n, void *a2);
int collisionCheck(char *gobj);
void pendulum_Process(void *a0, int a1);

#endif /* CHAIN_H */
