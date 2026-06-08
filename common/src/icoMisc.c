#include "common.h"

typedef void (*func_001AE8F0_FnPtr)(int *buf, int a2);

extern void func_00102828(int a0);
extern void func_0010F048(int a0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/icoMisc", disp_memory_partition_bar);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/icoMisc", disp_memory_partition);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/icoMisc", ExecIcoMisc);

extern unsigned short D_004AF050[];
int InitIcoMisc(void) {
    unsigned short *p = D_004AF050;
    if (p[1] != 0) {
        return p[2];
    }
    return 4;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/icoMisc", DispIcoMisc);

extern int D_004AEE68[];
extern int D_0062B234;

void ExitIcoMisc(int a0) {
    D_004AEE68[a0] = D_0062B234;
}

extern void func_002604B8(int a, int b);

void func_001ABE38(int *self, int a1, int a2)
{
    if (a1 != 0) {
        func_002604B8(a1, self[0] + self[0x4 / 4]);
    }
    self[0x4 / 4] = self[0x4 / 4] + a2;
}

void func_001ABE88(int *self, int a1, int a2)
{
  func_001AE8F0_FnPtr new_var;
  int buf[2];
  int new_var2;
  func_001AE8F0_FnPtr fn;
  buf[0] = a1;
  buf[1] = 0;
  fn = (func_001AE8F0_FnPtr) self[1];
  new_var2 = fn != 0;
  if (new_var2)
  {
    do
    {
      fn(buf, a2);
      self += 2;
      new_var2 = self[1];
      new_var = (func_001AE8F0_FnPtr) new_var2;
      fn = new_var;
    }
    while (new_var2);
  }
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/icoMisc", func_001ABEE0);

extern int func_002613B4(int *p, int *buf);
extern int D_0062B240;
extern int D_004AEE10[];

void func_001ABF40(int *self)
{
    int buf[8];
    func_001ABE38(self, buf, 0x12);
    if (func_002613B4(D_004AEE10, buf) != 0) {
        D_0062B240 = 1;
    } else {
        D_0062B240 = 0;
    }
}

extern void func_001AB750(int a, char *p, int n);
extern void func_00260568(char *p, int a, int n);

void func_001ABF88(int a0)
{
    if (D_0062B240 == 0) {
        func_001AB750(a0, D_004AEE10, 0x12);
        return;
    }
    {
        char buf[0x20];
        func_00260568(buf, 0, 0x12);
        func_001AB750(a0, buf, 0x12);
    }
}

void func_001ABFE8(int a0) {
    func_00102828(a0);
}

void func_001ABFF0(int a0) {
    func_0010F048(a0);
}

int func_001ABFF8(void) {
    return 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/icoMisc", func_001AC000);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/icoMisc", func_001AC5E8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/icoMisc", func_001AC728);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/icoMisc", func_001ACA38);


/* recovered struct shapes */
typedef struct {
    unsigned short     f_2;  /* 0x02 */
    unsigned short     f_4;  /* 0x04 */
} S_004AF050;

/* end struct shapes */
