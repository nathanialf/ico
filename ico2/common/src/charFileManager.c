#include "common.h"
#include "charFileName.h"
#include "debug.h"
#include "debug_exception.h"
#include "cdvd.h"
#include "memory.h"
#include "shockdriver.h"
#include "adpcm_init.h"
#include "s_init.h"
#include "camera-ico2.h"
#include "camera-set-manager.h"
#include "Basic.h"
#include "Light.h"
#include "StageAnimation.h"
#include "motionFileManager.h"
#include "particleEffect.h"
#include "tableSin.h"

extern void debug_assert(char *file, int line);
extern void __assert(char *file, int line, char *expr);

typedef struct {
    char _0[0x20];
    int unk_20; /* 0x20 */
} PObj;

typedef struct {
    char _0[0x44];
    short unk_44; /* 0x44 */
    char _46[0x6];
    float *unk_4C; /* 0x4C */
} Bone;            /* 0x50 */

typedef struct {
    char _0[0x8];
    int count; /* 0x08 */
    char _C[0x4];
    int unk_10; /* 0x10 */
    int unk_14; /* 0x14 */
    int unk_18; /* 0x18 */
    int unk_1C; /* 0x1C */
    int unk_20; /* 0x20 */
} Coll;

typedef struct {
    PObj *pObj;    /* 0x00 */
    PObj *pShadow; /* 0x04 */
    char *pSkel;   /* 0x08 */
    int skelSum;   /* 0x0C */
    Coll *pColl;   /* 0x10 */
    int state;     /* 0x14 */
} CharFile;

extern CharFile D_006FAD00[MAX_CHARS];

/* the TU's whole .data run, VMA 0x4D9C10..0x4D9C28 (0x18, = MAIN.MAP
   charFileManager.o .data 0x18): the empty entry both initialisers copy over
   every slot of the table. */
static CharFile charFileEmpty = {0, 0, 0, 0, 0, 1};

extern int D_0063AD00;

#include "charFileManager.h"
#include <stdio.h>

/* kept local: the prototype names PObj, a record only this TU defines, so it
   cannot travel to the header until that record has a home of its own. */
PObj *GetPObjAddress(int a0);

inline PObj *GetPObjAddress(int a0)
{
    return D_006FAD00[a0].pObj;
}

void InitCharFileManager(void)
{
    int i;

    D_0063AD00 = 0;
    for (i = 0; i < MAX_CHARS; i++) {
        D_006FAD00[i] = charFileEmpty;
    }
    InitPluralCameraSet();
    InitCameraSetManager();
}

void ResetCharFileManager(void)
{
    int i;

    D_0063AD00 = 0;
    for (i = 0; i < MAX_CHARS; i++) {
        if (D_006FAD00[i].state == 1) {
            D_006FAD00[i] = charFileEmpty;
        }
    }
    InitPluralCameraSet();
    InitCameraSetManager();
}

extern int D_0028F4C0[];
extern void *D_0063A44C;
extern char D_0063AD08[];
extern char D_0063AD10[];
extern PObj *InitPObj(void *buf, int a1, int id);

/* "Illegal Model ID number: %d (\"%s\")\n" / "ReadModelFile:Already loaded. (id:%d)%s\n" / "ReadModelFile:loaded::(id:%d)%s(addr:%p/size:%d)\n" / sprintf above belong to ReadModelFile. */
void ReadModelFile(void *h, int a1, int size, int id, int a4, int a5, int part)
{
    char buf[0x100];
    char *p;

    D_0028F4C0[8]++;
    if (size == 0) {
        return;
    }

    if (id >= MAX_CHARS) {
        sprintf(buf, "Illegal Model ID number: %d (\"%s\")\n", id, a1);
        /* please raise MAX_CHARS in commmon/include/charFileName.h */
        debug_StdPrintfDummy("commmon/include/charFileName.hのMAX_CHARSを増やしてください\n");
        debug_assertMessage(__FILE__, 0x82, buf);
        __assert(__FILE__, 0x82, D_0063AD08);
    }

    if (D_006FAD00[id].pObj != 0) {
        debug_StdPrintfDummy("ReadModelFile:Already loaded. (id:%d)%s\n", id, a1);
        iosCdvdHandlerRead(h, 0, size);
        return;
    }

    if (part == 0) {
        malloc_SetPartition(0);
    } else {
        malloc_SetPartition(1);
    }

    D_006FAD00[id].state = part;
    p = iosMallocDebug(D_0063A44C, size, __FILE__, 0x91);
    iosCdvdHandlerRead(h, p, size);
    debug_StdPrintfDummy("ReadModelFile:loaded::(id:%d)%s(addr:%p/size:%d)\n", id, a1, p, size);
    D_006FAD00[id].pObj = InitPObj(p, a1, id);
    D_006FAD00[id].pObj->unk_20 = D_0063AD00++;
    iosFree(p);
}

extern int D_0028F4C0[];
extern void *D_0063A44C;
extern char D_0063AD10[];
extern PObj *InitPObj(void *buf, int a1, int id);

void ReadVolumeModelFile(void *h, int a1, int size, int id, int a4, int a5, int a6)
{
    char *buf;

    D_0028F4C0[8]++;
    if (size == 0) {
        return;
    }
    if (a6 == 0) {
        malloc_SetPartition(0);
    } else {
        malloc_SetPartition(1);
    }
    buf = iosMallocDebug(D_0063A44C, size, __FILE__, 190);
    if (id >= MAX_CHARS) {
        debug_StdPrintfDummy("Illegal Volume ID number. %d\n", id);
        debug_StdPrintfDummy("commmon/include/charFileName.hのMAX_CHARSを増やしてください\n");
        debug_assert(__FILE__, 195);
        __assert(__FILE__, 195, D_0063AD10);
    }
    if (D_006FAD00[id].pObj != 0) {
        debug_StdPrintfDummy("ReadVolumeModelFile:Already loaded. (id:%d)%s\n", id, a1);
        iosCdvdHandlerRead(h, 0, size);
        return;
    }
    iosCdvdHandlerRead(h, buf, size);
    debug_StdPrintfDummy("ReadVolumeModelFile:loaded::(id:%d)%s(addr:%p/size:%d)\n", id, a1, buf,
                         size);
    D_006FAD00[id].pObj = InitPObj(buf, a1, id);
    D_006FAD00[id].pObj->unk_20 = D_0063AD00++;
    iosFree(buf);
}

extern PObj *AllocPObj(void *buf, int a1, int id);
extern void shadow_MakeObjectData(PObj *p);

void ReadShadowModelFile(void *h, int a1, int size, int id, int a4, int a5, int a6)
{
    char *buf;

    D_0028F4C0[8]++;
    if (size == 0) {
        return;
    }
    if (a6 == 0) {
        malloc_SetPartition(0);
    } else {
        malloc_SetPartition(1);
    }
    if (id >= MAX_CHARS) {
        debug_StdPrintfDummy("Illegal Shadow ID number. %d\n", id);
        debug_StdPrintfDummy("commmon/include/charFileName.hのMAX_CHARSを増やしてください\n");
        debug_assert(__FILE__, 235);
        __assert(__FILE__, 235, D_0063AD10);
    }
    buf = iosMallocDebug(D_0063A44C, size, __FILE__, 239);
    if (D_006FAD00[id].pShadow != 0) {
        debug_StdPrintfDummy("ReadShadowModelFile:Already loaded. (id:%d)%s\n", id, a1);
        iosCdvdHandlerRead(h, 0, size);
        return;
    }
    iosCdvdHandlerRead(h, buf, size);
    debug_StdPrintfDummy("ReadShadowModelFile:loaded::(id:%d)%s(addr:%p/size:%d)\n", id, a1, buf,
                         size);
    D_006FAD00[id].pShadow = AllocPObj(buf, a1, id);
    D_006FAD00[id].pShadow->unk_20 = D_0063AD00++;
    shadow_MakeObjectData(D_006FAD00[id].pShadow);
    iosFree(buf);
}

typedef struct {
    char _0[0x30];
    int unk_30; /* 0x30 */
} TexRec;       /* 0x34 */

extern TexRec D_00535168[];
extern int NonLinearCameraMove;
/* kept local: this TU's uses of tex_InitTexture do not fit the prototype in Texture.h */
extern int tex_InitTexture(int id, void *buf);
extern int D_0028F4C0[];
extern void *D_0063A44C;

void ReadTextureFile(void *h, int a1, int size, int a3, int a4, int a5, int a6)
{
    int rv = 0;
    char *buf;
    int flag = 0;

    D_0028F4C0[8]++;
    if (a6 == 0) {
        malloc_SetPartition(0);
    } else {
        malloc_SetPartition(1);
    }
    buf = iosMallocDebug(D_0063A44C, size, __FILE__, 276);
    if (size == 0) {
        debug_StdPrintfDummy("ReadTextureFile:texture size is zero.%s\n", a1);
        iosCdvdHandlerRead(h, 0, 0);
        return;
    }
    iosCdvdHandlerRead(h, buf, size);
    if (a4 == 55 && a6 == 1 && D_00535168[a3].unk_30 != 0) {
        if (D_00535168[a3].unk_30 != NonLinearCameraMove) {
            flag = a6;
        }
    }
    if (flag == 0) {
        rv = tex_InitTexture(a1, buf);
    }
    debug_StdPrintfDummy("ReadTextureFile:loaded::(%d)%s(addr:%p/size:%d)\n", rv, a1, buf, size);
    iosFree(buf);
}

typedef struct {
    char name[0x8C];
} SkelEnt; /* 0x8C */

extern SkelEnt D_004FBA80[];
extern char D_0063AD18[];
extern int strcmp(const char *a, const char *b);

/* sugipon/include/sugiCommon.h: byte checksum helper, inlined at its call site */
static inline int SumBytes(unsigned char *p, int n)
{
    int sum = 0;
    int i;

    for (i = 0; i < n; i++) {
        sum += *p++;
    }
    return sum;
}

void ReadSkeltonFile(void *h, char *name, int size, int a3, int a4, int a5, int a6)
{
    char *p = 0;
    int sum = 0;
    int i;

    D_0028F4C0[8]++;
    if (size == 0) {
        return;
    }
    if (a6 == 0) {
        malloc_SetPartition(0);
    } else {
        malloc_SetPartition(1);
    }
    for (i = 0; i < MAX_CHARS; i++) {
        if (D_004FBA80[i].name != 0 && strcmp(D_004FBA80[i].name, name) == 0) {
            if (p == 0) {
                if (D_006FAD00[i].pSkel != 0) {
                    debug_StdPrintfDummy("ReadSkeltonFile:Already loaded. %s\n", name);
                    iosCdvdHandlerRead(h, 0, size);
                    p = D_006FAD00[i].pSkel;
                    sum = D_006FAD00[i].skelSum;
                } else {
                    int j;

                    p = mallocseki(size);
                    j = 0;
                    iosCdvdHandlerRead(h, p, size);
                    debug_StdPrintfDummy("ReadSkeltonFile:loaded::%s  (size:%d)\n", name, size);
                    while (*(int *)(p + j * 64) != -1) {
                        j++;
                    }
                    D_006FAD00[i].pSkel = p;
                    sum = SumBytes((unsigned char *)p, j * 64);
                    D_006FAD00[i].skelSum = sum;
                }
            } else {
                D_006FAD00[i].pSkel = p;
                D_006FAD00[i].skelSum = sum;
            }
        }
    }
    if (p == 0) {
        debug_StdPrintfDummy("ReadSkeltonFile:Skelton file is not applied. %s\n", name);
        debug_assert(__FILE__, 362);
        __assert(__FILE__, 362, D_0063AD18);
    }
}

typedef struct {
    char name[0x8C];
} CollEnt; /* 0x8C */

extern CollEnt D_004FBAB0[];

void ReadCollisionFile(void *h, char *name, int size, int a3, int a4, int a5, int a6)
{
    int i;
    int j;
    int k;
    Coll *p;
    float *q;

    D_0028F4C0[8]++;
    if (size == 0) {
        return;
    }
    if (a6 == 0) {
        malloc_SetPartition(0);
    } else {
        malloc_SetPartition(1);
    }
    for (i = 0; i < MAX_CHARS; i++) {
        if (strcmp(D_004FBAB0[i].name, name) == 0) {
            if (D_006FAD00[i].pColl != 0) {
                debug_StdPrintfDummy("ReadCollisionFile:Already loaded. %s\n", name);
                iosCdvdHandlerRead(h, 0, size);
            } else {
                debug_StdPrintfDummy("collision size:%d\n", size);
                D_006FAD00[i].pColl = (Coll *)mallocseki(size);
                iosCdvdHandlerRead(h, D_006FAD00[i].pColl, size);
                debug_StdPrintfDummy("ReadCollisionFile:loaded::%s  (size:%d)\n", name, size);
                p = D_006FAD00[i].pColl;
                p->unk_10 = (int)p + p->unk_10;
                p->unk_14 = (int)p + p->unk_14;
                p->unk_18 = (int)p + p->unk_18;
                p->unk_1C = (int)p + p->unk_1C;
                p->unk_20 = (int)p + p->unk_20;
                debug_StdPrintfDummy("ch      :%p\n", p);
                debug_StdPrintfDummy("ch->wcl :%p\n", p->unk_10);
                debug_StdPrintfDummy("ch->fcl :%p\n", p->unk_14);
                debug_StdPrintfDummy("ch->wblk:%p\n", p->unk_18);
                debug_StdPrintfDummy("ch->fblk:%p\n", p->unk_1C);
                debug_StdPrintfDummy("ch->ofs :%p\n", p->unk_20);
                for (j = 0; j < 32; j++) {
                    for (k = 0; k < 32; k++) {
                        if (((int *)p->unk_18)[j * 32 + k] != 0) {
                            debug_StdPrintfDummy("w %2d %2d :%p\n", j, k,
                                                 ((int *)p->unk_18)[j * 32 + k]);
                            ((int *)p->unk_18)[j * 32 + k] =
                                (int)p + ((int *)p->unk_18)[j * 32 + k];
                        }
                        if (((int *)p->unk_1C)[j * 32 + k] != 0) {
                            debug_StdPrintfDummy("f %2d %2d :%p\n", j, k,
                                                 ((int *)p->unk_1C)[j * 32 + k]);
                            ((int *)p->unk_1C)[j * 32 + k] =
                                (int)p + ((int *)p->unk_1C)[j * 32 + k];
                        }
                    }
                }
                q = (float *)mallocseki(p->count * 8);
                for (j = 0; j < p->count; j++) {
                    ((Bone *)p->unk_10)[j].unk_4C = q + j * 2;
                    ((Bone *)p->unk_10)[j].unk_4C[0] = GetTableSin(((Bone *)p->unk_10)[j].unk_44);
                    ((Bone *)p->unk_10)[j].unk_4C[1] = GetTableCos(((Bone *)p->unk_10)[j].unk_44);
                }
            }
            return;
        }
    }
    debug_StdPrintfDummy("ReadCollisionFile:Collision file is not applied. %s\n", name);
    debug_assert(__FILE__, 466);
    __assert(__FILE__, 466, D_0063AD18);
}

extern char D_0063AD10[];

void ReadStageAnimationFile(void *h, int a1, int size, int a3, int a4, int a5, int a6)
{
    char *buf;

    D_0028F4C0[8]++;
    if (size == 0) {
        return;
    }
    if (a6 == 0) {
        malloc_SetPartition(0);
        debug_assert(__FILE__, 487);
        __assert(__FILE__, 487, D_0063AD10);
    } else {
        malloc_SetPartition(1);
    }
    buf = mallocseki(size);
    iosCdvdHandlerRead(h, buf, size);
    debug_StdPrintfDummy("ReadStageAnimationFile:loaded::[%d]%s (size:%d)\n", a3, a1, size);
    stage_ApplyData(a1, buf);
}

typedef struct {
    char _0[0x134];
    int unk_134; /* 0x134 */
    char _138[0x5C];
} MotEnt; /* 0x194 */

extern MotEnt D_0055FE58[];
extern char *D_004EB758[];
extern void *D_0063A440;
extern void *D_0063A444;
extern void *D_0063A448;

void ReadMotionFile(void *h, int a1, int size, int id, int a4, int a5, int a6)
{
    D_0028F4C0[8]++;
    if (size == 0) {
        return;
    }
    switch (D_0055FE58[id].unk_134) {
    case 0:
        D_004EB758[id] = iosMallocDebug(D_0063A444, size, __FILE__, 515);
        break;
    case 4:
        D_004EB758[id] = iosMallocDebug(D_0063A440, size, __FILE__, 518);
        if (D_004EB758[id] == 0) {
            /* not enough memory in the dynamic motion area */
            debug_StdPrintfDummy("ダイナミックモーション領域のメモリが足りません。\n");
            debug_assertMessage(__FILE__, 521, "LACK OF DYNAMIC MOTION MEMORY.\n");
            __assert(__FILE__, 521, D_0063AD08);
        }
        break;
    default:
        D_004EB758[id] = iosMallocDebug(D_0063A448, size, __FILE__, 526);
        if (D_004EB758[id] == 0) {
            /* not enough memory in the motion swap area */
            debug_StdPrintfDummy("モーションスワップ領域のメモリが足りません。\n");
            debug_assertMessage(__FILE__, 529, "LACK OF SWAP MOTION MEMORY.\n");
            __assert(__FILE__, 529, D_0063AD08);
        }
        break;
    }
    iosCdvdHandlerRead(h, D_004EB758[id], size);
    InitMotionFile(D_004EB758[id], a1);
    AddMotionMemorySize(size, a6);
    debug_StdPrintfDummy("ReadMotionFile:[%d]%s (size:%d): \033[33m%1.2fMB\033[m\n", id, a1, size,
                         (float)GetMotionMemorySize(a6) / 1024.0f / 1024.0f);
}

extern void *D_0063A438;
extern int D_0028F4C0[];

void ReadParticleEffectFile(void *h, int a1, int size, int a3)
{
    char *buf = iosMallocDebug(D_0063A438, size, __FILE__, 0x228);
    D_0028F4C0[8]++;
    iosCdvdHandlerRead(h, buf, size);
    SetParticleEffectPackage(a3, buf, size);
    iosFree(buf);
}

typedef struct {
    char _0[0x60];
    unsigned int loaded : 1; /* 0x60 bit 0 */
} SeRec;                     /* 0x64 */

extern SeRec D_005EBBE8[];
extern int D_0063A684;

void ReadSoundBdFile(void *h, int a1, int size, int a3, int kind, int a5, int a6)
{
    char *buf;

    D_0028F4C0[8]++;
    if (size == 0) {
        return;
    }
    buf = iosMallocDebug(D_0063A44C, size, __FILE__, 578);
    iosCdvdHandlerRead(h, buf, size);
    switch (kind) {
    case 11: {
        int ok = 1;

        if (D_005EBBE8[a3].loaded == 1) {
            a6 = 2;
            if (soundSeSemiCommonLoadChk() == 1) {
                ok = 0;
            }
        }
        if (ok != 0) {
            soundBDDataSet(buf, a3, 11, 0, a6, size);
        }
    } break;
    case 10:
        if (D_0063A684 == 0) {
            soundBDDataSet(buf, a3, 10, 1, a6, size);
        }
        break;
    default:
        debug_assert(__FILE__, 606);
        __assert(__FILE__, 606, D_0063AD10);
    }
    iosFree(buf);
    debug_StdPrintfDummy("ReadSoundBdFile:loaded::[%d]%s  (size:%d)\n", a3, a1, size);
}

typedef struct {
    int mode;
    int bank;
} HdInfo;

extern char *D_0063AD20;
extern void *D_0063A45C;
extern void *D_0063A444;
extern void *D_0063A458;

void ReadSoundHdFile(void *h, int a1, int size, int a3, int kind, int a5, int a6)
{
    /* same bank/mode pair the switch fills in and soundHDDataSet reads back:
       ROM keeps both words memory-resident and reloads mode at the call. */
    volatile HdInfo info;
    char *buf;

    D_0028F4C0[8]++;
    if (size == 0) {
        return;
    }
    switch (kind) {
    case 11:
        info.mode = 0;
        info.bank = 0;
        break;
    case 10:
        info.mode = 1;
        info.bank = D_0063A684;
        break;
    default:
        debug_assert(__FILE__, 642);
        __assert(__FILE__, 642, D_0063AD10);
    }
    if (info.bank == 0) {
        if (D_005EBBE8[a3].loaded != 1) {
            if (a6 == 0) {
                buf = iosMallocDebug(D_0063A444, size, __FILE__, 650);
            } else {
                buf = iosMallocDebug(D_0063A458, size, __FILE__, 652);
            }
        } else {
            a6 = 2;
            if (soundSeSemiCommonLoadChk() == 1) {
                buf = 0;
            } else {
                if (D_0063AD20 != 0) {
                    iosFree(D_0063AD20);
                }
                D_0063AD20 = iosMallocDebug(D_0063A45C, size, __FILE__, 663);
                buf = D_0063AD20;
            }
        }
    } else {
        buf = 0;
    }
    iosCdvdHandlerRead(h, buf, size);
    if (buf != 0) {
        soundHDDataSet(buf, a3, kind, info.mode, a6);
    }
    debug_StdPrintfDummy("ReadSoundHdFile:loaded::[%d]%s  (size:%d)\n", a3, a1, size);
}

extern char *ShockVoiceSetCommon;
extern char *ShockVoiceSetStage;
extern void *D_0063A460;

typedef struct {
    int mode;
    int bank;
} SqInfo;

/* ReadSoundSqFile and ReadSoundAdpcmFile sit here, at their census source
   lines 695 and 743, between ReadSoundHdFile and ReadShockFile.  They are
   plain `inline`, so gcc emits their bodies at the end of the object, where
   the ROM has them, while their string constants stay at this point of the
   .rodata run. */
extern void *D_0063A444;
extern void *D_0063A458;
extern int D_0063A684;
extern int D_0028F4C0[];

inline void ReadSoundSqFile(void *h, int a1, int size, int a3, int kind, int a5, int a6)
{
    /* the sound bank/mode pair the switch fills in and soundSQDataSet reads back:
       ROM keeps both words memory-resident and reloads mode at the call. */
    volatile SqInfo info;
    char *buf;

    D_0028F4C0[8]++;
    if (size == 0) {
        return;
    }
    switch (kind) {
    case 11:
        info.mode = 0;
        info.bank = 0;
        break;
    case 10:
        info.mode = 1;
        info.bank = D_0063A684;
        break;
    default:
        debug_assert(__FILE__, 709);
        __assert(__FILE__, 709, D_0063AD10);
    }
    if (info.bank == 0) {
        if (a6 == 0) {
            buf = iosMallocDebug(D_0063A444, size, __FILE__, 715);
        } else {
            buf = iosMallocDebug(D_0063A458, size, __FILE__, 717);
        }
    } else {
        buf = 0;
    }
    iosCdvdHandlerRead(h, buf, size);
    if (buf != 0) {
        soundSQDataSet(buf, a3, kind, info.mode, a6);
    }
    debug_StdPrintfDummy("ReadSoundSqFile:loaded::[%d]%s  (size:%d)\n", a3, a1, size);
}

inline void ReadSoundAdpcmFile(void *h, int a1, int size, int a3, int a4, int a5, int a6)
{
    int key;
    int hi;
    char *p;
    char *q;

    D_0028F4C0[8]++;
    if (size > 0x5C000)
        size = 0x5C000;
    hi = a4 << 16;
    key = (a3 & 0xFFFF) | hi;
    if (soundDataAreaSearch(&key) == 0) {
        p = iosMallocDebug(D_0063A444, size, __FILE__, 757);
        iosCdvdHandlerRead(h, p, size);
        debug_StdPrintfDummy("ReadAdpcmFile:loaded::[%d]%s  (size:%d)\n", a3, a1, size);
        q = adpcmDataSet(p, a3, a4, a6, size, AdpcmIopBuffAlloc(), 0);
        iosFree(p);
        AdpcmPlay(*(int *)(q + 0x2C));
    } else {
        iosCdvdHandlerRead(h, 0, size);
    }
}

void ReadShockFile(void *h, int a1, int size, int a3, int a4, int a5, int a6)
{
    char *p;

    D_0028F4C0[8]++;
    if (a6 == 0) {
        malloc_SetPartition(0);
        if (size == 0) {
            p = 0;
        } else {
            p = iosMallocDebug(D_0063A460, size + 16, __FILE__, 788);
            iosCdvdHandlerRead(h, p + 16, size);
            Init_ShockVoiceSet(p, p + 16);
        }
        ShockVoiceSetCommon = p;
    } else {
        malloc_SetPartition(1);
        if (size == 0) {
            p = 0;
        } else {
            p = mallocseki(size + 16);
            iosCdvdHandlerRead(h, p + 16, size);
            Init_ShockVoiceSet(p, p + 16);
        }
        ShockVoiceSetStage = p;
    }
    debug_StdPrintfDummy("ReadShockData:loaded::[%d]%s  (size:%d)\n", a3, a1, size);
}

extern void *D_0063A450;

void ReadCamerasetFile(void *h, int a1, int size, int a3)
{
    char *buf;

    buf = iosMallocDebug(D_0063A450, size, __FILE__, 820);
    if (buf == 0) {
        /* not enough memory to load the camera data */
        debug_StdPrintfDummy("カメラデータをロードするためのメモリが足りません\n");
        debug_assert(__FILE__, 825);
        __assert(__FILE__, 825, D_0063AD10);
    }
    D_0028F4C0[8]++;
    iosCdvdHandlerRead(h, buf, size);
    AddPluralCameraSet(a3, buf);
    iosFree(buf);
}

extern int D_0028F4C0[];

void ReadEndCheckFile(void *h, int a1, int size)
{
    char *buf = iosMallocDebug(D_0063A450, size, __FILE__, 0x356);
    D_0028F4C0[8]++;
    iosCdvdHandlerRead(h, buf, size);
    iosFree(buf);
}

extern char D_0028F720[];
extern void *memcpy(void *dst, const void *src, int n);
/* kept local: this TU's uses of tex_RemakeRegistersSampleMin do not fit the prototype in Texture.h */
extern void tex_RemakeRegistersSampleMin(int a);
extern void *D_0063A44C;

void ReadStageSettingFile(void *h, int a1, int size)
{
    char *buf;

    D_0028F4C0[8]++;
    buf = iosMallocDebug(D_0063A44C, size, __FILE__, 905);
    iosCdvdHandlerRead(h, buf, size);
    memcpy(D_0028F720, buf, size);
    light_AddLight(0, 0, 0);
    tex_RemakeRegistersSampleMin(0);
}

typedef struct {
    char _0[0x70];
    int unk_70; /* 0x70 */
    char _74[0x10];
    int unk_84;   /* 0x84 */
    int unk_88;   /* 0x88 */
    char *unk_8C; /* 0x8C */
    char _90[0x7A4];
    int unk_834; /* 0x834 */
    char _838[0x1C];
    PObj *unk_854; /* 0x854 */
    PObj *unk_858; /* 0x858 */
} CsvChar;

void CSVSYSTEM_ReadCharFiles(CsvChar *rec, int id)
{
    int n = 0;
    int sum;

    if (id >= MAX_CHARS) {
        debug_StdPrintfDummy("Illegal Char ID Number. %d\n");
        debug_StdPrintfDummy("commmon/include/charFileName.hのMAX_CHARSを増やしてください\n");
        debug_assert(__FILE__, 927);
        __assert(__FILE__, 927, D_0063AD10);
    }
    rec->unk_84 = id;
    debug_StdPrintfDummy("Link polygon & skelton & collision -> DObj. %d\n", id);
    rec->unk_854 = D_006FAD00[id].pObj;
    debug_StdPrintfDummy("polygon %p.\n", rec->unk_854);
    if (rec->unk_854 != 0) {
        debug_StdPrintfDummy("object name %s.\n", rec->unk_854);
    }
    rec->unk_858 = D_006FAD00[id].pShadow;
    debug_StdPrintfDummy("shadow %p.\n", rec->unk_858);
    if (rec->unk_858 != 0) {
        debug_StdPrintfDummy("shadow object name %s.\n", rec->unk_858);
    }
    rec->unk_8C = D_006FAD00[id].pSkel;
    debug_StdPrintfDummy("skelton %p.\n", rec->unk_8C);
    rec->unk_70 = (int)D_006FAD00[id].pColl;
    debug_StdPrintfDummy("collision %p.\n", rec->unk_70);
    if (rec->unk_8C != 0) {
        while (*(int *)(rec->unk_8C + n * 64) != -1) {
            n++;
        }
        rec->unk_88 = n;
        rec->unk_834 = *(int *)(rec->unk_8C + n * 64 + 4);
        if (rec->unk_834 < 0) {
            /* the shape data count information is old */
            debug_StdPrintfDummy("\033[36m シェイプデータの数情報が古いです。%d\033[m\n",
                                 rec->unk_834);
            rec->unk_834 = 0;
        }
        sum = SumBytes((unsigned char *)rec->unk_8C, rec->unk_88 * 64);
        if (sum == D_006FAD00[id].skelSum) {
            /* the skelton of "%s" is sound */
            debug_StdPrintfDummy("\033[36m\"%s\"のスケルトンは正常(%x)\033[m\n", rec->unk_854, sum);
        } else {
            debug_StdPrintfDummy(
                "\033[33m --- W - A - R - N - I - N - G ------------------------\033[m\n");
            /* the skelton of "%s" is damaged */
            debug_StdPrintfDummy("\033[33m\"%s\"のスケルトンが破損しています(%x(NOW)!=%x)\033[m\n",
                                 rec->unk_854, sum, D_006FAD00[id].skelSum);
            /* it was broken between the load and the stage placement */
            debug_StdPrintfDummy("\033[33mロード直後からステージ配置の間に壊されました\033[m\n");
            debug_StdPrintfDummy(
                "\033[33m ------------------------------------------------------\033[m\n");
        }
    } else {
        rec->unk_88 = 0;
        rec->unk_834 = 0;
    }
}
