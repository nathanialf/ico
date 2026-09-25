#include "common.h"
#include "debug.h"
#include "cdvd.h"
#include "memory.h"
#include "matrixDrive.h"
#include "streamMotionManager.h"

typedef struct {
    int w[7];
} SMotion;

extern SMotion D_00724AA8[];
extern int D_0028F4C0[];
extern int frame_count;
extern int ScreenHeight;
extern int D_0063A3D8;
extern int D_0063B13C;
extern int D_0063B144;
extern int D_0063BBF0;
extern int D_0063BC00;
extern int D_0063BC04;
extern int D_0063BC08;
extern int D_0063BC14;
extern int D_0063BC18;
extern int D_0063BC20;
extern int D_0063BC28;
extern int D_0063BC2C;
extern int D_0063BC30;
extern char D_0063BC38[]; /* "S:%d", the stream counter D_0063BC30 its argument */
extern int D_0063BCB8;
extern char D_00620FB0[];
extern char D_00620FF8[];
extern char D_00621030[];
extern char D_00621070[];
extern char D_006210B0[];
extern char D_006210D0[];
extern char D_00621100[];
extern char D_00621130[];

/* The ring is 0x28000 bytes; the check asks whether the write pointer has run
 * far enough ahead of the read pointer for `room` more bytes to be there. */
static inline int _checkRing(int room)
{
    unsigned int p = D_0063BC00;
    unsigned int end = p + room;
    unsigned int q = D_0063BC04;
    int r;

    if (q < p) {
        q += 0x28000;
    }
    r = 1;
    if (!(q < p) && (int)q < (int)end) {
        r = 0;
    }
    return r;
}

static inline void _setEntryOffsets(void)
{
    unsigned int off = 0;
    int i;

    for (i = 0; i < D_0063BBF0; i++) {
        D_00724AA8[i].w[3] = D_00724AA8[i].w[4] = (D_0063BC00 + off) % 0x28000;
        off += D_00724AA8[i].w[2];
    }
}

static inline void _setNextEntryOffsets(unsigned int base)
{
    unsigned int off = 0;
    int i;

    for (i = 0; i < D_0063BBF0; i++) {
        D_00724AA8[i].w[4] = (base + off) % 0x28000;
        off += D_00724AA8[i].w[2];
    }
}

static inline void _advanceRing(int amt)
{
    D_0063BC20 += amt;
    D_0063BC00 += amt;
    if ((unsigned int)D_0063BC00 > 0x27FFF) {
        D_0063BC00 -= 0x28000;
    }
}

int _infoUpdate(void)
{
    int top;
    int n;
    int i;

    if (D_0063BC14 == 0) {
        if (_checkRing(0x1000)) {
            D_0063BC18 = 0;
            for (i = 0; i < D_0063BBF0; i++) {
                int a = D_0063BC00 + D_0063BC18;

                D_00724AA8[i].w[0] = *(unsigned char *)(D_0063BC08 + (a + 2) % 0x28000);
                D_00724AA8[i].w[1] = *(unsigned char *)(D_0063BC08 + (a + 3) % 0x28000);
                D_00724AA8[i].w[2] = 16 + D_00724AA8[i].w[0] * 8 + D_00724AA8[i].w[1] * 4;
                D_0063BC18 += D_00724AA8[i].w[2];
            }
            n = 0xE23;
            if (D_0028F4C0[0] == 0) {
                n = 0xBB5;
            }
            D_0063BC14 = 1;
            D_0063BC2C = n;
        } else {
            debug_StdPrintfDummy(D_00620FB0);
            D_0063A3D8++;
            return 0;
        }
    }
    top = D_0063BC00;
    D_0063BC28 = 0;
    while (D_0063BC2C >= 2997) {
        if (!_checkRing(D_0063BC18)) {
            debug_StdPrintfDummy(D_00620FF8);
            D_0063A3D8++;
            return 0;
        } else {
            if (*(unsigned char *)(D_0063BC08 + D_0063BC00) == 0xFF) {
                return 1;
            }
            top = D_0063BC00;
            _setEntryOffsets();
            _advanceRing(D_0063BC18);
            if (_checkRing(D_0063BC18) && *(unsigned char *)(D_0063BC08 + D_0063BC00) == 0) {
                _setNextEntryOffsets(D_0063BC00);
            }
            D_0063BC2C -= 2997;
            D_0063BC30++;
            if (D_0063B144 != 0 || (D_0063B13C & 1)) {
                debug_Printf(500, ScreenHeight / 2 - 48, 0xCCCCCC00, D_0063BC38, D_0063BC30);
            }
            if (*(unsigned char *)(D_0063BC08 + top) == 1) {
                if (D_0063BC2C == 2997) {
                    debug_StdPrintfDummy(D_00621030);
                } else {
                    debug_StdPrintfDummy(D_00621070, (float)D_0063BC2C / 2997.0f);
                }
                break;
            }
        }
    }
    if (*(unsigned char *)(D_0063BC08 + top) == 1) {
        debug_StdPrintfDummy(D_006210B0);
        if (D_0063BCB8 != 0) {
            debug_StdPrintfDummy(D_006210D0, frame_count);
        } else {
            debug_StdPrintfDummy(D_00621100);
        }
    }
    if (D_0063BCB8 != 0) {
        debug_StdPrintfDummy(D_00621130);
        D_0063BC30 = 0;
        D_0063BC2C = 0;
        D_0063BCB8 = 0;
    }
    D_0063BC28 = D_0063BC2C;
    D_0063BC2C += D_0028F4C0[0] == 0 ? 0xBB5 : 0xE23;
    return 0;
}

extern char D_00621150[];
extern int D_0063BBF4;
extern int D_0063BBFC;

void PlayStreamMotion(void)
{
    if (D_0063BBFC == 0) {
        return debug_StdPrintfDummy(D_00621150);
    }
    D_0063BBF4 = 1;
    return 1;
}

/* The 0x10 bytes of frame at sp+0 belong to a declaration that emits no code in
 * this build: SRCFILE.TXT's rows for this function run 285, 286, 287, 288, 289
 * and then jump straight to 308, while the census gives the function lines
 * 285-308, so lines 290 to 307 are inside the body and carry no instructions at
 * all (a debug arm the retail build compiles out). Without the vector the body
 * is byte-identical except for the frame size, 0x30 against ROM's 0x40. */
void ClearStreamMotionEntry(char *gobj)
{
    float v[4];

    *(int *)(*(int *)(gobj + 0x15C) + 0x470) = -1;
    *(int *)(*(int *)(gobj + 0x15C) + 0x660) = 1;
    CopyVector((char *)*(int *)(gobj + 0x15C) + 0x670, ZeroVector);
    *(int *)(*(int *)(gobj + 0x15C) + 0x550) = 1;
}

/* .data, the whole of streamMotionManager.o's run: the cleared entry every
   slot is reset to. */
static SMotion emptyEntry = {{0, 0, -1, -1, -1, 0, 0}};

extern int D_0063BBF0;
extern int D_0063BBF8;
extern int D_0063BC00;
extern int D_0063BC04;
extern int D_0063BC14;
extern int D_0063BC18;
extern int D_0063BC20;
extern unsigned int D_0063BC24;
extern int D_0063BC28;
extern int D_0063BC2C;
extern char D_006211A8[];

void _deleteStreamMotionManager(void)
{
    int i;

    if (D_0063BBF0 != 0) {
        for (i = 0; i < D_0063BBF0; i++) {
            ClearStreamMotionEntry((char *)D_00724AA8[i].w[5]);
            if (D_00724AA8[i].w[6] != 0) {
                ((void (*)())D_00724AA8[i].w[6])(D_00724AA8[i].w[5]);
            }
        }
        D_0063BBF0 = 0;
    }
    for (i = 0; i < 10; i++) {
        D_00724AA8[i] = emptyEntry;
    }
    D_0063BBF4 = 0;
    D_0063BBF8 = 0;
    D_0063BC00 = 0;
    D_0063BC04 = 0;
    D_0063BC24 = 1;
    D_0063BC14 = 0;
    D_0063BC18 = 0;
    D_0063BC20 = 0;
    D_0063BC28 = 0;
    D_0063BC2C = 0;
    if (D_0063BBFC != 0) {
        D_0063BBFC = 0;
    }
    debug_StdPrintfDummy(D_006211A8);
}

extern int D_006211C8[];

void DisableStreamMotionManagerAutomaticDelete(void)
{
    D_0063BC24 = 0;
    debug_StdPrintfDummy(D_006211C8);
}

extern int D_0063BC08;
extern void memcpy();

void getStreamMotionData(char *dst, int off, int no)
{
    int size = D_00724AA8[no].w[2];
    int over = off + size - 0x28000;

    if (over > 0) {
        int first = 0x28000 - off;

        memcpy(dst, D_0063BC08 + off, first);
        return memcpy(dst + first, D_0063BC08, over);
    }
    return memcpy(dst, D_0063BC08 + off, size);
}

void getStreamMotionBlendData(char *dst, int no)
{
    int size = D_00724AA8[no].w[2];
    char a[size];
    char b[size];
    int i;

    getStreamMotionData(a, D_00724AA8[no].w[3], no);
    getStreamMotionData(b, D_00724AA8[no].w[4], no);
    for (i = 0; i < 4; i++) {
        dst[i] = a[i];
    }
}

void GetStreamMotionDataNext(int a0, int a1)
{
    getStreamMotionData(a0, D_00724AA8[a1].w[4], a1);
}

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

extern int D_0063B13C;
extern int ScreenHeight;
extern char D_0063BC40[];
extern char D_006212A0[];
extern char D_00621278[];
extern int D_0063BC1C;

void ExecStreamMotionManager(void)
{
    int i;
    int pct;

    switch (D_0063BBF4) {
    case 0:
        break;
    case 1:
        if (_infoUpdate() != 0) {
            debug_StdPrintfDummy(D_00621278);
            D_0063BBF4 = 0;
            if (D_0063BC24 != 0) {
                if (D_0063BBFC != 0) {
                    iosCdvdBackGroundMgrDelete(D_0063BBFC);
                } else {
                    _deleteStreamMotionManager();
                }
                if (D_0063BBF0 != 0) {
                    for (i = 0; i < D_0063BBF0; i++) {
                        ClearStreamMotionEntry((char *)D_00724AA8[i].w[5]);
                        if (D_00724AA8[i].w[6] != 0) {
                            ((void (*)())D_00724AA8[i].w[6])(D_00724AA8[i].w[5]);
                        }
                    }
                    D_0063BBF0 = 0;
                }
            }
        }
        break;
    }
    if (D_0063BBFC != 0) {
        unsigned int wp = D_0063BC04;
        unsigned int rp = D_0063BC00;

        if (wp < rp) {
            pct = wp + 0x28000 - rp;
        } else {
            pct = wp - rp;
        }
        pct = pct * 100 / 0x28000;
        if (D_0063B13C & 1) {
            debug_Printf(0, ScreenHeight / 2 - 16, 0xFF404000, D_0063BC40, pct);
        }
        if (D_0063B13C & 1) {
            debug_Printf(58, ScreenHeight / 2 - 16, 0x40FF4000, D_006212A0, D_0063BBF0, D_0063BC1C);
        }
    }
}

extern int D_0063A438;
extern int D_0063BC0C;
extern int D_0063BC10;
extern char D_006212B8[];
extern char D_006212D8[];

void MallocStreamMotionBuffer(void)
{
    D_0063BC08 = iosMallocDebug(D_0063A438, 0x28000, D_006212B8, 602);
    D_0063BC10 = iosMallocDebug(D_0063A438, 0x28040, D_006212B8, 604);
    D_0063BC0C = (D_0063BC10 + 0x3F) & 0xFFFFFFC0;
    if (D_0063BC08 == 0 || D_0063BC0C == 0) {
        debug_StdPrintfDummy(D_006212D8);
    }
}

inline void ClearAllStreamMotionEntry(void)
{
    int i;

    if (D_0063BBF0 == 0) {
        return;
    }
    for (i = 0; i < D_0063BBF0; i++) {
        ClearStreamMotionEntry((char *)D_00724AA8[i].w[5]);
        if (D_00724AA8[i].w[6] != 0) {
            ((void (*)())D_00724AA8[i].w[6])(D_00724AA8[i].w[5]);
        }
    }
    D_0063BBF0 = 0;
}

inline void DeleteStreamMotionManager(void)
{
    if (D_0063BBFC != 0) {
        iosCdvdBackGroundMgrDelete(D_0063BBFC);
    } else {
        _deleteStreamMotionManager();
    }
    ClearAllStreamMotionEntry();
}

/* kept local: this TU's uses of iosThreadSleep do not fit the prototype in thread.h */
extern void iosThreadSleep(void);
extern char D_00621310[];

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

inline void StopStreamMotion(void)
{
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

typedef struct {
    char c[4];
} StreamMotionHead;

inline float GetStreamMotionData(char *dst, int no)
{
    if (D_00724AA8[no].w[3] < 0) {
        *(StreamMotionHead *)dst = *(StreamMotionHead *)D_00621228;
        debug_StdPrintfDummy(D_00621230);
        return -1.0f;
    }
    getStreamMotionData(dst, D_00724AA8[no].w[3], no);
    return (float)D_0063BC28 / 2997.0f;
}

inline void InitStreamMotionManager(void)
{
    D_0063BC10 = 0;
    D_0063BC08 = 0;
    D_0063BC0C = 0;
}

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

inline void SetStreamMotionFinishCallBackFunc(int a0, int a1)
{
    D_00724AA8[a0].w[6] = a1;
}

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

inline int _closeHander(void)
{
    _deleteStreamMotionManager();
    return 1;
}

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
