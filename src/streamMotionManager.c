#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/streamMotionManager", _infoUpdate);
extern char D_00621150[];
extern int D_0063BBF4;
extern int D_0063BBFC;
extern void debug_StdPrintfDummy();

void PlayStreamMotion(void)
{
    if (D_0063BBFC == 0) {
        return debug_StdPrintfDummy(D_00621150);
    }
    D_0063BBF4 = 1;
    return 1;
}
INCLUDE_ASM("asm/nonmatchings/src/streamMotionManager", ClearStreamMotionEntry);
INCLUDE_ASM("asm/nonmatchings/src/streamMotionManager", _deleteStreamMotionManager);
extern int D_006211C8[];
extern unsigned int D_0063BC24;

void DisableStreamMotionManagerAutomaticDelete(void)
{
    D_0063BC24 = 0;
    debug_StdPrintfDummy(D_006211C8);
}
INCLUDE_ASM("asm/nonmatchings/src/streamMotionManager", getStreamMotionData);
INCLUDE_ASM("asm/nonmatchings/src/streamMotionManager", getStreamMotionBlendData);
INCLUDE_ASM("asm/nonmatchings/src/streamMotionManager", GetStreamMotionDataNext);
extern void memcpy();

void _transRingBuf(int *idx_p, char *dst, int size, char *src, int amt)
{
    int old_idx = *idx_p;
    int new_idx = old_idx + amt;
    *idx_p = new_idx;
    if (new_idx >= size) {
        int overflow = new_idx - size;
        int first_chunk = amt - overflow;
        *idx_p = overflow;
        memcpy(dst + old_idx, src, first_chunk);
        memcpy(dst, src + first_chunk, *idx_p);
        return;
    }
    memcpy(dst + old_idx, src, amt);
}
INCLUDE_ASM("asm/nonmatchings/src/streamMotionManager", ExecStreamMotionManager);
INCLUDE_ASM("asm/nonmatchings/src/streamMotionManager", MallocStreamMotionBuffer);
INCLUDE_ASM("asm/nonmatchings/src/streamMotionManager", StandbyStreamMotion);
void StopStreamMotion(void) {
    D_0063BBF4 = 0;
}
INCLUDE_ASM("asm/nonmatchings/src/streamMotionManager", DeleteStreamMotionManager);
INCLUDE_ASM("asm/nonmatchings/src/streamMotionManager", EntryStreamMotion);
INCLUDE_ASM("asm/nonmatchings/src/streamMotionManager", GetDataSizeOfStreamMotion);
INCLUDE_ASM("asm/nonmatchings/src/streamMotionManager", GetStreamMotionData);
extern int D_0063BC08;
extern int D_0063BC0C;
extern int D_0063BC10;

void InitStreamMotionManager(void) {
    D_0063BC10 = 0;
    D_0063BC08 = 0;
    D_0063BC0C = 0;
}
extern int D_0063BC00;
extern int D_0063BC04;

int CheckReadyStreamMotion(void)
{
    unsigned int p = D_0063BC00;
    unsigned int q = D_0063BC04;
    unsigned int end = p + 0x1000;
    int r;
    if (q < p)
        q += 0x28000;
    r = 1;
    if (!(q < p) && (int)q < (int)end)
        r = 0;
    return r;
}
typedef struct { int w[7]; } SMotion;
extern SMotion D_00724AA8[];
void SetStreamMotionFinishCallBackFunc(int a0, int a1) {
    D_00724AA8[a0].w[6] = a1;
}
extern int D_0063BC08;
extern int D_0063BC0C;
extern int D_0063BC10;
extern void iosFree();

void FreeStreamMotionBuffer(void)
{
    if (D_0063BC08 != 0) {
        iosFree(D_0063BC08);
        iosFree(D_0063BC10);
        D_0063BC10 = 0;
        D_0063BC08 = 0;
        D_0063BC0C = 0;
    }
}
INCLUDE_ASM("asm/nonmatchings/src/streamMotionManager", ClearAllStreamMotionEntry);
extern void _deleteStreamMotionManager();

int _closeHander(void) {
    _deleteStreamMotionManager();
    return 1;
}
INCLUDE_ASM("asm/nonmatchings/src/streamMotionManager", _handler);
