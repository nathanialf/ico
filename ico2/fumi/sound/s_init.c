#include "typedef.h"
#include "s_init.h"
#include "debug.h"
#include "cdvd.h"
#include "ios.h"
#include "memory.h"
#include "pad.h"
#include "adpcm_init.h"
#include "soundManager.h"
#include "camera-root.h"
#include "matrixDrive.h"
#include "Primitive.h"
#include <sifrpc.h>
#include <string.h>
#include <libvu0.h>
#include <eekernel.h>
#include "GifPacket.h"
#include "debug_exception.h"
#include "main.h"
#include <assert.h>
#include <sound.h>
#include "include_asm.h"

/* The TU's own .sbss and .bss, tentative definitions: the SPU buffer
   segments' next free addresses, the ADPCM and SE channel masks, the 16
   sound data areas and the 48 SE slots. */
static int bufSeg1Next; /* derived name */

static int bufSeg2Next; /* derived name */

static long long adpcmChMask;

static long long seChMask;

static SqEntry soundDataTbl[16]; /* derived name */

static SeSlot seSlotTbl[48]; /* derived name */

/* the SPU buffer's segment-0 allocation pointer and the top of segment 1
   (soundBufAlloc), the reverb depth and output mode the Set/Get pairs keep,
   the master SE volume rate, the environment-close request and the
   semi-common load flag */
static int bufSeg0Next = 0x5010; /* derived name */

static int bufSeg1Top = 0x1D9020; /* derived name */

static int reverbDepth = 10; /* derived name */

float soundSeEnvMasterVolRate = 1.0f;

int seEnvForceClose = 0;

static int outputMode = 0; /* derived name */

static int seSemiCommonLoaded = 0; /* derived name */

INCLUDE_ASM_LIT(Ee2Iop);

int soundInit(void)
{
    int i;
    char *p;

    debug_StdPrintfDummy("SgInit()\n");
    SgInit();
    if (iosCdvdMediaType == 1) {
        SgSetDigitalOutputMode(0x80);
    } else {
        SgSetDigitalOutputMode(0x880);
    }
    debug_StdPrintfDummy("SgSetTickMode()\n");
    SgSetTickMode(60);
    SgSetReverbEndAddr(0, 0x1FFFFF);
    SgSetReverbEndAddr(1, 0x1DFFFF);
    SgSetReverbType(0, 4);
    SgSetReverbDepth(0, 0xCCC, 0xCCC);
    SgSetReverbType(1, 4);
    SgSetReverbDepth(0, 0xCCC, 0xCCC);
    SgSetMasterVol(0, 0, 0);
    SgSetMasterVol(1, 0, 0);
    for (i = 15; i >= 0; i--) {
        *(int *)&((char *)soundDataTbl)[i * 48] = 0;
    }
    adpcmChMask = 0;
    seChMask = 0;
    /* the request slot of every SeSlot, walked through a base pointer: that is
       what keeps the +0x30 out of the symbol's %hi/%lo and in the loop start value */
    p = (char *)seSlotTbl;
    for (i = 47; i >= 0; i--) {
        *(int *)&p[i * 64 + 0x30] = 0;
    }
    AdpcmStreamInit();
    seEnvForceClose = 0;
    return 0;
}

void soundOutputModeSet(int mode)
{
    outputMode = mode;
    SgSetOutputMode(mode);
}

void soundReverbDepthSet(int depth)
{
    int val;
    reverbDepth = depth;
    val = (depth * 32767) / 100;
    SgSetReverbDepth(0, val, val);
    SgSetReverbDepth(1, val, val);
    SgSetMasterVol(0, 0x3FFF, 0x3FFF);
    SgSetMasterVol(1, 0x3FFF, 0x3FFF);
}

INCLUDE_ASM(soundAllocIopHeap);

void soundAllocIopFree(void)
{
    sceSifFreeIopHeap(soundIopHeapAddrs);
}

/* A free channel's allocation, shared by soundDataOpenChk and
   _soundSeDefPlay. */
static inline int seChAlloc(SqEntry *req) /* derived name */
{
    long long one = 1;
    long long bit;
    int i;

    for (i = 0; i < 48; i++) {
        bit = one << i;
        if ((seChMask & bit) == 0) {
            goto found;
        }
    }
    return -1;
found:
    seChMask |= bit;
    req->seMask |= bit;
    /* the slot indexed by byte offset */
    ((SeSlot *)&((char *)seSlotTbl)[i * 64])->flag.all &= 0xFDFFFFFF;
    return i;
}

/* A slot's request release, shared by soundDataOpenChk, soundDataClose and
   _soundSeDefStop.  seReqRelease takes the channel, not the slot, because
   _soundSeDefStop's copy recomputes the request word's address from it. */
static inline void seReqChClear(SqEntry *req, int ch) /* derived name */
{
    long long bit = (long long)1 << ch;

    if ((req->seMask & bit) != 0) {
        req->seMask &= ~bit;
        seChMask &= ~bit;
        seSlotTbl[ch].num = seSlotTbl[ch].num + 1;
        seSlotTbl[ch].req = 0;
    }
}

static inline void seReqRelease(int ch) /* derived name */
{
    SqEntry *req = seSlotTbl[ch].req;

    if (req != 0)
        seReqChClear(req, ch);
}

INCLUDE_ASM_LIT(soundDataAreaGet);

INCLUDE_ASM(soundDataOpenChk);

INCLUDE_ASM(soundBufAlloc);

void soundBufSegFree(int seg, int mode);

INCLUDE_ASM(soundBufSegFree);

INCLUDE_ASM_LIT(soundBufAdpcmChAlloc);

INCLUDE_ASM(soundBDDataSet);

INCLUDE_ASM(soundDataOpen);

INCLUDE_ASM(soundDataOpenSync);

void soundDataClose(SqEntry *self);

INCLUDE_ASM(soundDataClose);

void soundDataSegAllClose(int seg, int mode)
{
    int i;
    char *tbl;
    /* base in the loop header, as its sibling
       soundDataSegNextStageNotUseClose carries it */
    for (i = 0, tbl = (char *)soundDataTbl; i < 768; i += 0x30) {
        SqEntry *p = (SqEntry *)(tbl + i);
        if (*(int *)p != 0 && p->seg == seg && p->mode == mode) {
            soundDataClose(p);
        }
    }
    if (mode == 2)
        return;
    soundBufSegFree(seg, mode);
}

static void soundSeVolSet(SeSlot *self)
{
    int l;
    int r;
    int cur;
    int d;
    int vol;

    if (self->flag.all & 0x20000000) {
        r = 0;
        l = 0;
    } else {
        l = (int)((float)self->level0 * self->volumeRate);
        r = (int)((float)self->level1 * self->volumeRate);
    }
    if (self->owner == 0xFFFFFFFF && self->env != 0) {
        l = (int)((float)l * soundSeEnvMasterVolRate);
        r = (int)((float)r * soundSeEnvMasterVolRate);
    }
    if (l < 0) {
        l = 0;
    } else {
        l = (l < 4097) ? l : 4096;
    }
    if (r < 0) {
        r = 0;
    } else {
        r = (r < 4097) ? r : 4096;
    }
    cur = *(unsigned short *)&self->vol0;
    d = (short)(l - cur);
    if (((d < 0) ? -d : d) < 256 || (short)cur == -1) {
        self->vol0 = l;
    } else {
        self->vol0 = (d > 0) ? cur + 256 : cur - 256;
    }
    cur = *(unsigned short *)&self->flag;
    d = (short)(r - cur);
    if (((d < 0) ? -d : d) < 256 || (short)cur == -1) {
        *(short *)&self->flag = r;
    } else {
        *(short *)&self->flag = (d > 0) ? cur + 256 : cur - 256;
    }
    SgSetSeVolDirect(self->handle, self->vol0, *(short *)&self->flag);
    if (self->padAct != 0) {
        vol = (r < l) ? l : r;
        vol = (int)((float)vol * (1.0f / 4096.0f) * 255.0f);
        iosPadActVolumeSet(self->padAct, vol & 0xFF);
    }
}

/* The debug SE-info page: one row per editable field of the slot the pad is
   parked on, walked with the D-pad and nudged by `step`.  The row is a label
   followed by a nested value record. */
typedef struct DbgVal { /* field names derived */
    int ptr;            /* 0x04 */
    int type;           /* 0x08 : 0 = int cell, 1 = float cell */
    int mode;           /* 0x0C : 1 = colour the row when the value is past `dist` */
    float step;         /* 0x10 */
} DbgVal;               /* derived name */

typedef struct DbgRow { /* field names derived */
    char *label;        /* 0x00 */
    DbgVal v;           /* 0x04 */
} DbgRow;               /* derived name */

static inline void soundSeEnvDefaultSet(SeSlot *self);

static void debug_DispSEInfo(void)
{
    /* dbg is a local debug switch, set from the debugger to keep the selected
       slot soloed.  The page's own state is local static: the selected row
       and the solo flag in .sbss, the edited centre in .bss. */
    static sceVu0FVECTOR center;
    static int curRow;
    static int solo;
    static int page = 0; /* derived name */
    static int show = 1; /* derived name */
    float v[4];
    float step = 0.0f;
    float dist;
    float *cam;
    SeSlot *self;
    SeSlot *p;
    int i;
    int num;
    int dbg = 0; /* local debug switch, see the test after the solo toggle */

    cam = GetCameraPos();
    if (pad[0].flags & 0x400) {
        show ^= 1;
    }
    if (show == 0) {
        return;
    }
    if (pad[0].rep & 0x20) {
        page = page + 1;
    }
    for (i = page;; i++) {
        if (i >= 48) {
            page = 0;
            return;
        }
        if (seSlotTbl[i].req != 0) {
            break;
        }
    }
    self = &seSlotTbl[i];
    page = i;
    if (pad[0].flags & 0x40) {
        solo ^= 1;
    }
    if (dbg) {
        solo = 1;
    }
    for (i = 0; i < 48; i++) {
        if (*(int *)&((char *)seSlotTbl)[i * 64 + 0x30] == 0) {
            continue;
        }
        p = &seSlotTbl[i];
        if (self == p) {
            self->flag.bit.soloMute = 0;
        } else {
            p->flag.bit.soloMute = solo;
        }
    }
    if (pad[0].flags & 0x80) {
        soundSeEnvDefaultSet(self);
    }
    if (self->pos != 0) {
        sceVu0CopyVector(center, self->pos);
        if (self->flag.bit.levelHeight == 1) {
            center[1] = cam[1];
        }
        sceVu0SubVector(v, cam, center);
        dist = FSqrt(sceVu0InnerProduct(v, v));
    } else {
        dist = center[0] = center[1] = center[2] = 0.0f;
    }
    {
        int sel = self->flag.bit.maxVolumeType;
        DbgRow *row;
        DbgRow *cur;
        DbgRow list[9] = {
            {"center x", {(int)&center[0], 1, 0, 10.0f}},
            {"center y", {(int)&center[1], 1, 0, 10.0f}},
            {"center x", {(int)&center[2], 1, 0, 10.0f}},
            {"volumeRate", {(int)&self->volumeRate, 1, 1, 0.1f}},
            {"max volume range", {(int)&self->maxVolumeRange, 1, 1, 10.0f}},
            {"attenuator", {(int)&self->attenuator, 1, 1, 10.0f}},
            {"volume length", {(int)&self->volumeLength, 1, 1, 10.0f}},
            {"max volume type", {(int)&sel, 0, 0, 1.0f}},
            {"stereo rate", {(int)&self->stereoRate, 1, 0, 0.05f}},
        };

        num = 9;

        if (pad[0].rep & 0x1000) {
            curRow = curRow - 1;
        }
        if (pad[0].rep & 0x4000) {
            curRow = curRow + 1;
        }
        curRow = (curRow + num) % num;
        cur = &list[curRow];
        if (pad[0].rep & 0x2000) {
            step = cur->v.step;
        }
        if (pad[0].rep & 0x8000) {
            step = -cur->v.step;
        }
        debug_PrintfDummy(10, 70, 0xFFFFFF00u, "req no %d %s %f\n", page, self->src, dist);
        for (i = 0, row = list; i < num; i++, row++) {
            int col = 0xFFFFFF00;

            if (curRow == i)
                strcpy((char *)v, ">");
            else
                strcpy((char *)v, " ");
            switch (row->v.type) {
            case 0:
                if (curRow == i) {
                    *(int *)row->v.ptr = (int)((float)*(int *)row->v.ptr + step);
                }
                debug_PrintfDummy(10, i * 10 + 80, col, "%s%8s = %d\n", v, row->label,
                                  *(int *)list[i].v.ptr);
                break;
            case 1:
                if (curRow == i) {
                    *(float *)row->v.ptr += step;
                }
                if (row->v.mode && dist != 0.0f && dist < *(float *)row->v.ptr) {
                    col = 0xFF000000;
                }
                debug_PrintfDummy(10, i * 10 + 80, col, "%s%8s = %f\n", v, row->label,
                                  *(float *)list[i].v.ptr);
                break;
            }
        }
        self->flag.bit.maxVolumeType = sel;
        if (self->pos != 0) {
            sceVu0CopyVector(self->pos, center);
            MatrixDrive_PushMatrix();
            {
                sceVu0IVECTOR col = {0x00, 0x10, 0x20, 0x80};

                gif_StartPacketPri(11);
                sceVu0UnitMatrix(MatrixDrive_GetMatrix());
                MatrixDrive_TransMatrixV((char *)center);
                prim_DispWireSphere(100.0f, col, 16, 8);
                gif_EndPacket();
            }
            MatrixDrive_PopMatrix();
        }
    }
}

static void sound3DParamSet(SeSlot *self)
{
    float v[4];
    float dist;
    int ang;
    float *cam;
    float *obj;
    float vol;
    float rate;
    float range;
    float front;
    float volL;
    float volR;
    int n;
    int a;
    int pan;
    int ret;

    self->level1 = 0x1000;
    self->level0 = 0x1000;
    if (self->proc != 0) {
        ret = self->proc();
        if (ret > 0) {
            self->flag.bit.audible = 1;
            self->flag.bit.placed = 0;
        } else if (ret < 0) {
            self->flag.bit.audible = 0;
        } else {
            self->level0 = 0;
            self->level1 = 0;
            self->flag.bit.audible = 0;
        }
        self->src->procRan = 1;
    }
    if ((self->flag.all & 0x02000000) && self->src->procRan == 0) {
        if (self->flag.all & 0x20000000) {
            SgSetSeVolDirect(self->handle, 0, 0);
        }
        return;
    }
    if ((self->flag.all & 0x01000000) == 0 || (obj = self->pos) == 0) {
        soundSeVolSet(self);
        return;
    }
    self->flag.all |= 0x02000000;
    if (self->flag.bit.levelHeight == 1) {
        cam = GetCameraPos();
        sceVu0CopyVector(v, self->pos);
        v[1] = cam[1];
        CameraGetOtherObjOffset(v, &dist, &ang);
    } else {
        CameraGetOtherObjOffset(obj, &dist, &ang);
    }
    if (dist > self->volumeLength) {
        vol = 0.0f;
    } else if (dist < self->maxVolumeRange) {
        vol = 1.0f;
    } else {
        dist = dist - self->maxVolumeRange;
        range = self->attenuator - self->maxVolumeRange;
        if (self->flag.bit.maxVolumeType == 0) {
            rate = dist / range;
            vol = 1.0f / (rate + 1.0f);
        } else {
            if (dist < range) {
                rate = dist / range;
                vol = 1.0f / (rate + 1.0f);
            } else {
                dist = dist - range;
                vol = 1.0f / (dist / ((self->volumeLength - self->maxVolumeRange) - range) + 1.0f) -
                      0.5f;
            }
        }
    }
    if (self->flag.bit.stereo == 1) {
        a = ang;
        pan = a;
        if (self->flag.bit.rearFade == 1) {
            a = (a <= -1) ? -a : a;
            front = (float)a * -0.0027777778f + 1.0f;
        } else {
            front = 1.0f;
        }
        if (pan >= 0) {
            volL = 1.0f;
            a = pan;
            if (a >= 91) {
                a = 180 - a;
            }
            volR = -(1.0f - self->stereoRate) / 90.0f * (float)a + 1.0f;
        } else {
            volR = 1.0f;
            a = -pan;
            if (a >= 91) {
                a = 180 - a;
            }
            volL = -(1.0f - self->stereoRate) / 90.0f * (float)a + 1.0f;
        }
    } else {
        volR = 1.0f;
        front = 1.0f;
        volL = 1.0f;
    }
    n = (int)(vol * 4096.0f * front);
    self->level0 = (float)n * volR;
    self->level1 = (float)n * volL;
    soundSeVolSet(self);
}

/* as in the generated sedef member, which defines the rows const; this TU
   writes procRan into them */
extern SeDef seDef[];

/* The slot search between soundSeGroupStop and soundSeGroupGet, which
   _soundSeDefPlay inlines twice. */
static inline int se_find_slot(SeDef *src, SeSlot **out) /* derived name */
{
    SeSlot *p = seSlotTbl;
    int i;

    for (i = 0; i < 48; i++) {
        if (p->req != 0 && p->src == src) {
            goto found;
        }
        p++;
    }
    if (out != 0) {
        *out = 0;
    }
    return -1;
found:
    if (out != 0) {
        *out = p;
    }
    return i;
}

static int seGroupSerial = 0; /* derived name */

/* soundIopHeapAddrs is the last object of the TU's .sdata, after the group
   serial above, so its definition sits here although soundAllocIopHeap
   (declared through s_init.h) fills it first. */
int soundIopHeapAddrs = 0;

static int _soundSeDefPlay(int kind, unsigned int owner, float *pos, int playMode,
                           const SeEnvDef *env, SeSlot **out, float vol);

INCLUDE_ASM(_soundSeDefPlay);

void _soundSeDefStop(int id, int noRelease);

INCLUDE_ASM(_soundSeDefStop);

void soundSeDefStop(int id)
{
    _soundSeDefStop(id, 0);
}

void soundSeDefStopNoRelease(int id)
{
    _soundSeDefStop(id, 1);
}

/* sound.h leaves it out */
extern void SgSetSePitchDirect(unsigned int id, int pitch);

void soundSeDefPitchSet(int id, int pitch)
{
    SeSlot *entry;
    short h;
    entry = &seSlotTbl[id & 0xFF];
    h = entry->handle;
    if (h < 0)
        return;
    id = id >> 8;
    if (id != entry->num)
        return;
    SgSetSePitchDirect(h, pitch);
}

inline int soundSeSemiCommonLoadChk(void)
{
    return seSemiCommonLoaded;
}

static inline void soundSeEnvDefaultSet(SeSlot *self)
{
    const SeEnvDef *env = self->env;

    if (env->volumeRate != 0.0f) {
        self->volumeRate = env->volumeRate;
    } else {
        self->volumeRate = self->src->volume;
    }
    if (env->maxVolumeRange != 0.0f) {
        self->maxVolumeRange = env->maxVolumeRange;
    } else {
        self->maxVolumeRange = 500.0f;
    }
    if (env->attenuator != 0.0f) {
        self->attenuator = env->attenuator;
    } else {
        self->attenuator = 1000.0f;
    }
    if (env->volumeLength != 0.0f) {
        self->volumeLength = env->volumeLength;
    } else {
        self->volumeLength = 3000.0f;
    }
    self->flag.bit.maxVolumeType = env->maxVolumeType;
    self->flag.bit.levelHeight = env->levelHeight;
    self->flag.bit.stereo = env->stereo;
    self->stereoRate = 0.1f;
}

INCLUDE_ASM(soundSeEnvPlay);

/* &stageData[0].seEnvFirst, the range soundSeEnvNotUseClose walks */
extern char D_005F5E60[];

INCLUDE_ASM(soundSeEnvNotUseClose);

INCLUDE_ASM(soundDataSegNextStageNotUseClose);

inline int debug_req(void)
{
    char *e = (char *)seSlotTbl;
    int sz = 0x3C;
    int i = 0x2F;
    do {
        if (*(int *)(e + 0x30) != 0) {
            debug_StdPrintfDummy("num %d %d\n", *(short *)(e + 0x10),
                                 (unsigned int)(*(int *)(e + 0x38) - (int)seDef) / sz);
        }
        e += 0x40;
        i--;
    } while (i >= 0);
    __asm__ __volatile__("break");
}

INCLUDE_ASM(Ee2Iop);

INCLUDE_ASM(soundOutputModeGet);

INCLUDE_ASM(soundReverbDepthGet);

INCLUDE_ASM(soundBufAdpcmChAlloc);

INCLUDE_ASM(soundBufAdpcmFree);

INCLUDE_ASM(soundDataAreaSearch);

INCLUDE_ASM(soundDataAreaGet);

INCLUDE_ASM(soundHDDataSet);

INCLUDE_ASM(soundSQDataSet);

INCLUDE_ASM(soundSeDefPlay);

INCLUDE_ASM(soundSeDefPlayWithVolumeRate);

INCLUDE_ASM(soundSeDefVolumeRateGet);

INCLUDE_ASM(soundSeDefVolumeRateSet);

INCLUDE_ASM(soundSeGroupStop);

INCLUDE_ASM(soundSeGroupGet);

INCLUDE_ASM(soundSePlayModeStop);

INCLUDE_ASM(soundReqTickProc);

INCLUDE_ASM(soundVBlank);

INCLUDE_ASM(soundSeKindBuild);
