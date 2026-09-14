#include "common.h"

typedef struct {
    float f0;
    float f4;
    float f8;
} AudFrame;

typedef struct {
    float f0;
    float f4;
    float f8;
} LoadImg;

typedef struct {
    long long a;
    long long b;
} Blk16;

typedef union {
    int i;
    float f;
} SEVal;

typedef struct {
    SEVal unk00;
    SEVal flags;      /* 0x04 */
    char unk08[0x10]; /* 0x08 */
    SEVal vol;        /* 0x18 */
    SEVal pitch;      /* 0x1C */
    char unk20[0x14]; /* 0x20 */
    float *pos;       /* 0x34 */
    int unk38;        /* 0x38 */
    int *mail;        /* 0x3C */
} SEObj;

extern float D_0063C080[]; /* .sdata FLT_MAX; %hi/%lo, so the declaration withheld its size */
extern int D_00639EA4;
extern int gflagChk(int a0);
extern int *GetCameraPos();
extern int *isysGObjSearchFromObjKindID_begin(int kind);
extern int *isysGObjSearchFromObjKindID_next(int *g);
extern int *GetBoyWeaponGObj(void);
extern int *GetTorchGObjOfWeapon(int *w);
extern int IsTorchLightOn(int *g);
extern void GetRootPosition(void *dst, int *g);
extern void sceVu0SubVector(void *a0, void *a1, void *a2);
extern float sceVu0InnerProduct(void *a0, void *a1);
extern void sceVu0CopyVector(void *a0, void *a1);

int stageSEtaimatsu(SEObj *self)
{
    Blk16 v;
    Blk16 d;
    int *g = isysGObjSearchFromObjKindID_begin(10);
    int *best = 0;
    int *torch = 0;
    float bd = D_0063C080[0];
    int rv = 1;
    float *campos;
    int i;

    if (gflagChk(0x185)) {
        return 0;
    }
    campos = (float *)GetCameraPos();
    self->pitch.f = 0.5f;
    if (D_00639EA4 != 0) {
        int *w = GetBoyWeaponGObj();

        if (w != 0) {
            torch = GetTorchGObjOfWeapon(w);
        }
    }
    for (i = 0; g != 0; i++, g = isysGObjSearchFromObjKindID_next(g)) {
        int id;
        float t;

        if (IsTorchLightOn(g) == 0) {
            continue;
        }
        if (g == torch) {
            continue;
        }
        id = *self->mail;
        if ((i & 1) == 0) {
            id -= 0x1AA;
        } else {
            id -= 0x1AC;
        }
        if ((unsigned int)id >= 2) {
            continue;
        }
        GetRootPosition(&v, g);
        sceVu0SubVector(&d, campos, &v);
        t = sceVu0InnerProduct(&d, &d);
        if (t < bd) {
            bd = t;
            best = g;
        }
    }
    if (best != 0) {
        sceVu0CopyVector(self->pos, (char *)((int *)best[87])[3] + 0x30);
    } else {
        rv = 0;
    }
    return rv;
}

extern int *GetCameraPos();
extern int gflagChk(int a0);
extern int stage_no;
extern float D_0063C5B8;
extern float D_0063C5BC;
extern float D_0063C5C0;
extern float D_0063C088;

/* the river fade-out the PAL listing places at stageSEProc.c lines 397-401 and
 * inlines into stageSE04eriver (twice) and stageSE06ariver; it is not emitted
 * out of line, so it has no MAIN.MAP symbol and this name is ours. */
static inline int SEFadeOut(char *a0, float *lvl)
{
    float v = *lvl - D_0063C088;

    *lvl = v;
    *(float *)(a0 + 0x18) = v;
    if (0.0f < v) {
        return 1;
    }
    *(float *)(a0 + 0x18) = 0.0f;
    *lvl = 0.0f;
    return 0;
}

int stageSE04eriver(SEObj *a0)
{
    float *p = (float *)GetCameraPos();
    float z = p[2];
    float r;

    if (stage_no == 0x15) {
        if (gflagChk(0xE6)) {
            return SEFadeOut((char *)a0, &D_0063C5B8);
        }
        D_0063C5B8 = 1.0f;
    } else {
        if (gflagChk(0xE7)) {
            return SEFadeOut((char *)a0, &D_0063C5BC);
        }
        D_0063C5BC = 1.0f;
    }
    if (-5500.0f < z) {
        if (z < -5500.0f) {
            r = 0.0f;
        } else if (-2000.0f < z) {
            r = 1.0f;
        } else {
            r = (z - -5500.0f) / 3500.0f;
        }
        a0->vol.f = 1.0f - r;
    } else {
        if (z < -5750.0f) {
            r = 0.0f;
        } else if (-5500.0f < z) {
            r = 1.0f;
        } else {
            r = (z - -5750.0f) / 250.0f;
        }
        a0->vol.f = r;
    }
    if (a0->vol.f < 0.5f && p[1] < -1000.0f && -6500.0f < p[2]) {
        a0->vol.f = 0.5f;
    }
    return -1;
}

int stageSE06ariver(SEObj *a0)
{
    float *p = (float *)GetCameraPos();

    if (gflagChk(0x6A)) {
        return SEFadeOut((char *)a0, &D_0063C5C0);
    }
    D_0063C5C0 = 1.0f;
    if (p[0] < 300.0f && 848.0f < p[2]) {
        if (gflagChk(0x6B) == 0) {
            a0->vol.f = 0.05f;
        } else {
            a0->vol.f = 0.4f;
        }
        a0->pitch.f = 0.1f;
        a0->pos[0] = -490.0f;
        a0->pos[1] = -757.0f;
        a0->pos[2] = 759.0f;
        return 1;
    }
    a0->vol.f = 0.7f;
    a0->flags.i &= 0xEFFFFFFF;
    a0->pitch.f = 0.75f;
    a0->pos[0] = 740.0f;
    a0->pos[1] = p[1];
    a0->pos[2] = p[2];
    return 1;
}

extern int frame_count;
extern float D_0063C078;
extern int D_0063C07C;
extern int *GetCameraPos();
extern float GetRegularizedWindSpeed(void *a0);
extern int scpTriggerPosBox(int a, Blk16 *b, Blk16 *c);
extern Blk16 D_00623130;
extern Blk16 D_00623140;

int stageSE10lstrong2(char *a0)
{
    Blk16 b1;
    Blk16 b2;
    float *p = (float *)GetCameraPos();
    float f;
    float w;

    if (p[1] < 227.0f) {
        f = 0.0f;
    } else if (1000.0f < p[1]) {
        f = 1.0f;
    } else {
        f = (p[1] - 227.0f) / 773.0f;
    }
    *(float *)(a0 + 0x18) = f;
    if (f < 0.2f) {
        *(float *)(a0 + 0x18) = 0.2f;
    }
    if (D_0063C07C == frame_count) {
        w = D_0063C078;
    } else {
        float e;
        D_0063C07C = frame_count;
        e = GetRegularizedWindSpeed((void *)GetCameraPos());
        e = e * 0.5f + 0.5f;
        D_0063C078 = e;
        w = e;
    }
    *(float *)(a0 + 0x18) = *(float *)(a0 + 0x18) * w;
    b1 = D_00623130;
    b2 = D_00623140;
    if (scpTriggerPosBox((int)p, &b1, &b2) != 0) {
        *(float *)(a0 + 0x18) = *(float *)(a0 + 0x18) * 0.5f;
    }
    return -1;
}

typedef struct {
    Blk16 a;
    Blk16 b;
} Blk32;

extern int frame_count;
extern float D_0063C078;
extern int D_0063C07C;
extern int *GetCameraPos();
extern float GetRegularizedWindSpeed(void *a0);
extern void sceVu0SubVector(void *a0, void *a1, void *a2);
extern float sceVu0InnerProduct(void *a0, void *a1);
extern void sceVu0CopyVector(void *a0, void *a1);
extern Blk32 D_006230F0;
extern float D_0063C08C[];

static inline Blk16 *SENearestPoint(Blk16 *list, int n, float *limit)
{
    Blk16 d;
    Blk16 *best;
    float bd;
    void *campos;
    int i;

    best = 0;
    bd = limit[0];
    campos = (void *)GetCameraPos();
    for (i = n - 1; i != -1; i--) {
        float t;
        sceVu0SubVector(&d, campos, list);
        t = sceVu0InnerProduct(&d, &d);
        if (t < bd) {
            best = list;
            bd = t;
        }
        list++;
    }
    return best;
}

typedef struct {
    float x;
    float y;
    float z;
    float w;
} __attribute__((aligned(16))) SEVec;

extern float D_0063C084[];
extern void *memset(void *d, int c, int n);

int stageSE19ataki(SEObj *self)
{
    float *p = (float *)GetCameraPos();
    SEVec pts[6] = {
        {-1227.0f, p[1], 759.0f}, {-1194.0f, p[1], -208.0f}, {-171.0f, p[1], -1837.0f},
        {114.0f, p[1], -1526.0f}, {114.0f, p[1], -1526.0f},  {-987.0f, p[1], -2788.0f},
    };

    self->pitch.f = 0.8f;
    self->flags.i &= 0xEFFFFFFF;
    sceVu0CopyVector(self->pos, SENearestPoint((Blk16 *)pts, 6, D_0063C084));
    return 1;
}

int stageSE02astrong(char *a0)
{
    Blk32 v;
    float w;

    v = D_006230F0;
    sceVu0CopyVector(*(void **)(a0 + 0x34), SENearestPoint((Blk16 *)&v, 2, D_0063C08C));
    if (D_0063C07C == frame_count) {
        w = D_0063C078;
    } else {
        D_0063C07C = frame_count;
        w = GetRegularizedWindSpeed((void *)GetCameraPos());
        w = w * 0.5f + 0.5f;
        D_0063C078 = w;
    }
    *(float *)(a0 + 0x18) = w;
    return 1;
}

extern int gflagChk(int a0);

int stageSE02ataki(char *self)
{
    float *p = *(float **)(self + 0x34);
    p[0] = 785.0f;
    p[2] = 482.0f;
    *(float *)(self + 0x1C) = 0.5f;
    if (gflagChk(0x6A)) {
        *(int *)(self + 0x18) = 0;
    }
    return 1;
}

int stageSE02atakib(char *self)
{
    float *p = *(float **)(self + 0x34);
    p[0] = 785.0f;
    p[1] = 1786.0f;
    p[2] = 482.0f;
    *(float *)(self + 0x1C) = 0.5f;
    if (gflagChk(0x6A)) {
        *(int *)(self + 0x18) = 0;
    }
    return 1;
}

extern int GetCameraGroupCurrent(void);

int stageSE03tsuiro(void)
{
    int r = GetCameraGroupCurrent();
    if (r == 3 || r == 9) {
        return -1;
    }
    return 0;
}

int stageSE03tnotSuiro(void)
{
    int r = GetCameraGroupCurrent();
    int busy = (r == 3 || r == 9) ? -1 : 0;
    if (busy != 0) {
        return 0;
    }
    return -1;
}

extern int frame_count;
extern float D_0063C078;
extern int D_0063C07C;
extern int *GetCameraPos();
extern float GetRegularizedWindSpeed(void *a0);

int stageSE04agate(char *a0)
{
    float x = ((float *)GetCameraPos(a0))[2];
    float ratio = 1.0f;
    float w;
    if (x < -1300.0f) {
        return 0;
    }
    if (gflagChk(0x8C) == 0) {
        return 0;
    }
    if (x < 750.0f) {
        ratio = (x - -1300.0f) / 2050.0f;
    }
    if (D_0063C07C == frame_count) {
        w = D_0063C078;
    } else {
        D_0063C07C = frame_count;
        w = GetRegularizedWindSpeed((void *)GetCameraPos());
        w = w * 0.5f + 0.5f;
        D_0063C078 = w;
    }
    *(float *)(a0 + 0x18) = ratio * w;
    return -1;
}

extern int frame_count;
extern float D_0063C078;
extern int D_0063C07C;
extern void *GetCameraPos__pn(void) __asm__("GetCameraPos");
extern float GetRegularizedWindSpeed(void *a0);

int stageSE04bstrong(void *a0)
{
    float v;
    if (D_0063C07C == frame_count) {
        v = D_0063C078;
    } else {
        D_0063C07C = frame_count;
        v = GetRegularizedWindSpeed(GetCameraPos__pn()) * 0.5f + 0.5f;
        D_0063C078 = v;
    }
    *(float *)((char *)a0 + 0x18) = v;
    return -1;
}

int stageSE04ewind(char *a0)
{
    float x = ((float *)GetCameraPos__pn())[2];
    float f;
    if (x < -5770.0f) {
        f = 0.0f;
    } else if (x > -4900.0f) {
        f = 1.0f;
    } else {
        f = (x - -5770.0f) / 870.0f;
    }
    *(float *)(a0 + 0x18) = 1.0f - f;
    return -1;
}

extern int *GetCameraPos();
extern int stage_no;

int stageSE04eriverDown(char *a0)
{
    float x = ((float *)GetCameraPos(a0))[2];
    float f;
    if (stage_no == 0x15) {
        if (gflagChk(0xE6)) {
            return 0;
        }
    } else {
        if (gflagChk(0xE7)) {
            return 0;
        }
    }
    if (x < -5770.0f) {
        f = 0.0f;
    } else if (-3680.0f < x) {
        f = 1.0f;
    } else {
        f = (x - -5770.0f) / 2090.0f;
    }
    *(float *)(a0 + 0x18) = f;
    return -1;
}

int stageSE06astrong(char *a0)
{
    float *p = (float *)GetCameraPos(a0);
    float f;
    float v;
    if (p[0] < 300.0f && 848.0f < p[2]) {
        if (p[0] < -1753.0f) {
            f = 0.0f;
        } else if (-1145.0f < p[0]) {
            f = 1.0f;
        } else {
            f = (p[0] - -1753.0f) / 608.0f;
        }
        v = (1.0f - f) * 0.3f;
        *(float *)(a0 + 0x18) = v;
        if (v < 0.05f) {
            *(float *)(a0 + 0x18) = 0.05f;
        }
        return -1;
    } else {
        float *q = *(float **)(a0 + 0x34);
        *(float *)(a0 + 0x18) = 1.0f;
        q[0] = -2400.0f;
        q[1] = p[1];
        q[2] = p[2];
        return 1;
    }
}

extern int *GetCameraPos();

int stageSE06abirdIn(int *self)
{
    float *p = (float *)GetCameraPos((int)self);
    int v0 = 0;
    if (p[0] < 300.0f) {
        if (848.0f < p[2]) {
            v0 = -1;
        }
    }
    do {
        return v0;
    } while (0);
}

int stageSE06abirdOut(int *self)
{
    int new_var;
    float *p = (float *)GetCameraPos((int)self);
    int v0 = -1;
    if (p[0] < 300.0f) {
        new_var = 2;
        if (848.0f < p[new_var]) {
            v0 = 0;
        }
    }
    do {
        return v0;
    } while (0);
}

extern int UpdateRootPosition__p4() __asm__("GetCameraPos");
extern int stageSEtaimatsu(SEObj *a0);

int stageSE06ataimatsu(int *self)
{
    float *p = (float *)UpdateRootPosition__p4((int)self);
    if (p[0] < 300.0f) {
        if (848.0f < p[2]) {
            return stageSEtaimatsu((SEObj *)self);
        }
    }
    return 0;
}

extern Blk16 D_00623110;
extern Blk16 D_00623120;
extern int scpTriggerPosBox(int a, Blk16 *b, Blk16 *c);

int stageSE08astrong(char *a0)
{
    Blk16 b1;
    Blk16 b2;
    float f;
    int ret;
    if (D_0063C07C == frame_count) {
        f = D_0063C078;
    } else {
        float e;
        D_0063C07C = frame_count;
        e = GetRegularizedWindSpeed((void *)GetCameraPos());
        e = e * 0.5f + 0.5f;
        D_0063C078 = e;
        f = e;
    }
    ret = (int)GetCameraPos();
    b1 = D_00623110;
    b2 = D_00623120;
    if (scpTriggerPosBox(ret, &b1, &b2) == 0) {
        *(float *)(a0 + 0x18) = f;
    } else {
        *(float *)(a0 + 0x18) = f * 0.05f;
    }
    return -1;
}

extern Blk16 D_00623110;
extern Blk16 D_00623120;
extern int scpTriggerPosBox(int a, Blk16 *b, Blk16 *c);

int stageSE08astrong2(char *a0)
{
    Blk16 b1;
    Blk16 b2;
    float f;
    float w;
    int ret;
    if (D_0063C07C == frame_count) {
        w = D_0063C078;
    } else {
        float e;
        D_0063C07C = frame_count;
        e = GetRegularizedWindSpeed((void *)GetCameraPos());
        e = e * 0.5f + 0.5f;
        D_0063C078 = e;
        w = e;
    }
    f = 1.0f - w;
    ret = (int)GetCameraPos();
    b1 = D_00623110;
    b2 = D_00623120;
    if (scpTriggerPosBox(ret, &b1, &b2) == 0) {
        *(float *)(a0 + 0x18) = f;
    } else {
        *(float *)(a0 + 0x18) = f * 0.05f;
    }
    return -1;
}

extern Blk16 D_00623110;
extern Blk16 D_00623120;
extern int scpTriggerPosBox(int a, Blk16 *b, Blk16 *c);

int stageSE08anoise3(int self)
{
    Blk16 b1;
    Blk16 b2;
    int ret = UpdateRootPosition__p4(self);
    b1 = D_00623110;
    b2 = D_00623120;
    if (scpTriggerPosBox(ret, &b1, &b2) == 0) {
        *(float *)(self + 0x18) = 1.0f;
    } else {
        *(float *)(self + 0x18) = 0.2f;
    }
    return -1;
}

extern Blk16 D_00623110;
extern Blk16 D_00623120;
extern int scpTriggerPosBox(int a, Blk16 *b, Blk16 *c);

int stageSE08ataimatsu(int a0)
{
    Blk16 b1;
    Blk16 b2;
    int ret = UpdateRootPosition__p4(a0);
    b1 = D_00623110;
    b2 = D_00623120;
    if (scpTriggerPosBox(ret, &b1, &b2) == 0) {
        return 0;
    }
    return stageSEtaimatsu((SEObj *)a0);
}

int stageSE08bcrane(void *a0)
{
    AudFrame *p = *(AudFrame **)((char *)a0 + 0x34);
    float f;
    p->f0 = 1148.0f;
    p->f4 = -4521.0f;
    p->f8 = 1514.0f;
    if (D_0063C07C == frame_count) {
        f = D_0063C078;
    } else {
        D_0063C07C = frame_count;
        f = GetRegularizedWindSpeed((void *)UpdateRootPosition__p4());
        f = f * 0.5f + 0.5f;
        D_0063C078 = f;
    }
    *(float *)((char *)a0 + 0x18) = f;
    return 1;
}

int stageSE08brail(void *a0)
{
    AudFrame *p = *(AudFrame **)((char *)a0 + 0x34);
    float f;
    p->f0 = -114.0f;
    p->f4 = -3679.0f;
    p->f8 = 6186.0f;
    if (D_0063C07C == frame_count) {
        f = D_0063C078;
    } else {
        D_0063C07C = frame_count;
        f = GetRegularizedWindSpeed((void *)GetCameraPos());
        f = f * 0.5f + 0.5f;
        D_0063C078 = f;
    }
    *(float *)((char *)a0 + 0x18) = f;
    return 1;
}

int stageSE09asea(char *a0)
{
    AudFrame *p = *(AudFrame **)(a0 + 0x34);
    p->f0 = 1800.0f;
    p->f4 = 585.0f;
    p->f8 = -5000.0f;
    *(float *)(a0 + 0x18) = 1.0f;
    return 1;
}

extern Blk16 D_00623130;
extern Blk16 D_00623140;

int stageSE10lstrong(char *a0)
{
    Blk16 b1;
    Blk16 b2;
    float *p = (float *)GetCameraPos();
    float f;
    float w;
    if (p[1] < 227.0f) {
        f = 0.0f;
    } else if (1000.0f < p[1]) {
        f = 1.0f;
    } else {
        f = (p[1] - 227.0f) / 773.0f;
    }
    if (D_0063C07C == frame_count) {
        w = D_0063C078;
    } else {
        float e;
        D_0063C07C = frame_count;
        e = GetRegularizedWindSpeed((void *)GetCameraPos());
        e = e * 0.5f + 0.5f;
        D_0063C078 = e;
        w = e;
    }
    *(float *)(a0 + 0x18) = (1.0f - f) * w;
    b1 = D_00623130;
    b2 = D_00623140;
    if (scpTriggerPosBox((int)p, &b1, &b2) != 0) {
        *(float *)(a0 + 0x18) = *(float *)(a0 + 0x18) * 0.5f;
    }
    return -1;
}

int stageSE10rstrong(char *a0)
{
    float x = ((float *)GetCameraPos(a0))[2];
    float f;
    if (x < -300.0f) {
        f = 0.0f;
    } else if (400.0f < x) {
        f = 1.0f;
    } else {
        f = (x - -300.0f) / 700.0f;
    }
    *(float *)(a0 + 0x18) = f * 0.3f;
    return -1;
}

int stageSE10rstrong2(int self)
{
    float f;
    if (D_0063C07C == frame_count) {
        f = D_0063C078;
    } else {
        D_0063C07C = frame_count;
        f = GetRegularizedWindSpeed((void *)GetCameraPos__pn());
        f = f * 0.5f + 0.5f;
        D_0063C078 = f;
    }
    *(float *)(self + 0x18) = f;
    return -1;
}

int stageSE13arain(char *a0)
{
    float *v1 = *(float **)(a0 + 0x34);
    v1[0] = 118.0f;
    v1[1] = -192.0f;
    v1[2] = -46.0f;
    *(float *)(a0 + 0x1C) = 0.5f;
    return 1;
}

int stageSE13cNoise(int a0)
{
    float *v1 = *(float **)(a0 + 0x34);

    v1[0] = -133.0f;
    v1[1] = -5698.0f;
    v1[2] = -966.0f;
    return 1;
}

/* INTERIM (see the iosThreadCreate note in ios/thread.c): the listing inlines
   stageSE13dterrace into stageSE13dstrong, so it is `inline` in the dev's TU;
   while this tail still has asm members a deferred inline would land at the
   object end instead of here, so the public body stays a plain definition at
   its ROM position and stageSE13dstrong calls the static stand-in below.
   Collapses to one `inline` definition at layout. */
int stageSE13dterrace(void)
{
    float *p = (float *)GetCameraPos();
    if (p[1] > -1000.0f)
        return 0;
    return -1;
}

static inline int stageSE13dterrace_(void)
{
    float *p = (float *)GetCameraPos();
    if (p[1] > -1000.0f)
        return 0;
    return -1;
}

extern void soundReverbDepthSet(int a0);

int stageSE13dstrong(char *a0)
{
    int r = stageSE13dterrace_();
    float f;
    if (D_0063C07C == frame_count) {
        f = D_0063C078;
    } else {
        float e;
        D_0063C07C = frame_count;
        e = GetRegularizedWindSpeed((void *)GetCameraPos());
        e = e * 0.5f + 0.5f;
        D_0063C078 = e;
        f = e;
    }
    *(float *)(a0 + 0x18) = 1.0f - f * 0.5f;
    if (r == -1) {
        soundReverbDepthSet(20);
    }
    return r;
}

int stageSE17astrong(int self)
{
    float f;
    GetCameraPos(self);
    if (D_0063C07C == frame_count) {
        f = D_0063C078;
    } else {
        D_0063C07C = frame_count;
        f = GetRegularizedWindSpeed((void *)GetCameraPos());
        f = f * 0.5f + 0.5f;
        D_0063C078 = f;
    }
    *(float *)(self + 0x18) = f;
    return -1;
}

int stageSE18awind(char *a0)
{
    float x = ((float *)GetCameraPos(a0))[0];
    float f;
    if (x < -1000.0f) {
        f = 0.0f;
    } else if (1125.0f < x) {
        f = 1.0f;
    } else {
        f = (x - -1000.0f) / 2125.0f;
    }
    *(float *)(a0 + 0x18) = f * 0.7f;
    return -1;
}

int stageSE17brain(char *a0)
{
    float x = ((float *)GetCameraPos(a0))[0];
    float f;
    if (x < -5500.0f) {
        f = 0.0f;
    } else if (-3800.0f < x) {
        f = 1.0f;
    } else {
        f = (x - -5500.0f) / 1700.0f;
    }
    *(float *)(a0 + 0x18) = 1.0f - f;
    return -1;
}

int stageSE17bstrong(char *a0)
{
    float x = ((float *)GetCameraPos(a0))[0];
    float f;
    float w;
    if (x < -5500.0f) {
        f = 0.0f;
    } else if (-3800.0f < x) {
        f = 1.0f;
    } else {
        f = (x - -5500.0f) / 1700.0f;
    }
    *(float *)(a0 + 0x18) = 1.0f - f;
    if (D_0063C07C == frame_count) {
        w = D_0063C078;
    } else {
        float e;
        D_0063C07C = frame_count;
        e = GetRegularizedWindSpeed((void *)GetCameraPos());
        e = e * 0.5f + 0.5f;
        D_0063C078 = e;
        w = e;
    }
    *(float *)(a0 + 0x18) = *(float *)(a0 + 0x18) * w;
    return -1;
}

int stageSE17btaki(char *self)
{
    float a, b;
    float *p = *(float **)(self + 0x34);
    a = -5136.0f;
    b = 1518.0f;
    p[0] = a;
    p[2] = b;
    return 1;
}

int stageSE19astrong(void *a0)
{
    float *p = *(float **)((char *)a0 + 0x34);
    float f;
    p[0] = 1548.0f;
    p[2] = -3296.0f;
    if (D_0063C07C == frame_count) {
        f = D_0063C078;
    } else {
        D_0063C07C = frame_count;
        f = GetRegularizedWindSpeed(GetCameraPos__pn());
        f = f * 0.5f + 0.5f;
        D_0063C078 = f;
    }
    *(float *)((char *)a0 + 0x18) = f;
    return 1;
}

int stageSE19arain(int *self)
{
    float *p = (float *)self[0xD];
    register float a = 3190.0f;
    register float b = 3163.0f;
    register float c = -1332.0f;
    p[0] = a;
    p[1] = b;
    p[2] = c;
    return 1;
}

int stageSE20astrong(void *a0)
{
    float *p = *(float **)((char *)a0 + 0x34);
    float f;
    float a = -746.0f, b = -685.0f;
    p[0] = a;
    p[1] = b;
    p[2] = -398.0f;
    if (D_0063C07C == frame_count) {
        f = D_0063C078;
    } else {
        D_0063C07C = frame_count;
        f = GetRegularizedWindSpeed(GetCameraPos__pn());
        f = f * 0.5f + 0.5f;
        D_0063C078 = f;
    }
    *(float *)((char *)a0 + 0x18) = f;
    return 1;
}

int stageSE20astrong2(void *a0)
{
    float f;
    if (D_0063C07C == frame_count) {
        f = D_0063C078;
    } else {
        D_0063C07C = frame_count;
        f = GetRegularizedWindSpeed(GetCameraPos__pn());
        f = f * 0.5f + 0.5f;
        D_0063C078 = f;
    }
    *(float *)((char *)a0 + 0x18) = f;
    return -1;
}

extern int frame_count;
extern float D_0063C078;
extern int D_0063C07C;
extern void *GetCameraPos__pn(void) __asm__("GetCameraPos");
extern float GetRegularizedWindSpeed(void *a0);

int stageSE22astrong(void *a0)
{
    float f;
    if (D_0063C07C == frame_count) {
        f = D_0063C078;
    } else {
        float e;
        D_0063C07C = frame_count;
        e = GetRegularizedWindSpeed(GetCameraPos__pn());
        e = e * 0.5f + 0.5f;
        D_0063C078 = e;
        f = e;
    }
    *(float *)((char *)a0 + 0x18) = 1.0f - f * 0.5f;
    return -1;
}

int stageSE22arain(char *a0)
{
    float x = ((float *)GetCameraPos(a0))[2];
    float f;
    if (x < -8000.0f) {
        f = 0.0f;
    } else if (-1355.0f < x) {
        f = 1.0f;
    } else {
        f = (x - -8000.0f) / 6645.0f;
    }
    *(float *)(a0 + 0x18) = f;
    if (f < 0.3f) {
        *(float *)(a0 + 0x18) = 0.3f;
    }
    return -1;
}

int stageSE24astrong(void *a0)
{
    float f;
    if (D_0063C07C == frame_count) {
        f = D_0063C078;
    } else {
        D_0063C07C = frame_count;
        f = GetRegularizedWindSpeed(GetCameraPos__pn());
        f = f * 0.5f + 0.5f;
        D_0063C078 = f;
    }
    *(float *)((char *)a0 + 0x18) = f;
    return -1;
}

unsigned int stageSE24arain(char *a0)
{
    LoadImg *p = *(LoadImg **)(a0 + 0x34);
    p->f0 = 1771.0f;
    p->f8 = -4949.0f;
    *(float *)(a0 + 0x1C) = 0.5f;
    return 1;
}

int stageSE24ariver(char *self)
{
    float a, b;
    float *p = *(float **)(self + 0x34);
    a = 1478.0f;
    b = 1484.0f;
    p[0] = a;
    p[2] = b;
    return 1;
}

int stageSE47anoise(char *a0)
{
    float x = ((float *)GetCameraPos(a0))[1];
    float f;
    if (x < -3422.0f) {
        f = 0.0f;
    } else if (-122.0f < x) {
        f = 1.0f;
    } else {
        f = (x - -3422.0f) / 3300.0f;
    }
    *(float *)(a0 + 0x18) = 1.0f - f;
    return -1;
}
