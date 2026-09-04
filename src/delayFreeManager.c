#include "common.h"






#include "ico/types.h"
extern void MultiQuaternion();
extern void GetInverseQuaternion();
extern const char D_00553A78[64];
extern void func_001AD768();
extern void __assert();
extern const char D_00631B28[];
extern int D_0065ED40[];
extern int D_00631B20, D_00631B24;
extern int D_00631B20;
extern const char D_00553AB8[24];
extern void debug_StdPrintfDummy();
extern int D_00631914;
extern int D_00631900;
extern int D_00275254[];
extern void ExecKeyInput();
INCLUDE_ASM("asm/nonmatchings/src/delayFreeManager", func_00101C80);

INCLUDE_ASM("asm/nonmatchings/src/delayFreeManager", func_00101F70);

INCLUDE_ASM("asm/nonmatchings/src/delayFreeManager", func_00102158);

INCLUDE_ASM("asm/nonmatchings/src/delayFreeManager", func_00102340);

INCLUDE_ASM("asm/nonmatchings/src/delayFreeManager", Emergency_DestroyAllThread);

int movie_abort_check(void)
{
  int ret = 0;
  if (D_00631914 != D_00631900)
  {
    D_00631914 = D_00631900;
    ExecKeyInput();
    ret = 0;
    ret = (D_00275254[0] & 0x800) != ret;
  }
  return ret;
}

INCLUDE_ASM("asm/nonmatchings/src/delayFreeManager", main);

void func_00102558(int a0)
{
    int count = D_00631B24;
    *(int *)((char *)D_0065ED40 + (count * 4 + (D_00631B20 << 10))) = a0;
    count++;
    D_00631B24 = count;
    if (count >= 0x100) {
        debug_StdPrintfDummy(D_00553A78);
        func_001AD768(D_00553AB8, 0x33);
        __assert(D_00553AB8, 0x33, D_00631B28);
    }
}

void func_001025E8(void)
{
    int i;
    for (i = 0xFF; i >= 0; i--) D_0065ED40[i] = 0;
    for (i = 0xFF; i >= 0; i--) D_0065ED40[i + 0x100] = 0;
    for (i = 0xFF; i >= 0; i--) D_0065ED40[i + 0x200] = 0;
    D_00631B24 = 0;
    D_00631B20 = 0;
}

INCLUDE_ASM("asm/nonmatchings/src/delayFreeManager", func_00102680);

void func_00102790(int a0, int *a1)
{
    int *p;
    int *q;
    int idx;
    p = (int *)a1[0];
    if (p == 0) goto null_path;
    q = (int *)p[0x57];
    idx = a1[1];
    MultiQuaternion(a0, q[0x4] + (idx << 4), (int)a1 + 0xD0);
    return;
null_path:
    GetInverseQuaternion(a0, (int)a1 + 0xD0);
}

INCLUDE_ASM("asm/nonmatchings/src/delayFreeManager", func_001027C8);

void func_00102850(int a0, int a1)
{
    func_00102790(a0, (int)((GObj *)(a1))->p_15C);
}

void func_00102858(int a0)
{
    func_001027C8((int)((GObj *)(a0))->p_15C);
}

void SetRootBaseQuaternion(int a0)
{
    GetInverseQuaternion((int)((GObj *)(a0))->p_15C + 0xC0);
}

INCLUDE_ASM("asm/nonmatchings/src/delayFreeManager", func_00102870);

