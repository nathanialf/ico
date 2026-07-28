#include "common.h"






#include "ico/types.h"
extern void func_0010DDB8();
extern void GetInverseQuaternion();
extern int D_0065ED40_a[] __asm__("D_0065ED40");
extern int D_0065ED40_b[] __asm__("D_0065ED40");
extern const char D_00553A78[64];
extern void func_001AD768();
extern void func_00263FF0();
extern const char D_00631B28_a[] __asm__("D_00631B28");
extern char D_0065ED40[];
extern int D_00631B20, D_00631B24;
extern int D_00631B20;
extern const char D_00553AB8[24];
extern void debug_assertMessage();
extern int D_00631914;
extern int D_00631900;
extern int D_00275254[];
extern void func_00104C80();
INCLUDE_ASM("asm/nonmatchings/src/delayFreeManager", func_00101C80);

INCLUDE_ASM("asm/nonmatchings/src/delayFreeManager", func_00101F70);

INCLUDE_ASM("asm/nonmatchings/src/delayFreeManager", func_00102158);

INCLUDE_ASM("asm/nonmatchings/src/delayFreeManager", func_00102340);

INCLUDE_ASM("asm/nonmatchings/src/delayFreeManager", func_00102418);

int func_001024B8(void)
{
  int ret = 0;
  if (D_00631914 != D_00631900)
  {
    D_00631914 = D_00631900;
    func_00104C80();
    ret = 0;
    ret = (D_00275254[0] & 0x800) != ret;
  }
  return ret;
}

INCLUDE_ASM("asm/nonmatchings/src/delayFreeManager", func_001024F8);

void func_00102558(int a0)
{
    register int count __asm__("$5") = D_00631B24;
    int next = count + 1;
    int *slot = (int *)(D_0065ED40 + (count * 4 + (D_00631B20 << 10)));
    D_00631B24 = next;
    *slot = a0;
    if (next >= 0x100) {
        debug_assertMessage(D_00553A78);
        func_001AD768(D_00553AB8, 0x33);
        func_00263FF0(D_00553AB8, 0x33, D_00631B28_a);
    }
}

void func_001025E8(void)
{
    int *p;
    int i;
    p = D_0065ED40;
    p += 0xFF;
    i = 0xFF;
    do { *p = 0; i--; p--; } while (i >= 0);
    p = D_0065ED40_a;
    p += 0x1FF;
    i = 0xFF;
    do { *p = 0; i--; p--; } while (i >= 0);
    p = D_0065ED40_b;
    p += 0x2FF;
    i = 0xFF;
    do { *p = 0; i--; p--; } while (i >= 0);
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
    func_0010DDB8(a0, q[0x4] + (idx << 4), (int)a1 + 0xD0);
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

void func_00102860(int a0)
{
    GetInverseQuaternion((int)((GObj *)(a0))->p_15C + 0xC0);
}

INCLUDE_ASM("asm/nonmatchings/src/delayFreeManager", func_00102870);

