/* rotObject.c -- typed sdata / lit4 definitions for this TU.
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

extern unsigned char D_006335C8;
extern int D_006335CC;
extern int D_006335D0;
extern int D_006335D4;
extern int D_006335D8;
extern int D_006335DC;
extern const char D_006335E8[8];
extern unsigned int D_006335F0;
extern int D_006335F4;
extern int D_006335F8;

extern unsigned int D_00275890[20];
extern int          D_00275860[4];
extern int          D_00632010;
extern float        D_006313C8;

extern int  *func_0013A0F8(int handle, int size, char *file, int line);
extern int   func_00105278(void);
extern void  func_00104140(int v, int *self);
extern void  MatrixDrive_RotMatrixY(int x);
extern void  func_00105F00(int *out, int *src);
extern void  _ApplyMatrix(int *out, int v, unsigned int *src);
extern void  func_001182F0(int *out, int *in);
extern void  func_00105FA8(int v);
extern float atan2f(float a, float b);
extern void  func_00105F20(int a, int b);
extern void  func_0010ECB8(int *self);

/* String-pool rodata migrated from rotObject_data.c */
const char D_00619FC8[120] = "src/rotObject.c\000GetRotObjectHoldPoint\000\000\000\t%f, %f, %f\n\000\000\000\000MoveRotObjectWithHoldPoint\000\000\000\000\000\000GetRotObjectGlobalHoldGeometry\000";

#include "include_asm.h"
#include "ico/types.h"
#include "matching.h"
#include "regpin.h"

int *func_001E9F08(int *a0, int *a1)
{
    int *obj;
    int mode;
    int *vmtx;
    int *p15c;
    int *src275860;
    float angle;
    float zero_f;
    float v28, v20;

    obj = func_0013A0F8(D_00632010, 0x40, (char *)D_00619FC8, 0x37);

    obj[0x30 / 4] = D_006335C8;
    D_006335C8 = (D_006335C8 + 1) % 30;

    func_00105F00(obj + (0x10 / 4), a1);

    *(float *)((char *)obj + 0x1C) = 1.0f;

    angle = *(float *)((char *)a1 + 0x14) * 32768.0f;
    mode = a1[0x30 / 4];
    zero_f = 0.0f;
    obj[0] = mode;
    angle = angle / 180.0f;

    *(float *)((char *)obj + 0x2C) = zero_f;
    *(float *)((char *)obj + 0x28) = zero_f;
    obj[0x24 / 4] = 0;
    obj[0x34 / 4] = 0;

    *(short *)((char *)obj + 0x20) = (short)(int)angle;

    if (mode == 3) {
        register float v28_p REG("$f1");
        v28_p = *(float *)((char *)a1 + 0x28);
        src275860 = D_00275860;
        *(volatile float *)((char *)obj + 0x28) = v28_p;

        v20 = *(float *)((char *)a1 + 0x20);
        *(volatile float *)((char *)obj + 0x2C) = v20;
        __asm__ __volatile__("" : : : "memory");
        p15c = (int *)((GObj *)(a0))->p_15C;
        func_00105F00((int *)((char *)p15c + 0xA0), src275860);
    }

    vmtx = (int *)((int *)((GObj *)(a0))->p_15C)[0x840 / 4];
    *(volatile float *)((char *)vmtx + 0x20) = 1.0f;
    *(volatile float *)((char *)vmtx + 0x28) = 1.0f;
    *(volatile float *)((char *)vmtx + 0x24) = 1.0f;

    return obj;
}

void func_001EA030(int *self)
{
    int *s1;
    short *actor;
    int c_field;
    int sp[4];
    int v0;
    float f;

    s1 = (int *)((GObj *)(self))->p_15C;
    actor = (short *)((Sub15C *)(s1))->p_800;
    KEEP_LIVE(actor);
    c_field = s1[0xC / 4];

    v0 = func_00105278();
    func_00104140(v0, self);
    MatrixDrive_RotMatrixY((int)actor[0x20 / 2]);

    v0 = func_00105278();
    _ApplyMatrix(sp, v0, D_00275890);
    sp[1] = 0;
    func_001182F0(sp, sp);

    v0 = func_00105278();
    func_00105FA8(v0);

    f = atan2f(*(float *)&sp[0], *(float *)&sp[2]);
    f *= D_006313C8;
    MatrixDrive_RotMatrixY((int)(short)(int)f);

    v0 = func_00105278();
    func_00105F20(c_field, v0);

    func_0010ECB8(self);
}
