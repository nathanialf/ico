/*
 * ico2/omori/include/chain.h
 *
 * The declarations of what chain.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef CHAIN_H
#define CHAIN_H

void ChainGeo(char *gobj);
void ChainPositionReset(char *chain);
int CheckChainClimbablePos(char *chain);
void EnableChainHang(char *chain);
struct ClimbCol;
struct ChainNode;
struct ChainPendulum;
void GetChainClimbCollision(struct ClimbCol *dst, char *chain);
void GetChainClimbOrient(float *dst, char *chain);
int GetChainDirCorrectVal(char *chain, int *deg);
float GetChainHangRange(char *chain);
float GetChainLength(char *chain);
void GetChainPendulum(char *chain, float *angle, float *amp, float *cycle);
void GetRootPositionHandExtra(void *gobj, float *out);
void HoldChain(char *chain, char *owner, float *pos);
void LockChainGeo(char *chain);
void PlumbOrientUpdateChain(char *chain, float *src);
void ReleaseChain(char *chain, char *owner);
void SetChainParentGObj(char *chain, void *parent);
void SetChainRootUpdateMode(char *gobj, int mode, float *pos);
void UnLockChainGeo(char *chain);
void UnableChainHang(char *chain);

#endif /* CHAIN_H */
