/* geometryManager.c -- typed sdata / lit4 definitions for this TU.
 *
 * Generated initially by tools/decode_sdata_lit4_typed.py
 * from baserom/baseelf.elf. Each line is a developer
 * reconstruction of one game variable or constant; the
 * file is tracked because the typed forms (named float
 * constants, string literals, single hex-word declarations)
 * are clean-room rather than raw byte arrays.
 *
 * As the TU gets fully decompiled, function definitions
 * land in this same file (per-TU layout); typed
 * data declarations stay here next to their references.
 *
 * Downstream tools (rewrite_data_named_sections.py,
 * migrate_data_per_tu.py _scan_existing_definitions) detect
 * the D_<VMA> name on each line and drop the corresponding
 * asm-generated and sidecar definitions.
 */

extern const char D_00631B30[8];
extern unsigned int D_00631B38;
extern int D_00631B3C;
extern char D_00631B40[8];

unsigned int D_00275830[8] = { 0x00000007, 0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 };

/* String rodata migrated from geometryManager_data.c */
const char D_00553AD0[24] = "src/geometryManager.c";

/* String rodata migrated from geometryManager_data.c */
const char D_00553AE8[96] = "Fatal error! Geometry localize function called with GObj\n    that already have parent.\nExit...\n";

/* String rodata migrated from geometryManager_data.c */
const char D_00553B48[48] = "TOO MANY CHARACTERS EXIST ON THIS STAGE(>64)\n";

/* String rodata migrated from geometryManager_data.c */
const char D_00553B78[24] = "InitKeyInput2() in\n";

/* String rodata migrated from geometryManager_data.c */
const char D_00553B90[16] = "PadInit\n";

/* String rodata migrated from geometryManager_data.c */
const char D_00553BA0[24] = "InitKeyInput2() out\n";

/* String rodata migrated from geometryManager_data.c */
const char D_00553BB8[24] = "signal to main\n";

/* String rodata migrated from geometryManager_data.c */
const char D_00553BE0[48] = "Adjust Motion Height To Field. --------------\n";

/* String rodata migrated from geometryManager_data.c */
const float D_00553C10[4] = { 0.0f, 5.0f, 0.0f, 0.0f };

/* String rodata migrated from geometryManager_data.c */
const float D_00553C20[4] = { 0.0f, 0.0f, 5.0f, 0.0f };

/* String rodata migrated from geometryManager_data.c */
const float D_00553C30[4] = { 5.0f, 0.0f, 0.0f, 0.0f };

/* String rodata migrated from geometryManager_data.c */
const float D_00553C70[4] = { 1e+01f, 0.0f, 0.0f, 0.0f };

/* String rodata migrated from geometryManager_data.c */
const float D_00553C90[4] = { 0.0f, 1.0f, 0.0f, 1.0f };

#include "include_asm.h"
#include "ico/types.h"
#include "matching.h"
#include "vu0.h"

INCLUDE_ASM("asm/nonmatchings/src/geometryManager", func_00102E08);
extern void sceVu0ApplyMatrix(int *self, int v, char *p);
extern void sceVu0Normalize(int *out, int *src);

void func_00102FA0(int *self, int *other, char *p)
{
    func_00105F00((int)self, (int)p);
    {
        char *sub = ((GObj *)((char *)other))->p_15C;
        char *a = *(char **)sub;
        if (a != 0) {
            char *inner_struct = ((GObj *)(a))->p_15C;
            int inner_field = *(int *)(inner_struct + 0xC);
            int idx = *(int *)(sub + 0x4);
            sceVu0ApplyMatrix(self, inner_field + (idx << 6), p);
        }
    }
    *(int *)((char *)self + 0x4) = 0;
    sceVu0Normalize(self, self);
}
INCLUDE_ASM("asm/nonmatchings/src/geometryManager", func_00103018);

/* Matched body inlined from src/cod/003110.c during TU coalesce. */
extern void func_00105F00(int a0, int a1);
void func_00103110(int a0, int a1)
{
    func_00105F00(a0, (int)((GObj *)(a1))->p_15C + 0x130);
}

INCLUDE_ASM("asm/nonmatchings/src/geometryManager", func_0010311C);
INCLUDE_ASM("asm/nonmatchings/src/geometryManager", func_00103120);
INCLUDE_ASM("asm/nonmatchings/src/geometryManager", func_001031E0);
INCLUDE_ASM("asm/nonmatchings/src/geometryManager", func_001032A8);
INCLUDE_ASM("asm/nonmatchings/src/geometryManager", func_00103370);
INCLUDE_ASM("asm/nonmatchings/src/geometryManager", func_001034B8);
extern void func_00105F20(void *dst, void *src);
extern void func_00105E70(char *dst, char *src);
void func_00103AD0(int *self, int *a1)
{
    int buf[16];
    char *obj = (char *)a1[0];
    char *ctx = ((GObj *)(obj))->p_15C;
    func_00105F20(buf, (void *)(*(int *)(ctx + 0xC) + (a1[1] << 6)));
    func_00105E70((char *)buf, (char *)buf);
    sceVu0ApplyMatrix((int *)((char *)((GObj *)((char *)self))->p_15C + 0x520), (int)buf,
                  (char *)((GObj *)((char *)self))->p_15C + 0x520);
    sceVu0Normalize((int *)((char *)((GObj *)((char *)self))->p_15C + 0x520),
                  (int *)((char *)((GObj *)((char *)self))->p_15C + 0x520));
    ((GObj *)((char *)self))->p_15C->f_52C = 0;
}
INCLUDE_ASM("asm/nonmatchings/src/geometryManager", func_00103B48);
INCLUDE_ASM("asm/nonmatchings/src/geometryManager", func_00103C48);
INCLUDE_ASM("asm/nonmatchings/src/geometryManager", func_00103D50);
INCLUDE_ASM("asm/nonmatchings/src/geometryManager", func_00103F00);
extern void GetMatrixFromQuaternionPos(void *a, void *b, void *c);

void func_001040C0(void *a0, char *src)
{
    float *p = (float *)(src + 0xA0);
    GetMatrixFromQuaternionPos(a0, src + 0xD0, p);
    {
        int *g = *(int **)src;
        if (g) {
            func_002438E8(a0,
                          (char *)(*(int *)((int)((GObj *)((char *)g))->p_15C + 0xC) + (*(int *)(src + 4) << 6)),
                          (int)a0);
        }
    }
    *(float *)((char *)a0 + 0x34) += p[0x30];
}

void func_00104140(void *a0, char *outer)
{
    char *src = ((GObj *)(outer))->p_15C;
    float *p = (float *)(src + 0xA0);
    GetMatrixFromQuaternionPos(a0, src + 0xD0, p);
    {
        int *g = *(int **)src;
        if (g) {
            func_002438E8(a0,
                          (char *)(*(int *)((int)((GObj *)((char *)g))->p_15C + 0xC) + (*(int *)(src + 4) << 6)),
                          (int)a0);
        }
    }
    *(float *)((char *)a0 + 0x34) += p[0x30];
}
void func_001041C0(void *a0, char *src)
{
    float *p = (float *)(src + 0xA0);
    float f0;
    int *g = *(int **)src;
    if (g) {
        sceVu0ApplyMatrix((int *)a0,
                      *(int *)((int)((GObj *)((char *)g))->p_15C + 0xC) + (*(int *)(src + 4) << 6),
                      (char *)p);
    } else {
        func_00105F00((int)a0, (int)p);
    }
    f0 = p[0x30];
    *(float *)((char *)a0 + 0x4) += f0;
    *(float *)((char *)a0 + 0xC) = 1.0f;
}
INCLUDE_ASM("asm/nonmatchings/src/geometryManager", func_00104240);
INCLUDE_ASM("asm/nonmatchings/src/geometryManager", func_00104360);
void func_00104478(void *a0, int a1)
{
    int buf[16];
    char *src = ((GObj *)((char *)a0))->p_15C;
    float *p = (float *)(src + 0xA0);
    func_00105F00((int)p, a1);
    *(float *)((char *)p + 0x4) -= *(float *)((char *)p + 0xC0);
    *(float *)((char *)p + 0xC) = 1.0f;
    MEM_BARRIER();
    {
        char *src2 = ((GObj *)((char *)a0))->p_15C;
        int *g = *(int **)src2;
        if (g) {
            func_00105E70((char *)buf,
                          (char *)(*(int *)((int)((GObj *)((char *)g))->p_15C + 0xC) + (*(int *)(src2 + 4) << 6)));
            sceVu0ApplyMatrix((int *)p, (int)buf, (char *)p);
        }
    }
}
void func_00104508(void *a0, char *outer)
{
    char *src = ((GObj *)(outer))->p_15C;
    float *p = (float *)(src + 0xA0);
    float f0;
    int *g = *(int **)src;
    if (g) {
        sceVu0ApplyMatrix((int *)a0,
                      *(int *)((int)((GObj *)((char *)g))->p_15C + 0xC) + (*(int *)(src + 4) << 6),
                      (char *)p);
    } else {
        func_00105F00((int)a0, (int)p);
    }
    f0 = p[0x30];
    *(float *)((char *)a0 + 0x4) += f0;
    *(float *)((char *)a0 + 0xC) = 1.0f;
}
INCLUDE_ASM("asm/nonmatchings/src/geometryManager", func_00104590);

extern float D_00630904;
extern float D_00630908;

int func_00104638(float *vals, int *flags)
{
    float lo = D_00630904;
    int ret = 0;
    int i;
    for (i = 2; i >= 0; i--) {
        register float v REG("$f0") = *vals;
        if (v < lo) {
            *vals = lo;
            ret = 1;
            *flags = 0;
        } else {
            MEM_BARRIER();
            if (v > D_00630908) {
                *vals = D_00630908;
                ret = 1;
                *flags = 0;
            }
        }
        flags++;
        vals++;
    }
    return ret;
}
extern void func_00105E70(char *dst, char *src);
extern void func_002438E8(char *dst, char *src, int m);

void GetRootMatrixTransOffsetByDObj(char *dst, char *src)
{
    char tmp[0x40];
    func_00105E70(tmp, src + 0x20);
    func_002438E8(tmp, tmp, *(int *)(src + 0xC));
    func_00105F00((int)dst, (int)(tmp + 0x30));
}

void GetRootMatrixTransOffset(char *dst, char *outer)
{
    char *src = ((GObj *)(outer))->p_15C;
    char tmp[0x40];
    func_00105E70(tmp, src + 0x20);
    func_002438E8(tmp, tmp, *(int *)(src + 0xC));
    func_00105F00((int)dst, (int)(tmp + 0x30));
}
INCLUDE_ASM("asm/nonmatchings/src/geometryManager", GetRootMotionOrient);
INCLUDE_ASM("asm/nonmatchings/src/geometryManager", GetRootMotionMatrix);
extern void func_001183F0(void *buf, void *p1, float f);
extern void func_00105F78(void *a, void *b, void *c);
void GetProjectionPosOfPlane(void *a0, void *a1, void *a2)
{
    int buf[4];
    register float dot __asm__("$f12");
    VU0_LSV_R(lqc2, 1, 0x0, a2);
    VU0_LSV(lqc2, 2, 0x0, a1);
    VU0_V3OP(vmul.xyz, 3, 1, 2);
    VU0_V3OP_BC(vaddy.x, 3, 3, 3, y);
    VU0_V3OP_BC(vaddz.x, 3, 3, 3, z);
    VU0_V3OP_BC(vaddw.x, 3, 3, 2, w);
    VU0_QMFC2_NI(v0, 3);
    VU0_MTC1(v0, 12);
    func_001183F0(buf, a1, -dot);
    func_00105F78(a0, a2, buf);
    *(float *)((char *)a0 + 0xC) = 1.0f;
}
float GetProjectionOfPlane(void *a0, void *a1, void *a2)
{
    int buf[4];
    float z = 0.0f;
    register float dot __asm__("$f20");
    VU0_LSV_R(lqc2, 1, 0x0, a2);
    VU0_LSV(lqc2, 2, 0x0, a1);
    VU0_V3OP(vmul.xyz, 3, 1, 2);
    VU0_V3OP_BC(vaddy.x, 3, 3, 3, y);
    VU0_V3OP_BC(vaddz.x, 3, 3, 3, z);
    VU0_V3OP_BC(vaddw.x, 3, 3, 2, w);
    VU0_QMFC2_NI(v0, 3);
    VU0_MTC1(v0, 20);
    {
        register float nd __asm__("$f12") = -dot;
        func_001183F0(buf, a1, nd + z);
    }
    func_00118388(a0, a2, buf);
    return dot;
}
extern void func_00118388(void *a, void *b, void *c);
float GetProjectionOfPlaneWithKeepAway(void *a0, void *a1, void *a2, float t)
{
    int buf[4];
    register float dot __asm__("$f20");
    VU0_LSV_R(lqc2, 1, 0x0, a2);
    VU0_LSV(lqc2, 2, 0x0, a1);
    VU0_V3OP(vmul.xyz, 3, 1, 2);
    VU0_V3OP_BC(vaddy.x, 3, 3, 3, y);
    VU0_V3OP_BC(vaddz.x, 3, 3, 3, z);
    VU0_V3OP_BC(vaddw.x, 3, 3, 2, w);
    VU0_QMFC2_NI(v0, 3);
    VU0_MTC1(v0, 20);
    func_001183F0(buf, a1, -dot + t);
    func_00118388(a0, a2, buf);
    return dot;
}

/* Matched body inlined from src/cod/004A38.c during TU coalesce. */
extern int D_0065F940[];
int *func_00104A38(void) {
    return D_0065F940;
}

TRAILING_PAD_NOP();
