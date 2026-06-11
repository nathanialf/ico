#include "common.h"
#include "ico/types.h"

void GirlForceFieldGeo(void) {
}

void InitGirlForceFieldGeo(void *a0, int a1, int a2) {
    Obj7F0 *o = GOBJ_SUB(a0)->p_7F0;
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

typedef struct { float f_0; float f_4; int f_8; } GFField;

typedef struct { char _0[0x34]; int f_34; char _38[0x14]; } NestEnt;   /* 0x4C */
typedef struct { void *f_0; char _4[0x10]; } RotEnt;                    /* 0x14 */

struct gff_vec { float x, y, z, w; } __attribute__((aligned(16)));

extern void *D_00629DE8;
extern NestEnt D_002A0A90[];
extern RotEnt D_0029B128[];
extern void func_00102828(void *a0);
extern void func_00102820(void *dst, void *self);
extern void GetRootMatrixByDObj(void *dst, void *src);
extern float MatrixDrive_GetTurnYAngleXZ(float a0);
extern float stage_SetParentOfGObjWithLocalRotationFlag(void *parent, void *vecA,
                                                        void *vecB, float a3,
                                                        float a4);

void GirlForceFieldDL(GObj *self) {
    struct gff_vec self_vec;
    struct gff_vec buf;
    struct gff_vec target_vec;
    GFField *o = (GFField *)GOBJ_SUB(self)->p_7F0;
    void *tgt;

    func_00102828(self);
    GetRootMatrixByDObj(&self_vec, self);
    tgt = D_00629DE8;
    if (tgt != 0) {
        float d;
        GetRootMatrixByDObj(&target_vec, tgt);
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
            float angle = MatrixDrive_GetTurnYAngleXZ(d);
            float w = 1.0f - angle * o->f_4;
            w = (w < 0.0f) ? 0.0f : w;
            func_00102820(&buf, self);
            o->f_8 = (int)stage_SetParentOfGObjWithLocalRotationFlag(
                D_0029B128[D_002A0A90[self->f_8].f_34].f_0, &self_vec, &buf,
                (float)o->f_8, w);
        } else {
            o->f_8 = 0;
        }
    } else {
        o->f_8 = 0;
    }
}

extern int D_0062A310;
extern char D_00611830[];
extern int *iosFree(int heap, int size, const char *file, int line);

int *func_001CF010(int *self, int *src) {
    int *ret = iosFree(D_0062A310, 0xC, D_00611830, 0x17);
    float val = *(float *)((char *)src + 0x28);
    float one = 1.0f;
    int *new_var;
    int *p = ret;
    *(float *)((char *)p + 0x0) = val;
    *(int *)((char *)p + 0x8) = 0;
    val = one / val;
    *(float *)((char *)p + 0x4) = val;
    p = *(int **)((char *)*(long *)((char *)self + 0x15C) + 0x830);
    *(volatile float *)((char *)p + 0x20) = one;
    *(volatile float *)((char *)p + 0x28) = one;
    *(volatile float *)((char *)p + 0x24) = one;
    new_var = ret;
    return new_var;
}

void func_001CF090(void) {
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/girlForceField", func_001CF098);
