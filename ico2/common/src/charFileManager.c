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
    Coll *pColl;        /* 0x0C, ReadCollisionFile's (this build keeps no
                           skeleton checksum before it) */
    int state;          /* 0x10, InitCharFileManager sets it to 1 */
} CharFile;             /* derived name */

/* .bss: the character file table, MAX_CHARS entries of 0x14 bytes */
static CharFile charFiles[MAX_CHARS]; /* derived name */

/* This build keeps no empty-entry template in .data: the object has no
   .data (debug.c's follows the stage manager's directly). */

/* .sdata: the serial the loaders stamp into each object they build, and the
   semi-common sound header's buffer (defined below). */
static int objSerial = 0; /* derived name */

#include "charFileManager.h"
#include <stdio.h>
#include "main.h"

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
        charFiles[i].pObj = 0;
        charFiles[i].pShadow = 0;
        charFiles[i].pSkel = 0;
        charFiles[i].pColl = 0;
        charFiles[i].state = 1;
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
            charFiles[i].pObj = 0;
            charFiles[i].pShadow = 0;
            charFiles[i].pSkel = 0;
            charFiles[i].pColl = 0;
        } else {
            debug_StdPrintfDummy("keep common object [%d]%s %p\n", i, charFiles[i].pObj,
                                 charFiles[i].pObj);
        }
    }
    InitPluralCameraSet();
    InitCameraSetManager();
}

/* PObj.c has no header; this build passes the model's offset as three
   floats */
extern PObjModel *InitPObj(void *buf, int name, float x, float y, float z);

/* "Illegal Model ID number: %d (\"%s\")\n" / "ReadModelFile:Already loaded. (id:%d)%s\n" / "ReadModelFile:loaded::(id:%d)%s(addr:%p/size:%d)\n" / sprintf above belong to ReadModelFile. */
void ReadModelFile(void *h, int name, int size, int id, int kind, int word08, int part)
{
    char buf[1024];
    char *p;

    systemStatus[8]++;
    if (size == 0) {
        return;
    }

    if (id >= MAX_CHARS) {
        sprintf(buf, "Illegal Model ID number: %d (\"%s\")\n", id, name);
        /* please raise MAX_CHARS in commmon/include/charFileName.h */
        debug_StdPrintfDummy("commmon/include/charFileName.hのMAX_CHARSを増やしてください\n");
        debug_assertMessage(__FILE__, 125, buf);
        __assert(__FILE__, 125, "e");
    }

    if (charFiles[id].pObj != 0) {
        debug_StdPrintfDummy("ReadModelFile:Already loaded. (id:%d)%s\n", id, name);
        iosCdvdHandlerRead(h, 0, size);
        return;
    }

    if (part == 0) {
        malloc_SetPartition(0);
    } else {
        malloc_SetPartition(1);
    }

    charFiles[id].state = part;
    p = iosMallocDebug(ios_partition_seki, size, __FILE__, 140);
    iosCdvdHandlerRead(h, p, size);
    debug_StdPrintfDummy("ReadModelFile:loaded::(id:%d)%s(addr:%p/size:%d)\n", id, name, p, size);
    charFiles[id].pObj = InitPObj(p, name, modelData[id].offset[0], modelData[id].offset[1],
                                  modelData[id].offset[2]);
    charFiles[id].pObj->serial = objSerial++;
    iosFree(p);
}

void ReadVolumeModelFile(void *h, int name, int size, int id, int kind, int word08, int seg)
{
    char *buf;

    systemStatus[8]++;
    if (size == 0) {
        return;
    }
    if (seg == 0) {
        malloc_SetPartition(0);
    } else {
        malloc_SetPartition(1);
    }
    buf = iosMallocDebug(ios_partition_seki, size, __FILE__, 169);
    if (id >= MAX_CHARS) {
        debug_StdPrintfDummy("Illegal Volume ID number. %d\n", id);
        debug_StdPrintfDummy("commmon/include/charFileName.hのMAX_CHARSを増やしてください\n");
        debug_assert(__FILE__, 174);
        __assert(__FILE__, 174, "0");
    }
    if (charFiles[id].pObj != 0) {
        debug_StdPrintfDummy("ReadVolumeModelFile:Already loaded. (id:%d)%s\n", id, name);
        iosCdvdHandlerRead(h, 0, size);
        return;
    }
    iosCdvdHandlerRead(h, buf, size);
    debug_StdPrintfDummy("ReadVolumeModelFile:loaded::(id:%d)%s(addr:%p/size:%d)\n", id, name, buf,
                         size);
    charFiles[id].pObj = InitPObj(buf, name, modelData[id].offset[0], modelData[id].offset[1],
                                  modelData[id].offset[2]);
    charFiles[id].pObj->serial = objSerial++;
    iosFree(buf);
}

/* PObj.c has no header; this build's definition takes the buffer and the
   name */
extern PObjModel *AllocPObj(void *buf, int name);

void ReadShadowModelFile(void *h, int name, int size, int id, int kind, int word08, int seg)
{
    char *buf;

    systemStatus[8]++;
    if (size == 0) {
        return;
    }
    if (seg == 0) {
        malloc_SetPartition(0);
    } else {
        malloc_SetPartition(1);
    }
    if (id >= MAX_CHARS) {
        debug_StdPrintfDummy("Illegal Shadow ID number. %d\n", id);
        debug_StdPrintfDummy("commmon/include/charFileName.hのMAX_CHARSを増やしてください\n");
        debug_assert(__FILE__, 215);
        __assert(__FILE__, 215, "0");
    }
    buf = iosMallocDebug(ios_partition_seki, size, __FILE__, 219);
    if (charFiles[id].pShadow != 0) {
        debug_StdPrintfDummy("ReadShadowModelFile:Already loaded. (id:%d)%s\n", id, name);
        iosCdvdHandlerRead(h, 0, size);
        return;
    }
    iosCdvdHandlerRead(h, buf, size);
    debug_StdPrintfDummy("ReadShadowModelFile:loaded::(id:%d)%s(addr:%p/size:%d)\n", id, name, buf,
                         size);
    charFiles[id].pShadow = AllocPObj(buf, name);
    charFiles[id].pShadow->serial = objSerial++;
    shadow_MakeObjectData(charFiles[id].pShadow);
    iosFree(buf);
}

void ReadTextureFile(void *h, char *name, int size, int id, int kind, int word08, int seg)
{
    int rv;
    char *buf;

    systemStatus[8]++;
    if (seg == 0) {
        malloc_SetPartition(0);
    } else {
        malloc_SetPartition(1);
    }
    buf = iosMallocDebug(ios_partition_seki, size, __FILE__, 255);
    if (size == 0) {
        debug_StdPrintfDummy("ReadTextureFile:texture size is zero.%s\n", name);
        iosCdvdHandlerRead(h, 0, 0);
        return;
    }
    iosCdvdHandlerRead(h, buf, size);
    rv = tex_InitTexture(name, buf);
    debug_StdPrintfDummy("ReadTextureFile:loaded::(%d)%s(addr:%p/size:%d)\n", rv, name, buf, size);
    iosFree(buf);
}

void ReadSkeltonFile(void *h, char *name, int size, int id, int kind, int word08, int seg)
{
    SkelNode *p = 0;
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
    if (ModelDataID_NUMBER > MAX_CHARS) {
        debug_StdPrintfDummy("Too Many ModelDataID_NUMBER exists. %d\n", ModelDataID_NUMBER);
    }
    for (i = 0; i < ModelDataID_NUMBER; i++) {
        if (modelData[i].path != 0 && strcmp(modelData[i].path, name) == 0) {
            if (p == 0) {
                if (charFiles[i].pSkel != 0) {
                    debug_StdPrintfDummy("ReadSkeltonFile:Already loaded. %s\n", name);
                    iosCdvdHandlerRead(h, 0, size);
                    p = charFiles[i].pSkel;
                } else {
                    p = mallocseki(size);
                    iosCdvdHandlerRead(h, p, size);
                    charFiles[i].pSkel = p;
                    debug_StdPrintfDummy("ReadSkeltonFile:loaded::%s  (size:%d)\n", name, size);
                }
            } else {
                charFiles[i].pSkel = p;
            }
        }
    }
    if (p == 0) {
        debug_StdPrintfDummy("ReadSkeltonFile:Skelton file is not applied. %s\n", name);
        debug_assert(__FILE__, 320);
        __assert(__FILE__, 320, "FALSE");
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
    for (i = 0; i < ModelDataID_NUMBER; i++) {
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
    debug_assert(__FILE__, 424);
    __assert(__FILE__, 424, "FALSE");
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
        debug_assert(__FILE__, 445);
        __assert(__FILE__, 445, "0");
    } else {
        malloc_SetPartition(1);
    }
    buf = mallocseki(size);
    iosCdvdHandlerRead(h, buf, size);
    debug_StdPrintfDummy("ReadStageAnimationFile:loaded::[%d]%s (size:%d)\n", id, name, size);
    stage_ApplyData(name, buf);
}

typedef struct { /* field names derived */
    char pad0[280];
    int area; /* 0x118, the motion memory area: 0 static, 4 dynamic, else swap */
    char pad11C[104];
} MotEnt; /* 0x184 */ /* derived name */

/* motionOrientManager.h carries MotionDef and declares no motionKind */
extern MotEnt motionKind[];

void ReadMotionFile(void *h, char *name, int size, int id, int kind, int word08, int seg)
{
    systemStatus[8]++;
    if (size == 0) {
        return;
    }
    switch (motionKind[id].area) {
    case 0:
        motionTable[id] = iosMallocDebug(ios_partition_smotion, size, __FILE__, 473);
        break;
    case 4:
        motionTable[id] = iosMallocDebug(ios_partition_dmotion, size, __FILE__, 476);
        if (motionTable[id] == 0) {
            /* not enough memory in the dynamic motion area */
            debug_StdPrintfDummy("ダイナミックモーション領域のメモリが足りません。\n");
            debug_assertMessage(__FILE__, 479, "LACK OF DYNAMIC MOTION MEMORY.\n");
            __assert(__FILE__, 479, "e");
        }
        break;
    default:
        motionTable[id] = iosMallocDebug(ios_partition_s2motion, size, __FILE__, 484);
        if (motionTable[id] == 0) {
            /* not enough memory in the motion swap area */
            debug_StdPrintfDummy("モーションスワップ領域のメモリが足りません。\n");
            debug_assertMessage(__FILE__, 487, "LACK OF SWAP MOTION MEMORY.\n");
            __assert(__FILE__, 487, "e");
        }
        break;
    }
    iosCdvdHandlerRead(h, motionTable[id], size);
    InitMotionFile(motionTable[id], name);
    AddMotionMemorySize(size, seg);
    debug_StdPrintfDummy("ReadMotionFile:[%d]%s (size:%d): \033[33m%1.2fMB\033[m\n", id, name, size,
                         (float)GetMotionMemorySize(seg) / 1024.0f / 1024.0f);
}

void ReadParticleEffectFile(void *h, int name, int size, int id)
{
    int *buf = iosMallocDebug(ios_partition_sugipon, size, __FILE__, 510);
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
    buf = iosMallocDebug(ios_partition_seki, size, __FILE__, 536);
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
            soundBDDataSet((int)buf, id, 11, 0, seg, size);
        }
    } break;
    case 10:
        if (sndInitBgmCancelFlag == 0) {
            soundBDDataSet((int)buf, id, 10, 1, seg, size);
        }
        break;
    default:
        debug_assert(__FILE__, 564);
        __assert(__FILE__, 564, "0");
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
        debug_assert(__FILE__, 600);
        __assert(__FILE__, 600, "0");
    }
    if (info.bank == 0) {
        if (seFile[id].loaded != 1) {
            if (seg == 0) {
                buf = iosMallocDebug(ios_partition_smotion, size, __FILE__, 608);
            } else {
                buf = iosMallocDebug(ios_partition_sound, size, __FILE__, 610);
            }
        } else {
            seg = 2;
            if (soundSeSemiCommonLoadChk() == 1) {
                buf = 0;
            } else {
                if (semiCommonHdBuf != 0) {
                    iosFree(semiCommonHdBuf);
                }
                semiCommonHdBuf = iosMallocDebug(ios_partition_sound_semi, size, __FILE__, 621);
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
        debug_assert(__FILE__, 667);
        __assert(__FILE__, 667, "0");
    }
    if (info.bank == 0) {
        if (seg == 0) {
            buf = iosMallocDebug(ios_partition_smotion, size, __FILE__, 673);
        } else {
            buf = iosMallocDebug(ios_partition_sound, size, __FILE__, 675);
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
        p = iosMallocDebug(ios_partition_smotion, size, __FILE__, 715);
        iosCdvdHandlerRead(h, p, size);
        debug_StdPrintfDummy("ReadAdpcmFile:loaded::[%d]%s  (size:%d)\n", id, name, size);
        q = adpcmDataSet((int)p, id, kind, seg, size, AdpcmIopBuffAlloc(), 0);
        iosFree(p);
        AdpcmPlay(q->stream);
    } else {
        iosCdvdHandlerRead(h, 0, size);
    }
}

void ReadShockFile(void *h, int name, int size, int id, int kind, int word08, int seg)
{
    ShockVoiceFile *p;

    systemStatus[8]++;
    if (seg == 0) {
        malloc_SetPartition(0);
        if (size == 0) {
            p = 0;
        } else {
            p = iosMallocDebug(ios_partition_shock, size + 16, __FILE__, 746);
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

void ReadCamerasetFile(void *h, int name, int size, int id)
{
    char *buf;

    buf = iosMallocDebug(ios_partition_oomori, size, __FILE__, 778);
    if (buf == 0) {
        /* not enough memory to load the camera data */
        debug_StdPrintfDummy("カメラデータをロードするためのメモリが足りません\n");
        debug_assert(__FILE__, 783);
        __assert(__FILE__, 783, "0");
    }
    systemStatus[8]++;
    iosCdvdHandlerRead(h, buf, size);
    AddPluralCameraSet(id, buf);
    iosFree(buf);
}

void ReadStageSettingFile(void *h, int name, int size)
{
    char *buf;

    systemStatus[8]++;
    /* "the stage information uses the .ssb file" */
    debug_StdPrintfDummy("ステージ情報に.ssbファイルを使用します.\n");
    if (size != sizeof(StageSetting)) {
        /* "the ssb file's size is wrong" */
        debug_StdPrintfDummy(
            "\033[31mssbファイルのサイズが正しくありません(filesize:%d correctsize:%d)\033[0m\n",
            size, sizeof(StageSetting));
    }
    buf = iosMallocDebug(ios_partition_seki, size, __FILE__, 824);
    iosCdvdHandlerRead(h, buf, size);
    memcpy(&GlobalStageSetting, buf, size);
    light_AddLight(0, 0, 0);
    tex_RemakeRegistersSampleMin(0);
}

void CSVSYSTEM_ReadCharFiles(Sub15C *rec, int id)
{
    int n = 0;

    if (id >= MAX_CHARS) {
        debug_StdPrintfDummy("Illegal Char ID Number. %d\n");
        debug_StdPrintfDummy("commmon/include/charFileName.hのMAX_CHARSを増やしてください\n");
        debug_assert(__FILE__, 877);
        __assert(__FILE__, 877, "0");
    }
    rec->modelId = id;
    debug_StdPrintfDummy("Link polygon & skelton & collision -> DObj. %d\n", id);
    rec->model = charFiles[id].pObj;
    debug_StdPrintfDummy("polygon %p.\n", rec->model);
    if (rec->model != 0) {
        debug_StdPrintfDummy("object name %s.\n", rec->model);
    }
    rec->shadow = charFiles[id].pShadow;
    debug_StdPrintfDummy("shadow %p.\n", rec->shadow);
    if (rec->shadow != 0) {
        debug_StdPrintfDummy("shadow object name %s.\n", rec->shadow);
    }
    rec->skel = charFiles[id].pSkel;
    debug_StdPrintfDummy("skelton %p.\n", rec->skel);
    rec->colData = (int)charFiles[id].pColl;
    debug_StdPrintfDummy("collision %p.\n", rec->colData);
    if (rec->skel != 0) {
        while (rec->skel[n].mirror != -1) {
            n++;
        }
        rec->skelNodeNum = n;
        rec->morphNum = rec->skel[n].kind;
        if (rec->morphNum < 0) {
            /* the shape data count information is old */
            debug_StdPrintfDummy("\033[36m シェイプデータの数情報が古いです。%d\033[m\n",
                                 rec->morphNum);
            rec->morphNum = 0;
        }
    } else {
        rec->skelNodeNum = 0;
        rec->morphNum = 0;
    }
}
