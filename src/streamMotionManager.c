#include "common.h"

/* prototypes: their order is the inline tail's emission order */
void StandbyStreamMotion(int self);
void StopStreamMotion(void);
void DeleteStreamMotionManager(void);
int EntryStreamMotion(char *a0);
int GetDataSizeOfStreamMotion(int no);
float GetStreamMotionData(char *dst, int no);
void InitStreamMotionManager(void);
int CheckReadyStreamMotion(void);
void SetStreamMotionFinishCallBackFunc(int a0, int a1);
void FreeStreamMotionBuffer(void);
void ClearAllStreamMotionEntry(void);
int _closeHander(void);
int _handler(int self);

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
typedef struct { int w[7]; } SMotion;
extern SMotion D_00724AA8[];
void GetStreamMotionDataNext(int a0, int a1) {
    getStreamMotionData(a0, D_00724AA8[a1].w[4], a1);
}
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
extern int D_0063BBF0;

inline void ClearAllStreamMotionEntry(void)
{
    int i;

    if (D_0063BBF0 == 0) {
        return;
    }
    for (i = 0; i < D_0063BBF0; i++) {
        ClearStreamMotionEntry(D_00724AA8[i].w[5]);
        if (D_00724AA8[i].w[6] != 0) {
            ((void (*)())D_00724AA8[i].w[6])(D_00724AA8[i].w[5]);
        }
    }
    D_0063BBF0 = 0;
}
extern int D_0063BBFC;
extern void iosCdvdBackGroundMgrDelete();

inline void DeleteStreamMotionManager(void)
{
    if (D_0063BBFC != 0) {
        iosCdvdBackGroundMgrDelete(D_0063BBFC);
    } else {
        _deleteStreamMotionManager();
    }
    ClearAllStreamMotionEntry();
}
extern int iosCdvdBackGroundMgrAdd();
extern void iosThreadSleep(void);
extern char D_00621310[];
extern int D_0063BC1C;

inline void StandbyStreamMotion(int self)
{
    DeleteStreamMotionManager();
    while (D_0063BBFC != 0) {
        debug_StdPrintfDummy(D_00621310);
        iosThreadSleep();
    }
    D_0063BBFC = iosCdvdBackGroundMgrAdd(self, _handler, 0, 0, 0, 0, _closeHander, 0);
    D_0063BC1C = self;
}
inline void StopStreamMotion(void) {
    D_0063BBF4 = 0;
}
inline int EntryStreamMotion(char *a0)
{
    int no = D_0063BBF0;

    D_00724AA8[no].w[5] = (int)a0;

    *(int *)(*(int *)(a0 + 0x15C) + 0x470) = no;
    *(int *)(*(int *)(a0 + 0x15C) + 0x4F0) = 0;
    *(int *)(*(int *)(a0 + 0x15C) + 0x4EC) = 0;
    *(int *)(*(int *)(a0 + 0x15C) + 0x550) = 0;
    D_0063BBF0 = no + 1;
    return no;
}
extern char D_006211E8[];

inline int GetDataSizeOfStreamMotion(int no)
{
    if (D_00724AA8[no].w[3] < 0) {
        debug_StdPrintfDummy(D_006211E8);
        return 4;
    }
    return D_00724AA8[no].w[2];
}
extern char D_00621228[];
extern char D_00621230[];
extern int D_0063BC28;
extern float D_006396CC;
extern void getStreamMotionData();

typedef struct { char c[4]; } StreamMotionHead;

inline float GetStreamMotionData(char *dst, int no)
{
    if (D_00724AA8[no].w[3] < 0) {
        *(StreamMotionHead *)dst = *(StreamMotionHead *)D_00621228;
        debug_StdPrintfDummy(D_00621230);
        return -1.0f;
    }
    getStreamMotionData(dst, D_00724AA8[no].w[3], no);
    return (float)D_0063BC28 / D_006396CC;
}
extern int D_0063BC08;
extern int D_0063BC0C;
extern int D_0063BC10;

inline void InitStreamMotionManager(void) {
    D_0063BC10 = 0;
    D_0063BC08 = 0;
    D_0063BC0C = 0;
}
extern int D_0063BC00;
extern int D_0063BC04;

inline int CheckReadyStreamMotion(void)
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
inline void SetStreamMotionFinishCallBackFunc(int a0, int a1) {
    D_00724AA8[a0].w[6] = a1;
}
extern int D_0063BC08;
extern int D_0063BC0C;
extern int D_0063BC10;
extern void iosFree();

inline void FreeStreamMotionBuffer(void)
{
    if (D_0063BC08 != 0) {
        iosFree(D_0063BC08);
        iosFree(D_0063BC10);
        D_0063BC10 = 0;
        D_0063BC08 = 0;
        D_0063BC0C = 0;
    }
}
extern void _deleteStreamMotionManager();

inline int _closeHander(void) {
    _deleteStreamMotionManager();
    return 1;
}
extern int D_0063BBF8;
extern void iosCdvdBackGroundRead();

inline int _handler(int self)
{
    unsigned int wp = D_0063BC04;
    unsigned int rp = D_0063BC00;
    int rest;
    int size;

    if (wp < rp) {
        rest = wp + 0x28000 - rp;
    } else {
        rest = wp - rp;
    }
    switch (D_0063BBF8) {
    default:
    case 0:
        if (rest > 0x13FFF) {
            break;
        }
        D_0063BBF8 = 1;
    case 1:
        size = 0x28000 - rest;
        size = ((size - 1) / 2048) * 2048;
        iosCdvdBackGroundRead(self, D_0063BC0C, size);
        _transRingBuf(&D_0063BC04, D_0063BC08, 0x28000, D_0063BC0C, size);
        D_0063BBF8 = 0;
        break;
    }
    return 0;
}
