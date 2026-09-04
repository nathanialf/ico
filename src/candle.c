#include "common.h"

#include "ico/types.h"

typedef struct {
    int id;   /* 0x0 */
    int flag; /* 0x4 */
} CandleElem;

extern int file_LoadCDFile(int a0);
extern int func_0010ECD8(int a0);

void InitCandleGeo(int a0)
{
    int *s0 = ((GObj *)((char *)a0))->p_15C;
    if (s0[0x74 / 4] != 0) {
        func_0010ECD8(a0);
        return file_LoadCDFile((int)s0);
    }
}

int CandleDL(void)
{
    return 0;
}

extern int D_00276140[];
extern char D_00618858[];
extern char D_00618868[];
extern int D_00632010;
extern void CopyMatrix(int a0, int a1);
extern void debug_StdPrintfDummy(const char *p);
extern int func_00105278(void);
extern void func_00105308(float a0, float a1, float a2);
extern int *func_0013A0F8(int handle, int size, const char *file, int line);
extern int func_001E8B48(int a, void *b, void *c);

int *CandleGeo(GObj *self, int a1)
{
    Sub15C *sub = self->p_15C;
    int *r;
    if (sub->f_8 >= 2) {
        int i;
        r = func_0013A0F8(D_00632010, sub->f_8 * 8, D_00618858, 0x18);
        for (i = 0; i < sub->f_8; i++) {
            int v = func_00105278();
            CopyMatrix(v, sub->f_C + i * 0x40);
            func_00105308(0.0f, -40.0f, 0.0f);
            r[i * 2] = func_001E8B48(4, (void *)(func_00105278() + 0x30), D_00276140);
            r[i * 2 + 1] = 0;
        }
    } else {
        r = func_0013A0F8(D_00632010, 8, D_00618858, 0x23);
        r[0] = func_001E8B48(4, (void *)a1, D_00276140);
        r[1] = 0;
    }
    debug_StdPrintfDummy(D_00618868);
    return r;
}

extern int file_LoadCDFile(int a0);
extern int func_0010ECD8(int a0);

void DeleteLayoutedCandleParticleEffect(int a0)
{
    int *s0 = ((GObj *)((char *)a0))->p_15C;
    if (s0[0x74 / 4] != 0) {
        func_0010ECD8(a0);
        return file_LoadCDFile((int)s0);
    }
}

extern int D_00276140[];
extern void ExecParticleEffects(int a0, int a1, int *a2);
extern void CopyMatrix(int a0, int a1);
extern int func_00105278(void);
extern void func_00105308(float a0, float a1, float a2);

void _deleteLayoutedCandleParticleEffect(GObj *self)
{
    Sub15C *sub = self->p_15C;
    CandleElem *arr = (CandleElem *)sub->p_800;
    if (sub->f_74 != 0) {
        if (sub->f_8 > 1) {
            int i;
            for (i = 0; i < sub->f_8; i++) {
                CopyMatrix((int)func_00105278(),
                                                GOBJ_SUB(self)->f_C + i * 0x40);
                func_00105308(0.0f, -40.0f, 0.0f);
                if (arr[i].id != -1) {
                    ExecParticleEffects(arr[i].id,
                                        (int)func_00105278() + 0x30,
                                        D_00276140);
                }
            }
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/src/candle", func_001C3270);

