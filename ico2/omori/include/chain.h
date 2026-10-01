/*
 * ico2/omori/include/chain.h
 *
 * The declarations of what chain.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef CHAIN_H
#define CHAIN_H

void ChainGeo(char *gobj);
void ChainPositionReset(char *a0);
int CheckChainClimbablePos(char *a0);
void EnableChainHang(char *a0);
struct ClimbCol;
void GetChainClimbCollision(struct ClimbCol *dst, char *a0);
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
