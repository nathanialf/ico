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

INCLUDE_ASM(InitCharFileManager);

INCLUDE_ASM(ResetCharFileManager);

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

INCLUDE_ASM(ReadSkeltonFile);

INCLUDE_ASM(ReadCollisionFile);

INCLUDE_ASM(ReadStageAnimationFile);

typedef struct { /* field names derived */
    char pad0[308];
    int area; /* 0x134, the motion memory area: 0 static, 4 dynamic, else swap */
    char pad138[92];
} MotEnt; /* 0x194 */ /* derived name */

/* motionOrientManager.h carries MotionDef and declares no motionKind */
extern MotEnt motionKind[];

INCLUDE_ASM(ReadMotionFile);

INCLUDE_ASM(ReadParticleEffectFile);

INCLUDE_ASM(ReadSoundBdFile);

typedef struct { /* field names derived */
    int mode;
    int bank;
} HdInfo; /* derived name */

/* the semi-common sound bank's header buffer, freed and reallocated on each
   load */
static char *semiCommonHdBuf = 0; /* derived name */

INCLUDE_ASM(ReadSoundHdFile);

typedef struct { /* field names derived */
    int mode;
    int bank;
} SqInfo; /* derived name */

/* ReadSoundSqFile and ReadSoundAdpcmFile, between ReadSoundHdFile and
   ReadShockFile; they are plain `inline`, so their out-of-line bodies come
   out at the end of the object. */

INCLUDE_ASM(ReadShockFile);

INCLUDE_ASM(ReadCamerasetFile);

INCLUDE_ASM(ReadEndCheckFile);

INCLUDE_ASM(ReadStageSettingFile);

INCLUDE_ASM(CSVSYSTEM_ReadCharFiles);

INCLUDE_ASM(ReadSoundSqFile);

INCLUDE_ASM(ReadSoundAdpcmFile);
