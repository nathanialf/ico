#include "common.h"

#include "ico/types.h"

typedef struct { float f_0; float f_4; int f_8; } GFField;
typedef struct { char _0[0x34]; int f_34; char _38[0x14]; } NestEnt;
typedef struct { void *f_0; char _4[0x10]; } RotEnt;

void GirlForceFieldGeo(void) {}

void InitGirlForceFieldGeo(void *a0, int a1, int a2) {
    Obj7F0 *o = (Obj7F0 *)GOBJ_SUB(a0)->p_800;
    switch (a1) {
    case 0:
        o->f_4 = a2;
        break;
    case 1:
        o->f_C = a2;
        break;
    case 2:
        o->f_18 = a2;
        break;
    }
}

extern RotEnt D_0029F270[];
extern NestEnt D_002A4C48[];
extern void *D_00631AE8;
extern void GetRootPosition(void *dst, void *src);
extern float FSqrt(float a0);
extern void func_00102850(void *dst, void *self);
extern void func_00102858(void *a0);
extern float stage_SetParentOfGObjWithLocalRotationFlag(void *parent, void *vecA, void *vecB, float a3, float a4);

struct gff_vec { float x, y, z, w; } __attribute__((aligned(16)));

void GirlForceFieldDL(GObj *self) {
    struct gff_vec self_vec;
    struct gff_vec buf;
    struct gff_vec target_vec;
    GFField *o = ((GFField *)GOBJ_SUB(self)->p_800);
    void *tgt;

    func_00102858(self);
    GetRootPosition(&self_vec, self);
    tgt = D_00631AE8;
    if (tgt != 0) {
        float d;
        GetRootPosition(&target_vec, tgt);
        __asm__ __volatile__(
            "lqc2 $vf1, 0x0(%1)\n"
            "lqc2 $vf2, 0x0(%2)\n"
            "vsub.xyzw $vf3, $vf1, $vf2\n"
            "vmul.xyz $vf3, $vf3, $vf3\n"
            "vaddy.x $vf3, $vf3, $vf3y\n"
            "vaddz.x $vf3, $vf3, $vf3z\n"
            "qmfc2.ni $2, $vf3\n"
            "mtc1 $2, %0\n"
            : "=f"(d) : "r"(&target_vec), "r"(&self_vec) : "$2");
        if (d < o->f_0 * o->f_0) {
            float angle = FSqrt(d);
            float w = 1.0f - angle * o->f_4;
            w = (w < 0.0f) ? 0.0f : w;
            func_00102850(&buf, self);
            o->f_8 = (int)stage_SetParentOfGObjWithLocalRotationFlag(
                D_0029F270[D_002A4C48[self->f_8].f_34].f_0, &self_vec, &buf,
                (float)o->f_8, w);
        } else {
            o->f_8 = 0;
        }
    } else {
        o->f_8 = 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/src/girlForceField", func_001D1C78);

void func_001D1CF8(void) {}

INCLUDE_ASM("asm/nonmatchings/src/girlForceField", func_001D1D00);

