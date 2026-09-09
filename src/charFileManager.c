#include "common.h"

extern char *iosMallocDebug(int heap, int size, char *file, int line);
extern void iosFree(void *p);
extern void iosCdvdHandlerRead(void *h, void *buf, int size);
extern void SetParticleEffectPackage(int a0, void *buf, int size);
extern void debug_StdPrintfDummy(char *fmt, ...);
extern void debug_assert(char *file, int line);
extern void __assert(char *file, int line, char *expr);
extern void soundSQDataSet(void *buf, int a3, int kind, int mode, int a6);

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

extern CharFile D_006FAD00[1637];
extern CharFile D_004D9C10;
extern int D_0063AD00;
extern void InitPluralCameraSet(void);
extern void InitCameraSetManager(void);

void InitCharFileManager(void)
{
    int i;

    D_0063AD00 = 0;
    for (i = 0; i < 1637; i++) {
        D_006FAD00[i] = D_004D9C10;
    }
    InitPluralCameraSet();
    InitCameraSetManager();
}

void ResetCharFileManager(void)
{
    int i;

    D_0063AD00 = 0;
    for (i = 0; i < 1637; i++) {
        if (D_006FAD00[i].state == 1) {
            D_006FAD00[i] = D_004D9C10;
        }
    }
    InitPluralCameraSet();
    InitCameraSetManager();
}

extern int D_0028F4C0[];
extern int D_0063A44C;
extern char D_006193B0[];
extern char D_0063AD08[];
extern char D_0063AD10[];
extern char D_00619348[];
extern char D_00619370[];
extern char D_006193C8[];
extern char D_006193F8[];
extern int sprintf(char *buf, char *fmt, ...);
extern void debug_assertMessage(char *file, int line, char *msg);
extern void malloc_SetPartition(int part);
extern PObj *InitPObj(void *buf, int a1, int id);

/* D_00619348 / D_006193C8 / D_006193F8 / sprintf above belong to ReadModelFile,
   still asm below; its C sits in the seed store at 3 diffs. */
INCLUDE_ASM("asm/nonmatchings/src/charFileManager", ReadModelFile);

extern int D_0028F4C0[];
extern void malloc_SetPartition(int part);
extern int D_0063A44C;
extern char D_006193B0[];
extern char D_0063AD10[];
extern char D_00619370[];
extern char D_00619430[];
extern char D_00619450[];
extern char D_00619480[];
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
    buf = iosMallocDebug(D_0063A44C, size, D_006193B0, 190);
    if (id >= 1637) {
        debug_StdPrintfDummy(D_00619430, id);
        debug_StdPrintfDummy(D_00619370);
        debug_assert(D_006193B0, 195);
        __assert(D_006193B0, 195, D_0063AD10);
    }
    if (D_006FAD00[id].pObj != 0) {
        debug_StdPrintfDummy(D_00619450, id, a1);
        iosCdvdHandlerRead(h, 0, size);
        return;
    }
    iosCdvdHandlerRead(h, buf, size);
    debug_StdPrintfDummy(D_00619480, id, a1, buf, size);
    D_006FAD00[id].pObj = InitPObj(buf, a1, id);
    D_006FAD00[id].pObj->unk_20 = D_0063AD00++;
    iosFree(buf);
}

extern char D_006194B8[];
extern char D_006194D8[];
extern char D_00619508[];
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
    if (id >= 1637) {
        debug_StdPrintfDummy(D_006194B8, id);
        debug_StdPrintfDummy(D_00619370);
        debug_assert(D_006193B0, 235);
        __assert(D_006193B0, 235, D_0063AD10);
    }
    buf = iosMallocDebug(D_0063A44C, size, D_006193B0, 239);
    if (D_006FAD00[id].pShadow != 0) {
        debug_StdPrintfDummy(D_006194D8, id, a1);
        iosCdvdHandlerRead(h, 0, size);
        return;
    }
    iosCdvdHandlerRead(h, buf, size);
    debug_StdPrintfDummy(D_00619508, id, a1, buf, size);
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
extern char D_00619540[];
extern char D_00619570[];
extern int tex_InitTexture(int id, void *buf);
extern int D_0028F4C0[];
extern void malloc_SetPartition(int part);
extern int D_0063A44C;
extern char D_006193B0[];

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
    buf = iosMallocDebug(D_0063A44C, size, D_006193B0, 276);
    if (size == 0) {
        debug_StdPrintfDummy(D_00619540, a1);
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
    debug_StdPrintfDummy(D_00619570, rv, a1, buf, size);
    iosFree(buf);
}

typedef struct {
    char name[0x8C];
} SkelEnt; /* 0x8C */

extern SkelEnt D_004FBA80[];
extern char D_006195A8[];
extern char D_006195D0[];
extern char D_006195F8[];
extern char D_0063AD18[];
extern int strcmp(const char *a, const char *b);
extern char *mallocseki(int size);

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
    for (i = 0; i < 1637; i++) {
        if (D_004FBA80[i].name != 0 && strcmp(D_004FBA80[i].name, name) == 0) {
            if (p == 0) {
                if (D_006FAD00[i].pSkel != 0) {
                    debug_StdPrintfDummy(D_006195A8, name);
                    iosCdvdHandlerRead(h, 0, size);
                    p = D_006FAD00[i].pSkel;
                    sum = D_006FAD00[i].skelSum;
                } else {
                    int j;

                    p = mallocseki(size);
                    j = 0;
                    iosCdvdHandlerRead(h, p, size);
                    debug_StdPrintfDummy(D_006195D0, name, size);
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
        debug_StdPrintfDummy(D_006195F8, name);
        debug_assert(D_006193B0, 362);
        __assert(D_006193B0, 362, D_0063AD18);
    }
}

typedef struct {
    char name[0x8C];
} CollEnt; /* 0x8C */

extern CollEnt D_004FBAB0[];
extern char D_00619630[];
extern char D_00619658[];
extern char D_00619670[];
extern char D_006196A0[];
extern char D_006196B0[];
extern char D_006196C0[];
extern char D_006196D0[];
extern char D_006196E0[];
extern char D_006196F0[];
extern char D_00619700[];
extern char D_00619710[];
extern char D_00619720[];
extern float GetTableSin(short a);
extern float GetTableCos(short a);

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
    for (i = 0; i < 1637; i++) {
        if (strcmp(D_004FBAB0[i].name, name) == 0) {
            if (D_006FAD00[i].pColl != 0) {
                debug_StdPrintfDummy(D_00619630, name);
                iosCdvdHandlerRead(h, 0, size);
            } else {
                debug_StdPrintfDummy(D_00619658, size);
                D_006FAD00[i].pColl = (Coll *)mallocseki(size);
                iosCdvdHandlerRead(h, D_006FAD00[i].pColl, size);
                debug_StdPrintfDummy(D_00619670, name, size);
                p = D_006FAD00[i].pColl;
                p->unk_10 = (int)p + p->unk_10;
                p->unk_14 = (int)p + p->unk_14;
                p->unk_18 = (int)p + p->unk_18;
                p->unk_1C = (int)p + p->unk_1C;
                p->unk_20 = (int)p + p->unk_20;
                debug_StdPrintfDummy(D_006196A0, p);
                debug_StdPrintfDummy(D_006196B0, p->unk_10);
                debug_StdPrintfDummy(D_006196C0, p->unk_14);
                debug_StdPrintfDummy(D_006196D0, p->unk_18);
                debug_StdPrintfDummy(D_006196E0, p->unk_1C);
                debug_StdPrintfDummy(D_006196F0, p->unk_20);
                for (j = 0; j < 32; j++) {
                    for (k = 0; k < 32; k++) {
                        if (((int *)p->unk_18)[j * 32 + k] != 0) {
                            debug_StdPrintfDummy(D_00619700, j, k, ((int *)p->unk_18)[j * 32 + k]);
                            ((int *)p->unk_18)[j * 32 + k] =
                                (int)p + ((int *)p->unk_18)[j * 32 + k];
                        }
                        if (((int *)p->unk_1C)[j * 32 + k] != 0) {
                            debug_StdPrintfDummy(D_00619710, j, k, ((int *)p->unk_1C)[j * 32 + k]);
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
    debug_StdPrintfDummy(D_00619720, name);
    debug_assert(D_006193B0, 466);
    __assert(D_006193B0, 466, D_0063AD18);
}

extern char D_00619758[];
extern void stage_ApplyData(int id, void *buf);
extern char *mallocseki(int size);
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
        debug_assert(D_006193B0, 487);
        __assert(D_006193B0, 487, D_0063AD10);
    } else {
        malloc_SetPartition(1);
    }
    buf = mallocseki(size);
    iosCdvdHandlerRead(h, buf, size);
    debug_StdPrintfDummy(D_00619758, a3, a1, size);
    stage_ApplyData(a1, buf);
}

typedef struct {
    char _0[0x134];
    int unk_134; /* 0x134 */
    char _138[0x5C];
} MotEnt; /* 0x194 */

extern MotEnt D_0055FE58[];
extern char *D_004EB758[];
extern int D_0063A440;
extern int D_0063A444;
extern int D_0063A448;
extern char D_00619790[];
extern char D_006197C8[];
extern char D_006197E8[];
extern char D_00619818[];
extern char D_00619838[];
extern void InitMotionFile(void *buf, int a1);
extern void AddMotionMemorySize(int size, int a6);
extern int GetMotionMemorySize(int a6);

void ReadMotionFile(void *h, int a1, int size, int id, int a4, int a5, int a6)
{
    D_0028F4C0[8]++;
    if (size == 0) {
        return;
    }
    switch (D_0055FE58[id].unk_134) {
    case 0:
        D_004EB758[id] = iosMallocDebug(D_0063A444, size, D_006193B0, 515);
        break;
    case 4:
        D_004EB758[id] = iosMallocDebug(D_0063A440, size, D_006193B0, 518);
        if (D_004EB758[id] == 0) {
            debug_StdPrintfDummy(D_00619790);
            debug_assertMessage(D_006193B0, 521, D_006197C8);
            __assert(D_006193B0, 521, D_0063AD08);
        }
        break;
    default:
        D_004EB758[id] = iosMallocDebug(D_0063A448, size, D_006193B0, 526);
        if (D_004EB758[id] == 0) {
            debug_StdPrintfDummy(D_006197E8);
            debug_assertMessage(D_006193B0, 529, D_00619818);
            __assert(D_006193B0, 529, D_0063AD08);
        }
        break;
    }
    iosCdvdHandlerRead(h, D_004EB758[id], size);
    InitMotionFile(D_004EB758[id], a1);
    AddMotionMemorySize(size, a6);
    debug_StdPrintfDummy(D_00619838, id, a1, size,
                         (float)GetMotionMemorySize(a6) / 1024.0f / 1024.0f);
}

extern int D_0063A438;
extern char D_006193B0[];
extern int D_0028F4C0[];

void ReadParticleEffectFile(void *h, int a1, int size, int a3)
{
    char *buf = iosMallocDebug(D_0063A438, size, D_006193B0, 0x228);
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
extern char D_00619870[];
extern int soundSeSemiCommonLoadChk(void);
extern void soundBDDataSet(void *buf, int a3, int kind, int mode, int a6, int size);
extern int D_0063A684;

void ReadSoundBdFile(void *h, int a1, int size, int a3, int kind, int a5, int a6)
{
    char *buf;

    D_0028F4C0[8]++;
    if (size == 0) {
        return;
    }
    buf = iosMallocDebug(D_0063A44C, size, D_006193B0, 578);
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
        debug_assert(D_006193B0, 606);
        __assert(D_006193B0, 606, D_0063AD10);
    }
    iosFree(buf);
    debug_StdPrintfDummy(D_00619870, a3, a1, size);
}

typedef struct {
    int mode;
    int bank;
} HdInfo;

extern char *D_0063AD20;
extern int D_0063A45C;
extern int D_0063A444;
extern int D_0063A458;
extern char D_006198A0[];
extern void soundHDDataSet(void *buf, int a3, int kind, int mode, int a6);

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
        debug_assert(D_006193B0, 642);
        __assert(D_006193B0, 642, D_0063AD10);
    }
    if (info.bank == 0) {
        if (D_005EBBE8[a3].loaded != 1) {
            if (a6 == 0) {
                buf = iosMallocDebug(D_0063A444, size, D_006193B0, 650);
            } else {
                buf = iosMallocDebug(D_0063A458, size, D_006193B0, 652);
            }
        } else {
            a6 = 2;
            if (soundSeSemiCommonLoadChk() == 1) {
                buf = 0;
            } else {
                if (D_0063AD20 != 0) {
                    iosFree(D_0063AD20);
                }
                D_0063AD20 = iosMallocDebug(D_0063A45C, size, D_006193B0, 663);
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
    debug_StdPrintfDummy(D_006198A0, a3, a1, size);
}

extern char D_00619930[];
extern char *ShockVoiceSetCommon;
extern char *ShockVoiceSetStage;
extern void Init_ShockVoiceSet(void *hdr, void *body);
extern int D_0063A460;

void ReadShockFile(void *h, int a1, int size, int a3, int a4, int a5, int a6)
{
    char *p;

    D_0028F4C0[8]++;
    if (a6 == 0) {
        malloc_SetPartition(0);
        if (size == 0) {
            p = 0;
        } else {
            p = iosMallocDebug(D_0063A460, size + 16, D_006193B0, 788);
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
    debug_StdPrintfDummy(D_00619930, a3, a1, size);
}

extern char D_00619960[];
extern void AddPluralCameraSet(int slot, void *buf);
extern int D_0063A450;

void ReadCamerasetFile(void *h, int a1, int size, int a3)
{
    char *buf;

    buf = iosMallocDebug(D_0063A450, size, D_006193B0, 820);
    if (buf == 0) {
        debug_StdPrintfDummy(D_00619960);
        debug_assert(D_006193B0, 825);
        __assert(D_006193B0, 825, D_0063AD10);
    }
    D_0028F4C0[8]++;
    iosCdvdHandlerRead(h, buf, size);
    AddPluralCameraSet(a3, buf);
    iosFree(buf);
}

extern char D_006193B0[];
extern int D_0028F4C0[];

void ReadEndCheckFile(void *h, int a1, int size)
{
    char *buf = iosMallocDebug(D_0063A450, size, D_006193B0, 0x356);
    D_0028F4C0[8]++;
    iosCdvdHandlerRead(h, buf, size);
    iosFree(buf);
}

extern char D_0028F720[];
extern void *memcpy(void *dst, const void *src, int n);
extern void light_AddLight(int a, int b, int c);
extern void tex_RemakeRegistersSampleMin(int a);
extern int D_0063A44C;

void ReadStageSettingFile(void *h, int a1, int size)
{
    char *buf;

    D_0028F4C0[8]++;
    buf = iosMallocDebug(D_0063A44C, size, D_006193B0, 905);
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

extern char D_00619998[];
extern char D_006199B8[];
extern char D_006199E8[];
extern char D_006199F8[];
extern char D_00619A10[];
extern char D_00619A20[];
extern char D_00619A38[];
extern char D_00619A48[];
extern char D_00619A58[];
extern char D_00619A88[];
extern char D_00619AB0[];
extern char D_00619AF8[];
extern char D_00619B30[];
extern char D_00619B68[];

void CSVSYSTEM_ReadCharFiles(CsvChar *rec, int id)
{
    int n = 0;
    int sum;

    if (id >= 1637) {
        debug_StdPrintfDummy(D_00619998);
        debug_StdPrintfDummy(D_00619370);
        debug_assert(D_006193B0, 927);
        __assert(D_006193B0, 927, D_0063AD10);
    }
    rec->unk_84 = id;
    debug_StdPrintfDummy(D_006199B8, id);
    rec->unk_854 = D_006FAD00[id].pObj;
    debug_StdPrintfDummy(D_006199E8, rec->unk_854);
    if (rec->unk_854 != 0) {
        debug_StdPrintfDummy(D_006199F8, rec->unk_854);
    }
    rec->unk_858 = D_006FAD00[id].pShadow;
    debug_StdPrintfDummy(D_00619A10, rec->unk_858);
    if (rec->unk_858 != 0) {
        debug_StdPrintfDummy(D_00619A20, rec->unk_858);
    }
    rec->unk_8C = D_006FAD00[id].pSkel;
    debug_StdPrintfDummy(D_00619A38, rec->unk_8C);
    rec->unk_70 = (int)D_006FAD00[id].pColl;
    debug_StdPrintfDummy(D_00619A48, rec->unk_70);
    if (rec->unk_8C != 0) {
        while (*(int *)(rec->unk_8C + n * 64) != -1) {
            n++;
        }
        rec->unk_88 = n;
        rec->unk_834 = *(int *)(rec->unk_8C + n * 64 + 4);
        if (rec->unk_834 < 0) {
            debug_StdPrintfDummy(D_00619A58, rec->unk_834);
            rec->unk_834 = 0;
        }
        sum = SumBytes((unsigned char *)rec->unk_8C, rec->unk_88 * 64);
        if (sum == D_006FAD00[id].skelSum) {
            debug_StdPrintfDummy(D_00619A88, rec->unk_854, sum);
        } else {
            debug_StdPrintfDummy(D_00619AB0);
            debug_StdPrintfDummy(D_00619AF8, rec->unk_854, sum, D_006FAD00[id].skelSum);
            debug_StdPrintfDummy(D_00619B30);
            debug_StdPrintfDummy(D_00619B68);
        }
    } else {
        rec->unk_88 = 0;
        rec->unk_834 = 0;
    }
}

typedef struct {
    int mode;
    int bank;
} SqInfo;

extern int D_0063A444;
extern int D_0063A458;
extern int D_0063A684;
extern char D_006193B0[];
extern char D_006198D0[];
extern int D_0028F4C0[];

void ReadSoundSqFile(void *h, int a1, int size, int a3, int kind, int a5, int a6)
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
        debug_assert(D_006193B0, 709);
        __assert(D_006193B0, 709, D_0063AD10);
    }
    if (info.bank == 0) {
        if (a6 == 0) {
            buf = iosMallocDebug(D_0063A444, size, D_006193B0, 715);
        } else {
            buf = iosMallocDebug(D_0063A458, size, D_006193B0, 717);
        }
    } else {
        buf = 0;
    }
    iosCdvdHandlerRead(h, buf, size);
    if (buf != 0) {
        soundSQDataSet(buf, a3, kind, info.mode, a6);
    }
    debug_StdPrintfDummy(D_006198D0, a3, a1, size);
}

extern void *soundDataAreaSearch(int *key);
extern void *AdpcmIopBuffAlloc(void);
extern char *adpcmDataSet(char *buf, int a3, int bank, int a6, int size, void *iop, int zero);
extern void AdpcmPlay(int handle);
extern char D_00619900[];

void ReadSoundAdpcmFile(void *h, int a1, int size, int a3, int a4, int a5, int a6)
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
        p = iosMallocDebug(D_0063A444, size, D_006193B0, 757);
        iosCdvdHandlerRead(h, p, size);
        debug_StdPrintfDummy(D_00619900, a3, a1, size);
        q = adpcmDataSet(p, a3, a4, a6, size, AdpcmIopBuffAlloc(), 0);
        iosFree(p);
        AdpcmPlay(*(int *)(q + 0x2C));
    } else {
        iosCdvdHandlerRead(h, 0, size);
    }
}

PObj *GetPObjAddress(int a0)
{
    return D_006FAD00[a0].pObj;
}
