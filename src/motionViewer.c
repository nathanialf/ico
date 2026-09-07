#include "common.h"

#include "sugiCommon.h"

struct MvObj;
extern struct MvObj *D_0063BA08;
extern int D_0063BA10;
extern void SetRootUpdateMode(void *self, int val);

void setRootUpdateMode(void)
{
    SetRootUpdateMode(D_0063BA08, D_0063BA10);
}
extern void SetMotionPlaySpeedRatio(void *obj, float ratio);

void setMotionSpeed(float ratio)
{
    SetMotionPlaySpeedRatio(D_0063BA08, ratio);
}
/* dispProgressBar is defined as a nested function inside dispMotFrameProgress
 * below (the listing names it dispProgressBar.108). */
typedef struct { unsigned char r, g, b, a; } BarCol;
typedef struct { int x, y, w, h; } BarRect;

typedef struct {
    char pad000[0x134];
    int unk134;                     /* 0x134 */
    char pad138[0x13C - 0x138];
    int frameA;                     /* 0x13C */
    int frameB;                     /* 0x140 */
    char pad144[0x178 - 0x144];
    int unk178;                     /* 0x178 */
    char pad17C[0x18C - 0x17C];
    unsigned int flags;             /* 0x18C */
    char pad190[0x194 - 0x190];
} MotRec;

extern MotRec D_0055FE58[];
extern BarCol D_0063BA18[];
extern BarCol D_0063BA20[];
extern int D_0063A064;
extern int D_0063A068;
extern int GetNbMotionFrames(int obj);
extern void gif_StartPacketPri(int pri);
extern void gif_SetZTest(int on);
extern void gif_SetZWrite(int on);
extern void gif_SetAlpha(int a, int b, int c);
extern void gif_SpriteSensitiveOrg(void *rect, int a1, int a2, void *col, int a4);
extern void gif_EndPacket(void);

void dispMotFrameProgress(int obj, float cur)
{
    /* dispProgressBar is a nested function in the ROM: dispMotFrameProgress
     * passes it a static chain in $2 (STATIC_CHAIN_REGNUM), which it spills
     * to 0(sp).  The listing names it dispProgressBar.108. */
    void dispProgressBar(int s, int e, int n, float c, BarCol *col)
    {
        float r0 = (float)s / (float)n;
        float r1 = (float)e / (float)n;
        float rc = c / (float)n;

        gif_StartPacketPri(0xB);
        gif_SetZTest(0);
        gif_SetZWrite(0);
        gif_SetAlpha(1, 5, 0x80);
        if (r0 < rc && rc <= r1) {
            BarCol dark = { col->r / 2, col->g / 2, col->b / 2, 0x80 };
            BarRect ra = {
                (int)((-(D_0063A064 << 4) / 2 + (D_0063A064 << 4) * r0) * 8 / 10),
                ((D_0063A068 << 4) * 6 / 20) & ~15,
                (int)(((D_0063A064 << 4) * (rc - r0)) * 8 / 10),
                (((D_0063A068 << 4) / 100) & ~15) + 24
            };
            BarRect rb = {
                (int)((-(D_0063A064 << 4) / 2 + (D_0063A064 << 4) * rc) * 8 / 10),
                ra.y,
                (int)(((D_0063A064 << 4) * (r1 - rc)) * 8 / 10),
                ra.h
            };
            gif_SpriteSensitiveOrg(&ra, 0, 0, col, 1);
            gif_SpriteSensitiveOrg(&rb, 0, 0, &dark, 1);
        } else {
            BarRect rc2 = {
                (int)((-(D_0063A064 << 4) / 2 + (D_0063A064 << 4) * r0) * 8 / 10),
                ((D_0063A068 << 4) * 6 / 20) & ~15,
                (int)(((D_0063A064 << 4) * (r1 - r0)) * 8 / 10),
                (((D_0063A068 << 4) / 100) & ~15) + 24
            };
            if (rc <= r0) {
                BarCol dark = { col->r / 2, col->g / 2, col->b / 2, 0x80 };
                gif_SpriteSensitiveOrg(&rc2, 0, 0, &dark, 1);
            } else {
                gif_SpriteSensitiveOrg(&rc2, 0, 0, col, 1);
            }
        }
        gif_SetZTest(1);
        gif_SetZWrite(1);
        gif_EndPacket();
    }
    BarCol colA = D_0063BA18[0];
    BarCol colB = D_0063BA20[0];
    float f1 = D_0055FE58[obj].frameA;
    float f2 = D_0055FE58[obj].frameB;

    if (f1 >= 0.0f && f2 >= 0.0f) {
        float sum = f1 + f2;
        int rev;

        dispProgressBar(0, f1, GetNbMotionFrames(obj) - 1, cur,
                        (rev = (((D_0055FE58 + obj)->flags >> 19) & 1)) ? &colB : &colA);
        dispProgressBar(f1, sum, GetNbMotionFrames(obj) - 1, cur, rev ? &colA : &colB);
        dispProgressBar(sum, GetNbMotionFrames(obj) - 1, GetNbMotionFrames(obj) - 1, cur,
                        rev ? &colB : &colA);
    } else {
        dispProgressBar(0, GetNbMotionFrames(obj) - 1, GetNbMotionFrames(obj) - 1, cur, &colA);
    }
}
typedef struct MvSub {
    char  pad000[0xC];
    char  *nodes;               /* 0x00C — per-node 0x40 matrices */
    char  pad010[0x8C - 0x10];
    float *ground;              /* 0x08C */
    char  pad090[0xF0 - 0x90];
    short rot;                  /* 0x0F0 */
    char  padF2[2];
    float speed;                /* 0x0F4 */
    char  padF8[0x2D0 - 0xF8];
    int   lookMode;             /* 0x2D0 */
    char  pad2D4[0x2E0 - 0x2D4];
    float lookAt[4];            /* 0x2E0 */
    char  pad2F0[0x330 - 0x2F0];
    int   headMode;             /* 0x330 */
    char  pad334[0x340 - 0x334];
    float headAt[4];            /* 0x340 */
    char  pad350[0x380 - 0x350];
    int   testMode;             /* 0x380 */
    char  pad384[0x390 - 0x384];
    float testAt[4];            /* 0x390 */
    char  pad3A0[0x488 - 0x3A0];
    int   select;               /* 0x488 — "this object is the viewer target" */
} MvSub;

typedef struct MvObj {
    char   pad00[0x28];
    void  *motTbl;              /* 0x28 — parallel motion table, parked while viewing */
    char   pad2C[0x15C - 0x2C];
    MvSub *sub;                 /* 0x15C */
} MvObj;

typedef struct MvMenuEnt {
    char *name;                 /* 0x00 — csv window title */
    int  kind;                  /* 0x04 — isys object kind */
    int  motFirst;              /* 0x08 — first motion id of this object's block */
    int  motLast;               /* 0x0C */
    int  oriFrom;               /* 0x10 — first motionOrient row */
    int  oriTo;                 /* 0x14 — one past the last motionOrient row */
} MvMenuEnt;

extern MvMenuEnt objMenu[];
extern char D_00620718[];
extern MvObj *D_00639EC0;
extern int D_0063B9F8;
extern int D_0063B9FC;
extern float D_0063BA14;
extern int D_0063BA24;
extern char *D_0063BA28;
extern void Camctrl_SetTarget(MvObj *gobj, int a1, int a2);
extern void CameraSetMode(int mode);
extern int debug_SelectCsvWindow(char *title, int a1, int a2, int a3, void *tbl,
                                 int stride, int a6, int a7, int count, int *cur);
extern int isEnemyActive(MvObj *gobj);
extern MvObj *isysGObjSearchFromObjKindID_begin(int kind);
extern MvObj *isysGObjSearchFromObjKindID_next(MvObj *gobj);
extern void SetParallelMotionTableWithNoRequest(MvObj *gobj, int a1, int a2);

int objMenuProc(void)
{
    int ret = debug_SelectCsvWindow(D_00620718, 10, 0x32, 0xB, objMenu, 0x18, 0, 1, 5,
                                    &D_0063B9F8);

    if (D_0063BA24 != D_0063B9F8) {
        if (D_0063BA08) {
            D_0063BA08->motTbl = D_0063BA28;
            D_0063BA08->sub->select = 0;
        }
        D_0063BA08 = isysGObjSearchFromObjKindID_begin(objMenu[D_0063B9F8].kind);
        if (objMenu[D_0063B9F8].kind == 4) {
            for (; D_0063BA08 != 0; D_0063BA08 = isysGObjSearchFromObjKindID_next(D_0063BA08)) {
                if (isEnemyActive(D_0063BA08)) {
                    break;
                }
            }
        }
        if (D_0063BA08) {
            D_00639EC0 = D_0063BA08;
            Camctrl_SetTarget(D_0063BA08, 0, 3);
            D_0063BA28 = D_0063BA08->motTbl;
            D_0063BA08->motTbl = 0;
            SetParallelMotionTableWithNoRequest(D_0063BA08, 0, 0);
            D_0063BA08->sub->select = 1;
        }
        D_0063BA24 = D_0063B9F8;
        CameraSetMode(2);
    }
    if (ret == 1) {
        D_0063BA14 = 1.0f;
        setMotionSpeed(D_0063BA14);
        if (D_0063BA08 != 0) {
            D_0063B9FC = 0;
        } else {
            ret = 0;
        }
    }
    if (ret == -1) {
        D_00639EC0 = isysGObjSearchFromObjKindID_begin(1);
        Camctrl_SetTarget(D_00639EC0, 0, 3);
        if (D_0063BA08) {
            D_0063BA08->motTbl = D_0063BA28;
            D_0063BA08->sub->select = 0;
        }
        D_0063BA08 = 0;
        D_0063BA28 = 0;
        D_0063BA24 = ret;
        CameraSetMode(3);
    }
    return ret;
}
/*SWEEPmotKindMenuProc*/
typedef struct MvPad {
    int  now;                   /* 0x00 */
    int  trg;                   /* 0x04 */
    int  unk08;                 /* 0x08 */
    int  rep;                   /* 0x0C */
    char unk10[0x54 - 0x10];
    unsigned char stick[4];     /* 0x54 — the two analog sticks */
} MvPad;

/* motionOrientManager's table row (same object as src/motionOrientManager.c) */
typedef struct MotionOrientEntry {
    int id;
    int kind;
    int pad[4];
} MotionOrientEntry;

/* one row of the orient csv the viewer browses: name + the kind it selects */
typedef struct OriRow {
    char *name;                 /* 0x00 */
    int   kind;                 /* 0x04 */
} OriRow;

extern MotionOrientEntry D_002ADD60[];
extern MvPad D_0028F8F0[];
extern int D_004EB758[];
extern char D_005D1278[][0x20];
extern char D_00620700[];
extern char D_00620728[];
extern char D_00620748[];
extern char D_00620760[];
extern int D_0063A438;
typedef struct OriCsv { int sel; OriRow *rows; } OriCsv;
extern OriCsv D_0063BA00;
extern int D_0063BA0C;
extern float D_0063BA14;
extern int D_0063BA2C;
extern int D_0063C4AC;
extern void DisableChangeRootUpdateMode(MvObj *gobj);
extern void DisableMotionOrientUpdate(MvObj *gobj);
extern void EnableChangeRootUpdateMode(MvObj *gobj);
extern void EnableMotionOrientUpdate(MvObj *gobj);
extern float ForMotionViewer_GetCurrentAnimationFrame(MvObj *gobj);
extern int ForMotionViewer_GetCurrentMotion(MvObj *gobj);
extern MotionOrientEntry *GetMotionOrient(int i, int n, int id, int kind);
extern float GetMotionPlaySpeedRatio(int motion);
extern void InitMotionOrient(MvObj *gobj, int a1, int a2, int a3, int a4, int a5);
extern void debug_PrintfDummy(int x, int y, unsigned int color, const char *fmt, ...);
extern int debug_SelectCsvWindowWithLine(char *title, int a1, int a2, int a3,
                                         void *tbl, int stride, int a6, int a7,
                                         int count, int *cur, int a10);
extern int fptodp(float f);
extern void *iosMallocDebug(int heap, int size, char *file, int line);

static inline int countMotionKinds(int id, int from, int to)
{
    int n = 0;
    int i;

    for (i = from; i < to; i++) {
        if (D_002ADD60[i].id == id || D_002ADD60[i].id == 0x47A) {
            n++;
        }
    }
    return n;
}

static inline int makeMotionKindList(MvMenuEnt *ent, int base)
{
    OriRow *list;
    int id = ent->motFirst + base, from = ent->oriFrom, to = ent->oriTo;
    int n = countMotionKinds(id, from, to);
    int i;
    int k;

    list = iosMallocDebug(D_0063A438, n * 8, D_00620700, 93);
    if (n) {
        k = 0;
        for (i = from; i < to; i++) {
            if (D_002ADD60[i].id == id || D_002ADD60[i].id == 0x47A) {
                int kind = D_002ADD60[i].kind;

                list[k].kind = kind;
                list[k].name = D_005D1278[kind];
                k++;
            }
        }
    }
    D_0063BA00.rows = list;
    return n;
}

int motKindMenuProc(void)
{
    MvMenuEnt *ent = &objMenu[D_0063B9F8];
    int mot = ForMotionViewer_GetCurrentMotion(D_0063BA08);
    float speed = GetMotionPlaySpeedRatio(mot);
    int ret;
    int base;
    int cur;

    dispMotFrameProgress(mot, ForMotionViewer_GetCurrentAnimationFrame(D_0063BA08));
    ret = debug_SelectCsvWindowWithLine(ent->name, 10, 0x46, 6,
                                        &D_0055FE58[ent->motFirst], 0x194, 0xC0, 0,
                                        ent->motLast - ent->motFirst,
                                        &D_0063B9FC, 0);
    base = D_0063B9FC;
    cur = base + ent->motFirst;
    if (D_0055FE58[cur].unk134 != 0 && D_0055FE58[cur].unk178 == 0x140 &&
        D_004EB758[cur] == 0) {
        base = 0;
        if (((D_0063BA0C >> 4) & 3) != 0) {
            debug_PrintfDummy(10, 0x3C, 0x4080FF00, D_00620728);
        }
    } else {
        debug_PrintfDummy(10, 0x32, 0xC0FFFF00, D_00620748,
                          fptodp(ForMotionViewer_GetCurrentAnimationFrame(D_0063BA08)),
                          GetNbMotionFrames(mot) - 1);
        debug_PrintfDummy(10, 0x3C, 0x80FFFF00, D_00620760, fptodp(speed),
                          fptodp(ForMotionViewer_GetCurrentAnimationFrame(D_0063BA08) / speed),
                          (int)((GetNbMotionFrames(mot) - 1) / speed));
    }
    if (D_0063B9FC != D_0063BA2C) {
        DisableChangeRootUpdateMode(D_0063BA08);
        DisableMotionOrientUpdate(D_0063BA08);
        InitMotionOrient(D_0063BA08, base + ent->oriFrom, base + ent->oriTo, -1, -1,
                         base + ent->motFirst);
        D_0063BA2C = D_0063B9FC;
    }
    if (D_0028F8F0[0].trg & 0x10) {
        InitMotionOrient(D_0063BA08, base + ent->oriFrom, base + ent->oriTo, -1, -1,
                         base + ent->motFirst);
    }
    if (ret == 1) {
        D_0063C4AC = makeMotionKindList(ent, base);
        D_0063BA00.sel = 0;
    }
    if (ret == -1) {
        InitMotionOrient(D_0063BA08, ent->oriFrom, ent->oriTo, -1, -1, ent->motFirst);
        EnableMotionOrientUpdate(D_0063BA08);
        EnableChangeRootUpdateMode(D_0063BA08);
        D_0063BA2C = ret;
    }
    return ret;
}
/*SWEEP-ENDmotKindMenuProc*/
/*SWEEPmotOriMenuProc*/
extern char D_0055FF18[];
extern char D_00620778[];
extern char D_00620798[];
extern char D_006207A8[];
extern char D_006207D0[];
extern char D_0063BA38[];
extern int D_0063BA30;
extern void SetMotionRequest(MvObj *gobj, int motion, void *a2);
extern void iosFree();
extern void sprintf();

INCLUDE_ASM("asm/nonmatchings/src/motionViewer", motOriMenuProc);
/*SWEEP-ENDmotOriMenuProc*/
/*SWEEPmodeMessage*/
extern char D_006207C0[];
extern float D_00639658;
extern float D_0063965C;
extern char D_0063BA40[];
extern char D_0063BA48[];
extern char D_0063BA50[];
extern int scePadRead(int port, int slot, unsigned char *rdata);

INCLUDE_ASM("asm/nonmatchings/src/motionViewer", modeMessage);
/*SWEEP-ENDmodeMessage*/
/*SWEEPlookAtTest*/
typedef struct MvVec { float x, y, z, w; } __attribute__((aligned(16))) MvVec;
typedef struct MvCol { int r, g, b, a; } __attribute__((aligned(16))) MvCol;

extern float D_0028FF00[];
extern void CopyVector(void *dst, void *src);
extern void DrawLineG(void *p0, void *c0, void *p1, void *c1, int f);
extern void GetRootPosition(void *dst, MvObj *gobj);
extern float GetTableCos(short a);
extern float GetTableSin(short a);
extern void *MatrixDrive_GetMatrix(void);
extern void MatrixDrive_RotMatrixX(short a);
extern void MatrixDrive_RotMatrixY(short a);
extern void MatrixDrive_RotMatrixZ(short a);
extern void MatrixDrive_ScaleMatrix(float x, float y, float z);
extern void MatrixDrive_TransMatrixV(void *v);
extern void sceVu0UnitMatrix(void *m);

void lookAtTest(MvVec *pos, float rad, void *colAxis, void *colRing, short dy,
                short ang)
{
    float p0[4];
    float p1[4];
    float fdy = dy;
    float sx = rad * GetTableSin(ang);
    float cx = rad * GetTableCos(ang);
    int a;

    GetRootPosition(pos, D_0063BA08);
    gif_StartPacketPri(0xB);
    sceVu0UnitMatrix(MatrixDrive_GetMatrix());
    MatrixDrive_TransMatrixV(pos);
    for (a = 0; a <= 0xFFFF; a += 2048) {
        p0[1] = p1[1] = 0.0f;
        p0[0] = rad * GetTableCos(a);
        p0[2] = rad * GetTableSin(a);
        p1[0] = rad * GetTableCos(a + 2048);
        p1[2] = rad * GetTableSin(a + 2048);
        DrawLineG(p0, colRing, p1, colRing, 0);
    }
    gif_EndPacket();

    pos->y += fdy;
    gif_StartPacketPri(0xB);
    sceVu0UnitMatrix(MatrixDrive_GetMatrix());
    MatrixDrive_TransMatrixV(pos);
    for (a = 0; a <= 0xFFFF; a += 2048) {
        p0[1] = p1[1] = 0.0f;
        p0[0] = rad * GetTableCos(a);
        p0[2] = rad * GetTableSin(a);
        p1[0] = rad * GetTableCos(a + 2048);
        p1[2] = rad * GetTableSin(a + 2048);
        DrawLineG(p0, colRing, p1, colRing, 0);
    }
    gif_EndPacket();

    pos->x += sx;
    pos->z += cx;
    gif_StartPacketPri(0xB);
    sceVu0UnitMatrix(MatrixDrive_GetMatrix());
    MatrixDrive_TransMatrixV(pos);

    CopyVector(p0, D_0028FF00);
    CopyVector(p1, D_0028FF00);
    p1[0] -= sx;
    p1[2] -= cx;
    DrawLineG(p0, colAxis, p1, colAxis, 0);

    CopyVector(p0, D_0028FF00);
    CopyVector(p1, D_0028FF00);
    p1[1] -= fdy;
    DrawLineG(p0, colAxis, p1, colAxis, 0);

    p0[1] -= fdy;
    p1[0] -= sx;
    p1[2] -= cx;
    DrawLineG(p0, colAxis, p1, colAxis, 0);

    MatrixDrive_RotMatrixX(random_unit() * 65536.0f);
    MatrixDrive_RotMatrixY(random_unit() * 65536.0f);
    MatrixDrive_RotMatrixZ(random_unit() * 65536.0f);
    MatrixDrive_ScaleMatrix(random_unit() * 3.0f + 1.0f,
                            random_unit() * 3.0f + 1.0f,
                            random_unit() * 3.0f + 1.0f);
    for (a = 0; a < 3; a++) {
        CopyVector(p0, D_0028FF00);
        CopyVector(p1, D_0028FF00);
        p0[a] -= 10.0f;
        p1[a] += 10.0f;
        DrawLineG(p0, colAxis, p1, colAxis, 0);
    }
    gif_EndPacket();
}
/*SWEEP-ENDlookAtTest*/
/*SWEEPMotionViewer*/
extern MvCol D_004ECC70;
extern MvCol D_004ECC80;
extern MvCol D_004ECC90;
extern MvVec D_006207E0;
extern MvVec D_006207F0;
extern char D_00620800[];
extern char D_00620820[];
extern char D_00620840[];
extern char D_00620860[];
extern int D_0063B198;
extern int D_0063BA58;
extern int D_0063BA5C;
extern int D_0063BA60;
extern short D_0063BA64;
extern short D_0063BA66;
extern int D_0063BA68;
extern int D_0063BA6C;
extern int D_0063BA70;
extern float D_0063BA74;
extern char *matrixptr;
extern float FSqrt(float x);
extern int GetSkeltonFocusNode(MvObj *gobj, int node);
extern void SetMotionDirection(MvObj *gobj, MvVec *dir);
extern void dispPlane(MvVec *plane, MvVec *pos);
extern void *memset(void *dst, int c, int n);
extern void sceVu0ApplyMatrix(MvVec *dst, void *m, MvVec *src);
extern float sceVu0InnerProduct(MvVec *a, MvVec *b);
extern void sceVu0TransposeMatrix(void *dst, void *src);

INCLUDE_ASM("asm/nonmatchings/src/motionViewer", MotionViewer);
/*SWEEP-ENDMotionViewer*/
