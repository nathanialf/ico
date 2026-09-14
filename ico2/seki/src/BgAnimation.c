#include "common.h"
#include "vu0.h"

/* .data — carved VMA 0x4EE5B0..0x4EE5F0, bytes verified against
   baserom/pal/baseelf.rom.  D_004EE5B0 is the 0x30-byte default record
   bga_InitData block-copies into its mallocseki() allocation (two
   (0,0,0,1.0f) vectors then four words); D_004EE5E0 is the (0,0,0,1.0f)
   position vector bga_ApplyDObject hands to
   SetParticleEffectActiveSensing. */
unsigned int D_004EE5B0[12] = {
    0x00000000, 0x00000000, 0x00000000, 0x3F800000, 0x00000000, 0x00000000,
    0x00000000, 0x3F800000, 0x00000000, 0xFFFFFFFF, 0x00000001, 0x00000000,
};

float D_004EE5E0[4] = {0.0f, 0.0f, 0.0f, 1.0f};

INCLUDE_ASM("asm/nonmatchings/ico2/seki/src/BgAnimation", bga_InitData);

struct BgaEnvEnt;

struct BgaLightEnv;

typedef struct BgaDObjEnt {
    /* 0x00 */ unsigned short type;
    /* 0x02 */ short num;
    /* 0x04 */ char name[0x20];
    /* 0x24 */ union {
        void *obj;                 /* particle record, geometry, Kyomi object */
        struct BgaLightEnv *light; /* ambient-light record */
    } u;
    /* 0x28 */ struct BgaEnvEnt *env;
    /* 0x2C */ struct BgaDObjEnt *f2C;
    /* 0x30 */ struct BgaDObjEnt *f30;
} BgaDObjEnt;

typedef struct BgaGeom {
    /* 0x000 */ int f00;
    /* 0x004 */ int f04;
    /* 0x008 */ int f08;
    /* 0x00C */ char pad0C[0x848];
    /* 0x854 */ char *name;
} BgaGeom;

typedef struct BgaGObj {
    /* 0x000 */ char pad00[0x15C];
    /* 0x15C */ void *geom;
} BgaGObj;

/* The particle entry's word at +0x20 packs three fields: the loop flag in
   bits 0-1, the effect handle in bits 2-16 and the particle id in bits
   17-31.  The union with the 8-byte word is what the record is: the ROM
   reads and writes the whole doubleword (ld/sd) at every one of these
   sites, and the int bitfields inside it give the sign-extending 15-bit
   extraction the ROM uses for the id. */
typedef union BgaParticleBits {
    struct {
        int loop : 2;
        int eff : 15;
        int id : 15;
    } b;

    long long w;
} BgaParticleBits;

typedef struct BgaParticleEnt {
    /* 0x00 */ char pad00[0x20];
    /* 0x20 */ BgaParticleBits u;
} BgaParticleEnt;

extern int D_0063A44C;
extern char D_00621598[];
extern char D_00621638[];
extern char D_00621658[];
extern char D_0063BCF0[];
extern char D_0063BCE8[];
extern int D_002907E0[];
extern int GetParticleIDWithName(char *name);
extern void *iosMallocDebug(int heap, int size, char *file, int line);
extern int GetParticleLoopFlag(int id);
extern int SetParticleEffectActiveSensing(int id, float *pos, int *quat);
extern int sprintf(char *buf, char *fmt, ...);
extern void debug_assertMessage(char *file, int line, char *mes);
extern int strcmp(const char *a, const char *b);
extern void *light_AddAmbientObject(int obj);
extern char *CreateKyomiGObj(int no);

typedef struct BgaEnvEnt {
    /* 0x00 */ unsigned short type;
    /* 0x02 */ short f02;
    /* 0x04 */ unsigned char *data;
} BgaEnvEnt;

typedef struct BgaLightEnv {
    /* 0x00 */ char pad00[0x20];
    /* 0x20 */ float col[4];
    /* 0x30 */ char pad30[0x10];
    /* 0x40 */ float col2[4];
    /* 0x50 */ float f50;
    /* 0x54 */ float f54;
    /* 0x58 */ float f58;
    /* 0x5C */ int f5C;
    /* 0x60 */ float f60;
    /* 0x64 */ float f64;
    /* 0x68 */ float f68;
} BgaLightEnv;

extern char D_006215F8[];
extern char D_00621618[];
extern void debug_Assert(char *fmt, ...);

void bga_initLightEnvelope(BgaDObjEnt *p)
{
    BgaEnvEnt *e;
    unsigned char *d;

    e = p->env;
    if (e == 0) {
        return;
    }
    while ((d = e->data) != 0) {
        switch (e->type) {
        case 4:
            switch (p->type) {
            case 6:
            case 11:
                if (p->u.light != 0) {
                    p->u.light->col[0] = (float)d[0] / 255.0f;
                    p->u.light->col[1] = (float)d[1] / 255.0f;
                    p->u.light->col[2] = (float)d[2] / 255.0f;
                    p->u.light->col[3] = 1.0f;
                } else {
                    debug_Assert(D_006215F8);
                    debug_assert(D_00621598, 1089);
                    __assert(D_00621598, 1089, D_0063BCE8);
                }
                break;
            case 7:
            case 8:
            case 9:
                if (p->u.light != 0) {
                    p->u.light->col2[0] = (float)d[0] / 255.0f;
                    p->u.light->col2[1] = (float)d[1] / 255.0f;
                    p->u.light->col2[2] = (float)d[2] / 255.0f;
                    p->u.light->col2[3] = 1.0f;
                } else {
                    debug_Assert(D_00621618);
                    debug_assert(D_00621598, 1109);
                    __assert(D_00621598, 1109, D_0063BCE8);
                }
                break;
            }
            break;
        case 5:
            switch (p->type) {
            case 8:
            case 9:
                if (p->u.light != 0) {
                    p->u.light->f50 = 1.0f / (((float *)d)[0] * 50.0f);
                    p->u.light->f54 = 1.0f / (((float *)d)[1] * 50.0f);
                    p->u.light->f58 = 1.0f / (((float *)d)[2] * 50.0f);
                    p->u.light->f60 = 1.0f / (((float *)d)[3] * 50.0f);
                    p->u.light->f64 = 1.0f / (((float *)d)[4] * 50.0f);
                    p->u.light->f68 = 1.0f / (((float *)d)[5] * 50.0f);
                } else {
                    debug_assert(D_00621598, 1141);
                    __assert(D_00621598, 1141, D_0063BCE8);
                }
                break;
            }
            break;
        /* A third arm above 5 with an empty body: the ROM's dispatch is the
           three-test tree balance_case_nodes only builds for more than two
           case values (== 5, then >= 6 to the default, then == 4), and jump
           optimisation then deletes this arm's own test because its label is
           the switch end.  That makes the value itself unobservable; 6 is the
           next envelope type. */
        case 6:
            break;
        }
        e++;
    }
}

void bga_ApplyDObject(BgaDObjEnt *p, void **objs, int n, int no)
{
    char buf[1024];
    int i;

    switch (p->type) {
    case 13:
        i = GetParticleIDWithName(p->name);
        if (i != -1) {
            p->u.obj = iosMallocDebug(D_0063A44C, 0x30, D_00621598, 1177);
            ((BgaParticleEnt *)p->u.obj)->u.b.id = i;
            ((BgaParticleEnt *)p->u.obj)->u.b.loop =
                GetParticleLoopFlag(((BgaParticleEnt *)p->u.obj)->u.b.id);
            if (((BgaParticleEnt *)p->u.obj)->u.b.loop) {
                ((BgaParticleEnt *)p->u.obj)->u.b.eff = SetParticleEffectActiveSensing(
                    ((BgaParticleEnt *)p->u.obj)->u.b.id, D_004EE5E0, D_002907E0);
            } else {
                ((BgaParticleEnt *)p->u.obj)->u.b.eff = -1;
            }
            break;
        }
    case 1:
    case 2:
    case 5:
        p->u.obj = 0;
        break;
    case 0:
    case 4:
    case 10:
        p->u.obj = 0;
        for (i = 0; i < n; i++) {
            if (((BgaGeom *)((BgaGObj *)objs[i])->geom)->name == 0) {
                sprintf(buf, D_00621638, p->name);
                debug_StdPrintfDummy(D_00621658, p->name);
                debug_assertMessage(D_00621598, 1201, buf);
                __assert(D_00621598, 1201, D_0063BCF0);
            }
            if (strcmp(((BgaGeom *)((BgaGObj *)objs[i])->geom)->name, p->name) == 0) {
                p->u.obj = ((BgaGObj *)objs[i])->geom;
                p->num = ((BgaGeom *)((BgaGObj *)objs[i])->geom)->f08++;
            }
        }
        break;
    case 7:
        p->u.obj = light_AddAmbientObject(0);
        bga_initLightEnvelope(p);
        break;
    case 8:
        p->u.obj = light_AddAmbientObject(2);
        bga_initLightEnvelope(p);
        break;
    case 9:
        p->u.obj = light_AddAmbientObject(1);
        bga_initLightEnvelope(p);
        break;
    case 12:
        p->u.obj = CreateKyomiGObj(no);
        break;
    }
    if (p->f2C) {
        bga_ApplyDObject(p->f2C, objs, n, no);
    }
    if (p->f30) {
        bga_ApplyDObject(p->f30, objs, n, no);
    }
}

ASM_LIT4_SLOT(D_00639724, 1.2075409f);
ASM_LIT4_SLOT(D_00639728, 182.04445f);
ASM_LIT4_SLOT(D_0063972C, 182.04445f);
ASM_LIT4_SLOT(D_00639730, 0.1f);
ASM_LIT4_SLOT(D_00639734, 182.04445f);
INCLUDE_ASM("asm/nonmatchings/ico2/seki/src/BgAnimation", bga_GetMotion);
ASM_LIT4_SLOT(D_00639738, 1.2075409f);
ASM_LIT4_SLOT(D_0063973C, 182.04445f);
ASM_LIT4_SLOT(D_00639740, 182.04445f);
ASM_LIT4_SLOT(D_00639744, 182.04445f);
INCLUDE_ASM("asm/nonmatchings/ico2/seki/src/BgAnimation", bga_GetMotionParticle);
ASM_LIT4_SLOT(D_00639748, 1.2075409f);
ASM_LIT4_SLOT(D_0063974C, 182.04445f);
ASM_LIT4_SLOT(D_00639750, 182.04445f);
ASM_LIT4_SLOT(D_00639754, 0.1f);
ASM_LIT4_SLOT(D_00639758, 182.04445f);
INCLUDE_ASM("asm/nonmatchings/ico2/seki/src/BgAnimation", bga_GetMotionLightning);
ASM_LIT4_SLOT(D_0063975C, 1.2075409f);
INCLUDE_ASM("asm/nonmatchings/ico2/seki/src/BgAnimation", bga_GetExtMotion);
ASM_LIT4_SLOT(D_00639760, 1.2075409f);
INCLUDE_ASM("asm/nonmatchings/ico2/seki/src/BgAnimation", bga_GetGizmoMotion);
ASM_LIT4_SLOT(D_00639764, 0.82812935f);
ASM_LIT4_SLOT(D_00639768, 2.66f);
ASM_LIT4_SLOT(D_0063976C, 0.82812935f);
ASM_LIT4_SLOT(D_00639770, 0.82812935f);
INCLUDE_ASM("asm/nonmatchings/ico2/seki/src/BgAnimation", bga_calcEnvelope);

extern float GetTableCos(short a);
extern float _Sqrt(float x);

/* The rotation is applied Y, then X, then Z, with the three sines derived
   from the cosines (sin = sign(angle) * sqrt(1 - cos^2)) instead of a second
   table lookup.  The VU0 block is the _TransCurrentMatrix body followed by
   the three _RotCurrentMatrix* bodies with the cos/sin pairs already in
   $vf21..$vf26; $vf27..$vf29 hold the vmr32 chain so it is built once. */
void _RotTransCurrentMatrixYXZ(void *t, int *rot)
{
    float cx, cy, cz, sx, sy, sz;

    cx = GetTableCos(rot[0]);
    cy = GetTableCos(rot[1]);
    cz = GetTableCos(rot[2]);
    {
        float q = _Sqrt(1.0f - cx * cx);
        if (rot[0] < 0.0f) {
            sx = -q;
        } else if (rot[0] > 0.0f) {
            sx = q;
        } else {
            sx = q * 0.0f;
        }
    }
    {
        float q = _Sqrt(1.0f - cy * cy);
        if (rot[1] < 0.0f) {
            sy = -q;
        } else if (rot[1] > 0.0f) {
            sy = q;
        } else {
            sy = q * 0.0f;
        }
    }
    {
        float q = _Sqrt(1.0f - cz * cz);
        if (rot[2] < 0.0f) {
            sz = -q;
        } else if (rot[2] > 0.0f) {
            sz = q;
        } else {
            sz = q * 0.0f;
        }
    }

    /* The rotation pairs go into $vf21..$vf26 while the vmr32 chain builds
       the identity rows in $vf14..$vf17.  The sequence is one asm block
       because it is hand scheduled: every mfc1 is separated from the qmtc2
       that consumes its GPR, and the three vmr32 sit in those gaps. */
    __asm__ __volatile__("vmove.xyzw $vf17, $vf0\n\t"
                         "lqc2 $vf8, 0(%6)\n\t"
                         "mfc1 $4, %0\n\t"
                         "mfc1 $5, %1\n\t"
                         "vmr32.xyzw $vf16, $vf17\n\t"
                         "mfc1 $6, %2\n\t"
                         "mfc1 $7, %3\n\t"
                         "mfc1 $8, %4\n\t"
                         "vmr32.xyzw $vf15, $vf16\n\t"
                         "mfc1 $9, %5\n\t"
                         "qmtc2.ni $4, $vf21\n\t"
                         "qmtc2.ni $5, $vf22\n\t"
                         "vmr32.xyzw $vf14, $vf15\n\t"
                         "qmtc2.ni $6, $vf23\n\t"
                         "qmtc2.ni $7, $vf24\n\t"
                         "qmtc2.ni $8, $vf25\n\t"
                         "qmtc2.ni $9, $vf26"
                         :
                         : "f"(cy), "f"(sy), "f"(cx), "f"(sx), "f"(cz), "f"(sz), "r"(t)
                         : "$4", "$5", "$6", "$7", "$8", "$9", "memory");
    VU0_V3OP_ACC_BC(vmulax.xyzw, 4, 8, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 5, 8, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 6, 8, z);
    VU0_V2OP(vmove.xyzw, 27, 14);
    VU0_V2OP(vmove.xyzw, 29, 16);
    VU0_V3OP_BC(vaddx.x, 14, 0, 21, x);
    VU0_V3OP_BC(vaddx.x, 16, 0, 22, x);
    VU0_V3OP_BC(vmaddw.xyzw, 7, 7, 8, w);
    VU0_V2OP(vmove.xyzw, 28, 15);
    VU0_V3OP_BC(vsubx.z, 14, 0, 22, x);
    VU0_V3OP_BC(vaddx.z, 16, 0, 21, x);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 4, 14, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 5, 14, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 6, 14, z);
    VU0_V3OP_BC(vmaddw.xyzw, 10, 7, 14, w);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 4, 15, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 5, 15, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 6, 15, z);
    VU0_V3OP_BC(vmaddw.xyzw, 11, 7, 15, w);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 4, 16, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 5, 16, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 6, 16, z);
    VU0_V3OP_BC(vmaddw.xyzw, 12, 7, 16, w);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 4, 17, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 5, 17, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 6, 17, z);
    VU0_V3OP_BC(vmaddw.xyzw, 13, 7, 17, w);
    VU0_V2OP(vmove.xyzw, 15, 28);
    VU0_V2OP(vmove.xyzw, 16, 29);
    VU0_V2OP(vmove.xyzw, 14, 27);
    VU0_V2OP(vmove.xyzw, 17, 0);
    VU0_V3OP_BC(vaddx.y, 15, 0, 23, x);
    VU0_V3OP_BC(vsubx.y, 16, 0, 24, x);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 10, 14, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 11, 14, y);
    VU0_V3OP_BC(vaddx.z, 15, 0, 24, x);
    VU0_V3OP_BC(vaddx.z, 16, 0, 23, x);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 12, 14, z);
    VU0_V3OP_BC(vmaddw.xyzw, 4, 13, 14, w);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 10, 15, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 11, 15, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 12, 15, z);
    VU0_V3OP_BC(vmaddw.xyzw, 5, 13, 15, w);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 10, 16, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 11, 16, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 12, 16, z);
    VU0_V3OP_BC(vmaddw.xyzw, 6, 13, 16, w);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 10, 17, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 11, 17, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 12, 17, z);
    VU0_V3OP_BC(vmaddw.xyzw, 7, 13, 17, w);
    VU0_V2OP(vmove.xyzw, 14, 27);
    VU0_V2OP(vmove.xyzw, 15, 28);
    VU0_V2OP(vmove.xyzw, 16, 29);
    VU0_V2OP(vmove.xyzw, 17, 0);
    VU0_V3OP_BC(vaddx.x, 14, 0, 25, x);
    VU0_V3OP_BC(vsubx.x, 15, 0, 26, x);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 4, 16, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 5, 16, y);
    VU0_V3OP_BC(vaddx.y, 14, 0, 26, x);
    VU0_V3OP_BC(vaddx.y, 15, 0, 25, x);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 6, 16, z);
    VU0_V3OP_BC(vmaddw.xyzw, 12, 7, 16, w);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 4, 14, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 5, 14, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 6, 14, z);
    VU0_V3OP_BC(vmaddw.xyzw, 10, 7, 14, w);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 4, 15, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 5, 15, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 6, 15, z);
    VU0_V3OP_BC(vmaddw.xyzw, 11, 7, 15, w);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 4, 17, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 5, 17, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 6, 17, z);
    VU0_V3OP_BC(vmaddw.xyzw, 13, 7, 17, w);
    VU0_V2OP(vmove.xyzw, 4, 10);
    VU0_V2OP(vmove.xyzw, 5, 11);
    VU0_V2OP(vmove.xyzw, 6, 12);
    VU0_V2OP(vmove.xyzw, 7, 13);
}

ASM_LIT4_SLOT(D_00639774, 0.41406468f);
ASM_LIT4_SLOT(D_00639778, 0.82812935f);
ASM_LIT4_SLOT(D_0063977C, 0.82812935f);
INCLUDE_ASM("asm/nonmatchings/ico2/seki/src/BgAnimation", bga_CalcObject);

extern int D_0028F4C0[];

static inline float bga_palFrame(float f)
{
    if (D_0028F4C0[0]) {
        f *= 0.82812935f;
    }
    return f;
}

typedef struct {
    /* 0x00 */ int f00;
    /* 0x04 */ int f04;
    /* 0x08 */ unsigned int f08;
    /* 0x0C */ float f0C;
} BgaCount;

typedef struct {
    /* 0x00 */ int f00;
    /* 0x04 */ BgaCount *obj;
} BgaCountEnt;

typedef struct BgaCntNode {
    /* 0x00 */ char pad00[0x28];
    /* 0x28 */ BgaCountEnt *ents;
    /* 0x2C */ struct BgaCntNode *f2C;
    /* 0x30 */ struct BgaCntNode *f30;
    /* 0x34 */ BgaCount f34;
} BgaCntNode;

static inline void bga_clampCount(BgaCount *o, float f)
{
    if (f >= 0.0f) {
        float c = (float)o->f08;
        float r;

        if (D_0028F4C0[0] ? c * 0.82812935f < f : c < f) {
            float t = (float)o->f08;

            r = t;
            if (D_0028F4C0[0]) {
                r *= 0.82812935f;
            }
        } else {
            r = f;
        }
        o->f0C = r;
    } else {
        o->f0C = 0.0f;
    }
}

void bga_resetObjectCounter(BgaCntNode *o, float f, int a1)
{
    BgaCountEnt *e;

    e = o->ents;
    if (e != 0) {
        while (e->obj != 0) {
            bga_clampCount(e->obj, f);
            e++;
        }
    }
    if (o->f2C != 0) {
        bga_resetObjectCounter(o->f2C, f, a1);
    }
    if (o->f30 != 0) {
        bga_resetObjectCounter(o->f30, f, a1);
    }
    bga_clampCount(&o->f34, f);
}

ASM_LIT4_SLOT(D_00639790, 0.82812935f);
ASM_LIT4_SLOT(D_00639794, 0.82812935f);
ASM_LIT4_SLOT(D_00639798, 0.82812935f);
INCLUDE_ASM("asm/nonmatchings/ico2/seki/src/BgAnimation", bga_SetFrame);

extern int D_0063C4B4;
extern int D_0063BCBC;
extern void GetMatrixFromQuaternionPos(void *m, void *q, void *pos);
extern void _SetCurrentMatrix(void *m);
extern void GetRootMatrix(void *m, void *gobj);
extern void CopyVector(void *dst, void *src);
extern void _InitCurrentMatrix(void);
extern void _MulCurrentMatrixR(void *m);
extern int *GetCurrentQuaternion(void);
extern void CopyQuaternion(void *dst, void *src);
extern void GetRootQuaternion(void *q, void *gobj);
extern void SetIdentityQuaternion(void *q);
extern void MultiQuaternion(void *dst, void *a, void *b);
extern void PushQuaternion(void);
extern void PopQuaternion(void);
extern void _PushCurrentMatrix(void);
extern void _PopCurrentMatrix(void);
extern void bga_CalcObject(BgaCntNode *o, int a1, int a2, int a3, float frame, float end);

typedef struct BgaAnimGeom {
    /* 0x000 */ char pad00[0xC];
    /* 0x00C */ float (*mtx)[4][4];
    /* 0x010 */ float (*quat)[4];
} BgaAnimGeom;

typedef struct BgaAnimObj {
    /* 0x000 */ char pad00[0x15C];
    /* 0x15C */ BgaAnimGeom *geom;
} BgaAnimObj;

typedef struct BgaAnimEnt {
    /* 0x00 */ float pos[4];
    /* 0x10 */ float quat[4];
    /* 0x20 */ BgaAnimObj *obj;
    /* 0x24 */ int idx;
    /* 0x28 */ int root;
} BgaAnimEnt;

#define BGA_ANIM_ENT(p) (*(BgaAnimEnt **)((p) + 0x24))

void bga_CalcAnimation(char *p, int a1, int a2)
{
    float m[4][4];
    float rm[4][4];
    BgaCntNode *o;
    int i;
    int f1;
    int f2;

    if (p[0xA] == -1) {
        return;
    }

    if (p[0xB]) {
        D_0063C4B4 = 1;
    }

    GetMatrixFromQuaternionPos(m, BGA_ANIM_ENT(p)->quat, BGA_ANIM_ENT(p));
    if (BGA_ANIM_ENT(p)->obj) {
        if (BGA_ANIM_ENT(p)->root) {
            _SetCurrentMatrix(BGA_ANIM_ENT(p)->obj->geom->mtx[BGA_ANIM_ENT(p)->idx]);
        } else {
            GetRootMatrix(rm, BGA_ANIM_ENT(p)->obj);
            CopyVector(rm[3], BGA_ANIM_ENT(p)->obj->geom->mtx[BGA_ANIM_ENT(p)->idx][3]);
            _SetCurrentMatrix(rm);
        }
    } else {
        _InitCurrentMatrix();
    }
    _MulCurrentMatrixR(m);

    if (BGA_ANIM_ENT(p)->obj) {
        if (BGA_ANIM_ENT(p)->root) {
            CopyQuaternion(GetCurrentQuaternion(),
                           BGA_ANIM_ENT(p)->obj->geom->quat[BGA_ANIM_ENT(p)->idx]);
        } else {
            GetRootQuaternion(GetCurrentQuaternion(), BGA_ANIM_ENT(p)->obj);
        }
    } else {
        SetIdentityQuaternion(GetCurrentQuaternion());
    }
    MultiQuaternion(GetCurrentQuaternion(), GetCurrentQuaternion(), BGA_ANIM_ENT(p)->quat);

    for (i = 0;; i++) {
        f2 = (p[0xA] == 1);
        f1 = p[0xB] && f2;
        o = (*(BgaCntNode ***)(p + 0x10))[i];
        if (o == 0) {
            break;
        }
        PushQuaternion();
        _PushCurrentMatrix();
        if (a2 == 1) {
            bga_resetObjectCounter(o, *(float *)(p + 0x20), a1);
        }
        bga_CalcObject(o, f1, f2, a1, *(float *)(p + 0x1C), *(float *)(p + 0x20));
        _PopCurrentMatrix();
        PopQuaternion();
    }

    D_0063BCBC = (int)*(float *)(p + 0x20);
    if (a2) {
        return;
    }

    if (p[0xA] == 1) {
        float end = *(float *)(p + 0x18);

        *(float *)(p + 0x20) += *(float *)(p + 0x1C);
        if (D_0028F4C0[0] ? end * 0.82812935f < *(float *)(p + 0x20) : end < *(float *)(p + 0x20)) {
            if (a1 == 0) {
                *(float *)(p + 0x20) = bga_palFrame(*(float *)(p + 0x18));
                p[0xA] = 0;
            } else {
                *(float *)(p + 0x20) = 0.0f;
            }
        }
    }
}

ASM_LIT4_SLOT(D_006397A4, 0.82812935f);
ASM_LIT4_SLOT(D_006397A8, 0.82812935f);
ASM_LIT4_SLOT(D_006397AC, 1.2075409f);
ASM_LIT4_SLOT(D_006397B0, 1.2075409f);
ASM_LIT4_SLOT(D_006397B4, 182.04445f);
ASM_LIT4_SLOT(D_006397B8, 3.1415927f);
ASM_LIT4_SLOT(D_006397BC, 10430.378f);
INCLUDE_ASM("asm/nonmatchings/ico2/seki/src/BgAnimation", bga_CalcSdfCamera);
INCLUDE_ASM("asm/nonmatchings/ico2/seki/src/BgAnimation", bga_addLightning);
ASM_LIT4_SLOT(D_006397C0, 0.01f);
INCLUDE_ASM("asm/nonmatchings/ico2/seki/src/BgAnimation", bga_DispLightning);

extern int D_0063C4B4;

void bga_ResetCamera(void)
{
    D_0063C4B4 = 0;
}

extern int D_0063BCC0;
extern int D_0063BCC8;
extern int D_0063C4B4;
extern int D_007281F0[];
extern void _CopyMatrix(void *dst, void *src);

int bga_GetCameraMatrix(void *p)
{
    int v = D_0063C4B4;
    if (v != 0) {
        _CopyMatrix(p, D_007281F0);
        v = D_0063C4B4;
    } else {
        D_0063BCC0 = 0;
    }
    return v != 0 && D_0063BCC8 == 0;
}

extern char D_0063BCE0[];
extern char D_006215D8[];
extern char D_00621598[];
extern char D_0063BCD8[];

char *bga_InitSdfCamera(char *a0)
{
    if (strncmp(a0, D_0063BCE0, 3) != 0) {
        debug_StdPrintfDummy(D_006215D8);
        debug_assert(D_00621598, 0x415);
        __assert(D_00621598, 0x415, D_0063BCD8);
    }
    return a0;
}

extern int D_0063C4B4;
extern int D_0063BCB8;
extern int GlobalTimer;
extern float D_00728230[];
extern float D_00728220[];
extern void _CopyVector(void *dst, void *src);

void bga_SetCamFrame(char *p, int frame, int mode)
{
    *(int *)(p + 0xC) = mode;
    D_0063C4B4 = 1;
    if (mode == 1) {
        GlobalTimer = mode;
        D_0063BCB8 = mode;
        _CopyVector(D_00728230, D_00728220);
    }
    if (frame == -1) {
        *(float *)(p + 8) = bga_palFrame(*(int *)(p + 4));
    } else {
        *(float *)(p + 8) = bga_palFrame(frame);
    }
}

int bga_CheckAnimationFinish(char *p)
{
    float f = *(float *)(p + 0x18);
    float t = *(float *)(p + 0x20);
    int r = 0;

    if (D_0028F4C0[0]) {
        if (f * 0.82812935f <= t || p[0xA] != 1) {
            r = 1;
        }
    } else {
        if (f <= t || p[0xA] != 1) {
            r = 1;
        }
    }
    return r;
}

int bga_CheckAnimationFrame(char *p, int frame, int reset)
{
    float f = frame;
    float t = *(float *)(p + 0x20);
    int r = 0;

    if (D_0028F4C0[0]) {
        if (f * 0.82812935f <= t || p[0xA] != 1) {
            r = 1;
        }
    } else {
        if (f <= t || p[0xA] != 1) {
            r = 1;
        }
    }
    if (r && reset) {
        p[0xA] = 0;
    }
    return r;
}

int bga_CheckAnimationFrameIn(char *p, int in, int out)
{
    float a = in;
    float t = *(float *)(p + 0x20);
    int r = 0;

    if (D_0028F4C0[0] ? a * 0.82812935f <= t : a <= t) {
        float b = out;

        if (D_0028F4C0[0] ? t < b * 0.82812935f : t < b) {
            r = p[0xA] == 1;
        }
    }
    return r;
}

int bga_CheckSdfCameraFinish(char *p)
{
    float f = *(int *)(p + 4);
    float t = *(float *)(p + 8);

    if (D_0028F4C0[0]) {
        return f * 0.82812935f <= t;
    }
    return f <= t;
}

int bga_CheckSdfCameraFrame(char *p, int frame, int reset)
{
    float f = frame;
    float t = *(float *)(p + 8);
    int r;

    if (D_0028F4C0[0]) {
        r = f * 0.82812935f <= t;
    } else {
        r = f <= t;
    }
    if (r && reset) {
        *(int *)(p + 0xC) = 0;
    }
    return r;
}

int bga_CheckSdfCameraFrameIn(char *p, int in, int out)
{
    float t = *(float *)(p + 8);
    float a = in;
    int r = 0;

    if (D_0028F4C0[0] ? a * 0.82812935f <= t : a <= t) {
        float b = out;

        if (D_0028F4C0[0] ? t < b * 0.82812935f : t < b) {
            r = 1;
        }
    }
    return r;
}

void bga_SetCameraForceOff(void)
{
    D_0063BCC8 = 1;
}

extern int D_0063BCCC;

void bga_InitBGA(void)
{
    D_0063BCC8 = 0;
    D_0063BCCC = 0;
}

extern int D_0063BCC4;

void bga_SetUniqAnimationFlag(int val)
{
    D_0063BCC4 = val;
}

extern int D_0028F4D4[];
extern void freeseki(void *p);

void bga_ResetAnimation(void)
{
    void *p;
    D_0063C4B4 = 0;
    if (D_0028F4D4[0] != 0) {
        return;
    }
    p = (void *)D_0063BCCC;
    D_0063BCCC = 0;
    if (p == 0) {
        return;
    }
    do {
        void *next = *(void **)((char *)p + 0x154);
        freeseki(p);
        p = next;
    } while (p != 0);
}

extern float D_0063BCC0__pn __asm__("D_0063BCC0");

float bga_GetZoom(void)
{
    return D_0063BCC0__pn;
}
