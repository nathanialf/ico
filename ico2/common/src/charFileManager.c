#include "charFileName.h"
#include "debug.h"
#include "debug_exception.h"
#include "cdvd.h"
#include "memory.h"
#include "shockdriver.h"
#include "adpcm_init.h"
#include "s_init.h"
#include "soundManager.h"
#include "camera-ico2.h"
#include "camera-set-manager.h"
#include "Basic.h"
#include "Light.h"
#include "StageAnimation.h"
#include "motionFileManager.h"
#include "particleEffect.h"
#include "tableSin.h"
#include "DisplayP2O.h"
#include "Shadow.h"
#include "Texture.h"
#include <string.h>
#include "ios.h"
#include <assert.h>

typedef struct { /* field names derived */
    char pad0[68];
    short angle; /* 0x44, the wall's angle, its sine and cosine kept at 0x4C */
    char pad46[6];
    float *sinCos; /* 0x4C */
} Bone; /* 0x50 */ /* derived name */

typedef struct { /* field names derived */
    char pad0[8];
    int count; /* 0x08 */
    char padC[4];
    int wcl;  /* 0x10 */
    int fcl;  /* 0x14 */
    int wblk; /* 0x18 */
    int fblk; /* 0x1C */
    int ofs;  /* 0x20 */
} Coll;       /* derived name */

typedef struct {        /* field names derived */
    PObjModel *pObj;    /* 0x00 */
    PObjModel *pShadow; /* 0x04 */
    SkelNode *pSkel;    /* 0x08 */
    int skelSum;        /* 0x0C */
    Coll *pColl;        /* 0x10 */
    int state;          /* 0x14 */
} CharFile;             /* derived name */

/* .bss: the character file table, MAX_CHARS entries of 0x18 bytes */
static CharFile charFiles[MAX_CHARS]; /* derived name */

/* .data: the empty entry both initialisers copy over
   every slot of the table. */
static CharFile charFileEmpty = {0, 0, 0, 0, 0, 1}; /* derived name */

/* .sdata: the serial the loaders stamp into each object they build, and the
   semi-common sound header's buffer (defined below). */
static int objSerial = 0; /* derived name */

#include "charFileManager.h"
#include <stdio.h>
#include "main.h"
#include "include_asm.h"

/* declared here until enemy.c's call stores the pointer without its int
   view; then charFileManager.h declares it */
PObjModel *GetPObjAddress(int id);

inline PObjModel *GetPObjAddress(int id)
{
    return charFiles[id].pObj;
}

void InitCharFileManager(void)
{
    int i;

    objSerial = 0;
    for (i = 0; i < MAX_CHARS; i++) {
        charFiles[i] = charFileEmpty;
    }
    InitPluralCameraSet();
    InitCameraSetManager();
}

void ResetCharFileManager(void)
{
    int i;

    objSerial = 0;
    for (i = 0; i < MAX_CHARS; i++) {
        if (charFiles[i].state == 1) {
            charFiles[i] = charFileEmpty;
        }
    }
    InitPluralCameraSet();
    InitCameraSetManager();
}

/* PObj.c has no header; the definition is (int, int, int) */
extern PObjModel *InitPObj(void *buf, int name, int id);

/* "Illegal Model ID number: %d (\"%s\")\n" / "ReadModelFile:Already loaded. (id:%d)%s\n" / "ReadModelFile:loaded::(id:%d)%s(addr:%p/size:%d)\n" / sprintf above belong to ReadModelFile. */
INCLUDE_ASM(ReadModelFile);

INCLUDE_ASM(ReadVolumeModelFile);

/* PObj.c has no header; the definition is (ObjHdr *, char *, int) */
extern PObjModel *AllocPObj(void *buf, int name, int id);

INCLUDE_ASM(ReadShadowModelFile);

INCLUDE_ASM(ReadTextureFile);

/* sugipon/include/sugiCommon.h: byte checksum helper, inlined at its call site */
static inline int SumBytes(unsigned char *p, int n) /* derived name */
{
    int sum = 0;
    int i;

    for (i = 0; i < n; i++) {
        sum += *p++;
    }
    return sum;
}

void ReadSkeltonFile(void *h, char *name, int size, int id, int kind, int word08, int seg)
{
    SkelNode *p = 0;
    int sum = 0;
    int i;

    systemStatus[8]++;
    if (size == 0) {
        return;
    }
    if (seg == 0) {
        malloc_SetPartition(0);
    } else {
        malloc_SetPartition(1);
    }
    for (i = 0; i < MAX_CHARS; i++) {
        if (modelData[i].path != 0 && strcmp(modelData[i].path, name) == 0) {
            if (p == 0) {
                if (charFiles[i].pSkel != 0) {
                    debug_StdPrintfDummy("ReadSkeltonFile:Already loaded. %s\n", name);
                    iosCdvdHandlerRead(h, 0, size);
                    p = charFiles[i].pSkel;
                    sum = charFiles[i].skelSum;
                } else {
                    int j;

                    p = mallocseki(size);
                    j = 0;
                    iosCdvdHandlerRead(h, p, size);
                    debug_StdPrintfDummy("ReadSkeltonFile:loaded::%s  (size:%d)\n", name, size);
                    while (p[j].mirror != -1) {
                        j++;
                    }
                    charFiles[i].pSkel = p;
                    sum = SumBytes((unsigned char *)p, j * 64);
                    charFiles[i].skelSum = sum;
                }
            } else {
                charFiles[i].pSkel = p;
                charFiles[i].skelSum = sum;
            }
        }
    }
    if (p == 0) {
        debug_StdPrintfDummy("ReadSkeltonFile:Skelton file is not applied. %s\n", name);
        debug_assert(__FILE__, 349);
        __assert(__FILE__, 349, "FALSE");
    }
}

void ReadCollisionFile(void *h, char *name, int size, int id, int kind, int word08, int seg)
{
    int i;
    int j;
    int k;
    Coll *p;
    float *q;

    systemStatus[8]++;
    if (size == 0) {
        return;
    }
    if (seg == 0) {
        malloc_SetPartition(0);
    } else {
        malloc_SetPartition(1);
    }
    for (i = 0; i < MAX_CHARS; i++) {
        if (strcmp(modelData[i].collPath, name) == 0) {
            if (charFiles[i].pColl != 0) {
                debug_StdPrintfDummy("ReadCollisionFile:Already loaded. %s\n", name);
                iosCdvdHandlerRead(h, 0, size);
            } else {
                debug_StdPrintfDummy("collision size:%d\n", size);
                charFiles[i].pColl = (Coll *)mallocseki(size);
                iosCdvdHandlerRead(h, charFiles[i].pColl, size);
                debug_StdPrintfDummy("ReadCollisionFile:loaded::%s  (size:%d)\n", name, size);
                p = charFiles[i].pColl;
                p->wcl = (int)p + p->wcl;
                p->fcl = (int)p + p->fcl;
                p->wblk = (int)p + p->wblk;
                p->fblk = (int)p + p->fblk;
                p->ofs = (int)p + p->ofs;
                debug_StdPrintfDummy("ch      :%p\n", p);
                debug_StdPrintfDummy("ch->wcl :%p\n", p->wcl);
                debug_StdPrintfDummy("ch->fcl :%p\n", p->fcl);
                debug_StdPrintfDummy("ch->wblk:%p\n", p->wblk);
                debug_StdPrintfDummy("ch->fblk:%p\n", p->fblk);
                debug_StdPrintfDummy("ch->ofs :%p\n", p->ofs);
                for (j = 0; j < 32; j++) {
                    for (k = 0; k < 32; k++) {
                        if (((int *)p->wblk)[j * 32 + k] != 0) {
                            debug_StdPrintfDummy("w %2d %2d :%p\n", j, k,
                                                 ((int *)p->wblk)[j * 32 + k]);
                            ((int *)p->wblk)[j * 32 + k] = (int)p + ((int *)p->wblk)[j * 32 + k];
                        }
                        if (((int *)p->fblk)[j * 32 + k] != 0) {
                            debug_StdPrintfDummy("f %2d %2d :%p\n", j, k,
                                                 ((int *)p->fblk)[j * 32 + k]);
                            ((int *)p->fblk)[j * 32 + k] = (int)p + ((int *)p->fblk)[j * 32 + k];
                        }
                    }
                }
                q = (float *)mallocseki(p->count * 8);
                for (j = 0; j < p->count; j++) {
                    ((Bone *)p->wcl)[j].sinCos = q + j * 2;
                    ((Bone *)p->wcl)[j].sinCos[0] = GetTableSin(((Bone *)p->wcl)[j].angle);
                    ((Bone *)p->wcl)[j].sinCos[1] = GetTableCos(((Bone *)p->wcl)[j].angle);
                }
            }
            return;
        }
    }
    debug_StdPrintfDummy("ReadCollisionFile:Collision file is not applied. %s\n", name);
    debug_assert(__FILE__, 453);
    __assert(__FILE__, 453, "FALSE");
}

void ReadStageAnimationFile(void *h, char *name, int size, int id, int kind, int word08, int seg)
{
    char *buf;

    systemStatus[8]++;
    if (size == 0) {
        return;
    }
    if (seg == 0) {
        malloc_SetPartition(0);
        debug_assert(__FILE__, 474);
        __assert(__FILE__, 474, "0");
    } else {
        malloc_SetPartition(1);
    }
    buf = mallocseki(size);
    iosCdvdHandlerRead(h, buf, size);
    debug_StdPrintfDummy("ReadStageAnimationFile:loaded::[%d]%s (size:%d)\n", id, name, size);
    stage_ApplyData(name, buf);
}

typedef struct { /* field names derived */
    char pad0[308];
    int area; /* 0x134, the motion memory area: 0 static, 4 dynamic, else swap */
    char pad138[92];
} MotEnt; /* 0x194 */ /* derived name */

/* motionOrientManager.h carries MotionDef and declares no motionKind */
extern MotEnt motionKind[];

INCLUDE_ASM(ReadMotionFile);

void ReadParticleEffectFile(void *h, int name, int size, int id)
{
    int *buf = iosMallocDebug(ios_partition_sugipon, size, __FILE__, 539);
    systemStatus[8]++;
    iosCdvdHandlerRead(h, buf, size);
    SetParticleEffectPackage(id, buf, size);
    iosFree(buf);
}

void ReadSoundBdFile(void *h, int name, int size, int id, int kind, int word08, int seg)
{
    char *buf;

    systemStatus[8]++;
    if (size == 0) {
        return;
    }
    buf = iosMallocDebug(ios_partition_seki, size, __FILE__, 565);
    iosCdvdHandlerRead(h, buf, size);
    switch (kind) {
    case 11: {
        int ok = 1;

        if (seFile[id].loaded == 1) {
            seg = 2;
            if (soundSeSemiCommonLoadChk() == 1) {
                ok = 0;
            }
        }
        if (ok != 0) {
            soundBDDataSet(buf, id, 11, 0, seg, size);
        }
    } break;
    case 10:
        if (sndInitBgmCancelFlag == 0) {
            soundBDDataSet(buf, id, 10, 1, seg, size);
        }
        break;
    default:
        debug_assert(__FILE__, 593);
        __assert(__FILE__, 593, "0");
    }
    iosFree(buf);
    debug_StdPrintfDummy("ReadSoundBdFile:loaded::[%d]%s  (size:%d)\n", id, name, size);
}

typedef struct { /* field names derived */
    int mode;
    int bank;
} HdInfo; /* derived name */

/* the semi-common sound bank's header buffer, freed and reallocated on each
   load */
static char *semiCommonHdBuf = 0; /* derived name */

void ReadSoundHdFile(void *h, int name, int size, int id, int kind, int word08, int seg)
{
    /* the sound bank/mode pair the switch fills in and soundHDDataSet reads
       back */
    volatile HdInfo info;
    char *buf;

    systemStatus[8]++;
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
        info.bank = sndInitBgmCancelFlag;
        break;
    default:
        debug_assert(__FILE__, 629);
        __assert(__FILE__, 629, "0");
    }
    if (info.bank == 0) {
        if (seFile[id].loaded != 1) {
            if (seg == 0) {
                buf = iosMallocDebug(ios_partition_smotion, size, __FILE__, 637);
            } else {
                buf = iosMallocDebug(ios_partition_sound, size, __FILE__, 639);
            }
        } else {
            seg = 2;
            if (soundSeSemiCommonLoadChk() == 1) {
                buf = 0;
            } else {
                if (semiCommonHdBuf != 0) {
                    iosFree(semiCommonHdBuf);
                }
                semiCommonHdBuf = iosMallocDebug(ios_partition_sound_semi, size, __FILE__, 650);
                buf = semiCommonHdBuf;
            }
        }
    } else {
        buf = 0;
    }
    iosCdvdHandlerRead(h, buf, size);
    if (buf != 0) {
        soundHDDataSet(buf, id, kind, info.mode, seg);
    }
    debug_StdPrintfDummy("ReadSoundHdFile:loaded::[%d]%s  (size:%d)\n", id, name, size);
}

typedef struct { /* field names derived */
    int mode;
    int bank;
} SqInfo; /* derived name */

/* ReadSoundSqFile and ReadSoundAdpcmFile, between ReadSoundHdFile and
   ReadShockFile; they are plain `inline`, so their out-of-line bodies come
   out at the end of the object. */

void ReadShockFile(void *h, int name, int size, int id, int kind, int word08, int seg)
{
    ShockVoiceFile *p;

    systemStatus[8]++;
    if (seg == 0) {
        malloc_SetPartition(0);
        if (size == 0) {
            p = 0;
        } else {
            p = iosMallocDebug(ios_partition_shock, size + 16, __FILE__, 775);
            iosCdvdHandlerRead(h, p->image, size);
            Init_ShockVoiceSet(&p->set, p->image);
        }
        ShockVoiceSetCommon = &p->set;
    } else {
        malloc_SetPartition(1);
        if (size == 0) {
            p = 0;
        } else {
            p = mallocseki(size + 16);
            iosCdvdHandlerRead(h, p->image, size);
            Init_ShockVoiceSet(&p->set, p->image);
        }
        ShockVoiceSetStage = &p->set;
    }
    debug_StdPrintfDummy("ReadShockData:loaded::[%d]%s  (size:%d)\n", id, name, size);
}

INCLUDE_ASM(ReadCamerasetFile);

void ReadEndCheckFile(void *h, int name, int size)
{
    char *buf = iosMallocDebug(ios_partition_oomori, size, __FILE__, 841);
    systemStatus[8]++;
    iosCdvdHandlerRead(h, buf, size);
    iosFree(buf);
}

void ReadStageSettingFile(void *h, int name, int size)
{
    char *buf;

    systemStatus[8]++;
    buf = iosMallocDebug(ios_partition_seki, size, __FILE__, 892);
    iosCdvdHandlerRead(h, buf, size);
    memcpy(&GlobalStageSetting, buf, size);
    light_AddLight(0, 0, 0);
    tex_RemakeRegistersSampleMin(0);
}

INCLUDE_ASM(CSVSYSTEM_ReadCharFiles);

inline void ReadSoundSqFile(void *h, int name, int size, int id, int kind, int word08, int seg)
{
    /* the sound bank/mode pair the switch fills in and soundSQDataSet reads
       back */
    volatile SqInfo info;
    char *buf;

    systemStatus[8]++;
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
        info.bank = sndInitBgmCancelFlag;
        break;
    default:
        debug_assert(__FILE__, 696);
        __assert(__FILE__, 696, "0");
    }
    if (info.bank == 0) {
        if (seg == 0) {
            buf = iosMallocDebug(ios_partition_smotion, size, __FILE__, 702);
        } else {
            buf = iosMallocDebug(ios_partition_sound, size, __FILE__, 704);
        }
    } else {
        buf = 0;
    }
    iosCdvdHandlerRead(h, buf, size);
    if (buf != 0) {
        soundSQDataSet(buf, id, kind, info.mode, seg);
    }
    debug_StdPrintfDummy("ReadSoundSqFile:loaded::[%d]%s  (size:%d)\n", id, name, size);
}

inline void ReadSoundAdpcmFile(void *h, int name, int size, int id, int kind, int word08, int seg)
{
    int key;
    int hi;
    char *p;
    SqEntry *q;

    systemStatus[8]++;
    if (size > 0x5C000)
        size = 0x5C000;
    hi = kind << 16;
    key = (id & 0xFFFF) | hi;
    if (soundDataAreaSearch(&key) == 0) {
        p = iosMallocDebug(ios_partition_smotion, size, __FILE__, 744);
        iosCdvdHandlerRead(h, p, size);
        debug_StdPrintfDummy("ReadAdpcmFile:loaded::[%d]%s  (size:%d)\n", id, name, size);
        q = adpcmDataSet(p, id, kind, seg, size, AdpcmIopBuffAlloc(), 0);
        iosFree(p);
        AdpcmPlay(q->stream);
    } else {
        iosCdvdHandlerRead(h, 0, size);
    }
}
