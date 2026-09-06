#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/effectTool", _dispParam);
INCLUDE_ASM("asm/nonmatchings/src/effectTool", editParam);
INCLUDE_ASM("asm/nonmatchings/src/effectTool", dispXZYZCircle);
INCLUDE_ASM("asm/nonmatchings/src/effectTool", dispCircle2);
extern short D_0063B858;
extern short D_0063B85A;
extern void RotQuaternionX(int *self, short y);
extern void RotQuaternionY(int *self, short y);
extern void SetIdentityQuaternion(int *self);

void setQ(int *self)
{
    SetIdentityQuaternion(self);
    RotQuaternionY(self, -D_0063B858);
    RotQuaternionX(self, -D_0063B85A);
}
INCLUDE_ASM("asm/nonmatchings/src/effectTool", dispEffectToolField);
/* the shared pad-state array (op.c's PadState, GsBase.c's GsbPad): 0x58 per
 * pad, trg at 0x4 and rep at 0xC; this tool reads pad 0 and pad 1. */
typedef struct {
    int unk00;          /* 0x00 */
    int trg;            /* 0x04 */
    int unk08;          /* 0x08 */
    int rep;            /* 0x0C */
    char unk10[0x48];   /* 0x10 */
} EffToolPad;
extern EffToolPad D_0028F8F0[];

extern float D_00720170[];
extern int D_0063B854;
extern int D_0063B85C;
extern int D_0063B864;

/* the effect-parameter descriptor table _dispParam/editParam walk: 0x1C per
 * entry, name pointer first, NULL-terminated. */
typedef struct {
    char *name;         /* 0x00 */
    char unk04[0x18];   /* 0x04 */
} EffParamDef;
extern EffParamDef D_004E74A0[];

extern int *GetParticleEffectPackage(int id);
extern void ResetParticleEffectPackages(int *pkg);
extern void DeleteParticleEffect(int id);
extern int SetParticleEffect(int id, void *pos, void *quat);
extern int editParam(int id, int sel);
extern void _dispParam(int *pkg, int i, int x, int y, int color);

/* two static helpers the PAL listing places at effectTool.c lines 260 and
 * 266-275 and inlines into EditTarget; neither is emitted out of line, so
 * neither has a MAIN.MAP symbol and these names are ours. */
static inline int countEffectParams(void)
{
    int n = 0;
    if (D_004E74A0[0].name != 0) {
        do {
            n++;
        } while (D_004E74A0[n].name != 0);
    }
    return n;
}

static inline void dispEffectParams(int id, int sel)
{
    int n = countEffectParams();
    int *pkg = GetParticleEffectPackage(id);
    int start = sel - 5;
    int i;

    if (start < 0) {
        start = 0;
    }
    if (start + 10 > n) {
        start = n - 10;
    }
    for (i = 0; i < 10 && start + i < n; i++) {
        _dispParam(pkg, start + i, 10, i * 8 + 0x32,
                   (sel == start + i) ? 0x00E0FF00 : 0xFFFFFF00);
    }
}

int EditTarget(int id)
{
    int q[4];
    int n;

    n = countEffectParams();
    setQ(q);
    if (editParam(id, D_0063B864) != 0) {
        ResetParticleEffectPackages(GetParticleEffectPackage(id));
        DeleteParticleEffect(D_0063B854);
        D_0063B854 = SetParticleEffect(D_0063B85C, D_00720170, q);
    }
    dispEffectParams(id, D_0063B864);
    if ((D_0028F8F0[0].rep & 0x1000) || (D_0028F8F0[1].rep & 0x1000)) {
        D_0063B864--;
        if (D_0063B864 < 0) {
            D_0063B864 = n - 1;
        }
    }
    if ((D_0028F8F0[0].rep & 0x4000) || (D_0028F8F0[1].rep & 0x4000)) {
        D_0063B864++;
        if (D_0063B864 == n) {
            D_0063B864 = 0;
        }
    }
    if ((D_0028F8F0[0].trg & 0x40) || (D_0028F8F0[1].trg & 0x40)) {
        return -1;
    }
    return 0;
}
extern char D_0061F530[];
extern char D_0061F570[];
extern char D_0061F598[];
extern char D_0061F5C8[];
extern char D_0061F5D8[];
/* particleEffect.c's effect table is 0x50 bytes per entry: char name[0x20]
   then char file[0x30].  D_0062A298 is &tbl[0].file (D_0062A278 = &tbl[0].name). */
extern char D_0062A298[];
extern int *GetParticleEffectPackage(int id);
extern void debug_closeLog(void);
extern void debug_openLog(void);
extern int debugSceOpen(void *name, int flags);
extern int debugSceClose(int fd);
extern int sceWrite(int fd, void *buf, int size);
extern void debug_StdPrintfDummy(char *fmt, ...);

int saveEffectData(int id)
{
    int *pkg;

    pkg = GetParticleEffectPackage(id);
    debug_closeLog();
    debug_StdPrintfDummy(D_0061F530);
    if (debugSceOpen(D_0062A298 + id * 0x50, 0x602) < 0) {
        debug_StdPrintfDummy(D_0061F570);
    } else {
        debug_StdPrintfDummy(D_0061F598, D_0062A298 + id * 0x50,
                             D_0062A298 + id * 0x50 - 0x20, 0xA0);
        debug_StdPrintfDummy(D_0061F5C8, sceWrite(0, pkg, 0xA0));
        debugSceClose(0);
    }
    debug_StdPrintfDummy(D_0061F5D8);
    debug_openLog();
    return 0;
}
extern char iosPadConfDefault[];
extern float D_006394B8;
extern float D_00720170[];
extern int D_0063B854;

/* iosPadGetStick's output block (camera-ico2.c's IosPadStick, extended): the
 * camera-coord helper reads the two floats at 0xC/0x10 as a1[3]/a1[4]. */
typedef struct {
    int x;              /* 0x00 */
    int y;              /* 0x04 */
    int unk08;          /* 0x08 */
    float fx;           /* 0x0C */
    float fz;           /* 0x10 */
    float mag;          /* 0x14 */
    char unk18[8];      /* 0x18 */
} EffToolStick;

extern int iosPadConnect(void *pad, int slot, int port, void *conf);
extern void iosPadRead(void *pad);
extern int iosPadGetStick(void *pad, EffToolStick *out, int a2, int a3, int a4, int a5);
extern void iosPadStickCameraCoord(void *out, float *stick);
extern int *GetParticleEffectPackage(int id);
extern void SetParticleEffectGeometry(int id, void *pos, void *quat);

void moveEffectToolGeometry(int idx)
{
    float v[4];
    int padCtx[0x60 / 4];
    EffToolStick st0;
    EffToolStick st1;
    int q[4];
    int *pkg;

    iosPadConnect(padCtx, 0, 0, iosPadConfDefault);
    iosPadRead(padCtx);
    iosPadGetStick(padCtx, &st0, 0, 2, 2, 0);
    iosPadGetStick(padCtx, &st1, 1, 2, 2, 0);
    iosPadStickCameraCoord(v, (float *)&st0);
    if (st0.mag > D_006394B8) {
        D_00720170[0] += v[0] * st0.mag * 16.0f;
        D_00720170[2] += v[2] * st0.mag * 16.0f;
    }
    if (st1.mag > D_006394B8) {
        if (padCtx[2] & 2) {
            D_00720170[1] += st1.fz * st1.mag * 16.0f;
        } else {
            D_0063B858 = D_0063B858 + st1.fx * 256.0f * st1.mag;
            D_0063B85A = D_0063B85A + st1.fz * 256.0f * st1.mag;
            if (D_0063B85A < -0x4000) {
                D_0063B85A = -0x4000;
            }
            if (D_0063B85A > 0x4000) {
                D_0063B85A = 0x4000;
            }
        }
    }
    pkg = GetParticleEffectPackage(idx);
    if (pkg[1] != 0) {
        setQ(q);
        SetParticleEffectGeometry(D_0063B854, D_00720170, q);
    }
}
extern char D_0061F618[];
extern char D_0062A278[];
extern float D_00720170[];
extern int targetMemo;
extern int D_0063B854;
extern int D_0063B85C;
extern int D_0063B860;
extern int D_0063B864;
extern int D_0063B868;

extern int debug_SelectCsvWindow(char *title, int a1, int a2, int a3, void *tbl,
                                 int stride, int a6, int a7, int count, int *cur);
extern void DeleteParticleEffect(int id);
extern int SetParticleEffect(int id, void *pos, void *quat);
extern int EditTarget(int idx);
extern void moveEffectToolGeometry(int idx);
extern void dispEffectToolField(int idx);
extern int saveEffectData(int idx);

int execEffectTool(void)
{
    int q[4];
    int r;

    switch (targetMemo) {
    default:
    case 0:
        r = debug_SelectCsvWindow(D_0061F618, 10, 0x32, 0xB, D_0062A278, 0x50, 0, 0,
                                  0x3D, &D_0063B85C);
        if (D_0063B85C != D_0063B860) {
            setQ(q);
            if (D_0063B854 != -1) {
                DeleteParticleEffect(D_0063B854);
            }
            D_0063B854 = SetParticleEffect(D_0063B85C, D_00720170, q);
            D_0063B860 = D_0063B85C;
            D_0063B864 = 0;
        }
        if (D_0028F8F0[1].trg & 0x10) {
            saveEffectData(D_0063B85C);
        }
        if (D_0028F8F0[1].trg & 0x20) {
            r = 1;
        }
        if (D_0028F8F0[1].rep & 0x1000) {
            D_0063B85C--;
            if (D_0063B85C < 0) {
                D_0063B85C = 0x3C;
            }
        }
        if (D_0028F8F0[1].rep & 0x4000) {
            D_0063B85C++;
            if (D_0063B85C >= 0x3D) {
                D_0063B85C = 0;
            }
        }
        if (r == 1) {
            r = 0;
            targetMemo++;
        }
        break;
    case 1:
        r = EditTarget(D_0063B85C);
        if (r == -1) {
            targetMemo--;
        }
        r = 0;
        break;
    }
    moveEffectToolGeometry(D_0063B85C);
    if ((D_0028F8F0[0].trg & 0x80) || (D_0028F8F0[1].trg & 0x80)) {
        D_0063B868 = (D_0063B868 == 0);
    }
    if (D_0063B868) {
        dispEffectToolField(D_0063B85C);
    }
    return r;
}
extern void Camctrl_SetTarget(int x, int y, int z);
extern int D_0063AA08;
extern int D_0063B854;
extern int D_0063B86C;
extern char D_0063B878[];
extern void DeleteParticleEffect(int x);
extern void debug_StdPrintfDummy(char *fmt, ...);

void exitEffectTool(void)
{
    DeleteParticleEffect(D_0063B854);
    D_0063B854 = -1;
    Camctrl_SetTarget(D_0063B86C, 0, 3);
    D_0063AA08 = 0;
    debug_StdPrintfDummy(D_0063B878);
}
extern char D_0061F520[];
extern float D_00720170[];
extern int D_00720070[];
extern int D_0063B880;
extern int D_0063B868;
extern int D_0063B860;
extern int D_0063B864;
extern int CameraGetTarget(void);
extern void GetRootPosition(void *dst, int gobj);
extern void GetRootQuaternion(void *dst, int gobj);
extern void CameraSetMode(int mode);
extern int execEffectTool(void);

/* static helper the PAL listing places at effectTool.c lines 403-415 and
 * inlines at the head of EffectTool; never emitted out of line, so it has no
 * MAIN.MAP symbol and this name is ours. */
static inline void initEffectTool(void)
{
    int q[4];
    int i;

    setQ(q);
    D_0063B86C = CameraGetTarget();
    GetRootPosition(D_00720170, D_0063B86C);
    D_00720170[3] = 1.0f;
    GetRootQuaternion(q, D_0063B86C);
    CameraSetMode(1);
    D_0063AA08 = 1;
    debug_StdPrintfDummy(D_0061F520);
    for (i = 0x3C; i >= 0; i--) {
        D_00720070[i] = 0;
    }
}

int EffectTool(void)
{
    int r;

    if (D_0063B880 == 0) {
        initEffectTool();
        D_0063B880 = 1;
        D_0063B868 = 1;
    }
    r = execEffectTool();
    if (r == -1) {
        exitEffectTool();
        D_0063B880 = 0;
        D_0063B860 = r;
        D_0063B864 = 0;
    }
    return r;
}
