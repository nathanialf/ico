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

extern void MatrixDrive_TurnObjectMatrix(void *a0, void *a1);
extern unsigned char D_00271BE0[];

int DispIcoMisc(void *a0) {
    unsigned short *p = D_004AF050;
    if (p[1] != 0) {
        MatrixDrive_TurnObjectMatrix(a0, p + 8);
        return p[2];
    }
    MatrixDrive_TurnObjectMatrix(a0, D_00271BE0);
    return 4;
}

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

extern int func_00178DD8(int a0);

void func_001ABEE0(int *a0, int a1, int a2) {
    int buf[2];
    void (*f)(int *, int);
    int next;
    buf[0] = a1;
    buf[1] = 0;
    f = (void (*)(int *, int))a0[0];
    if (f != 0) {
        do {
            f(buf, a2);
            a0 += 2;
            next = a0[0];
            f = (void (*)(int *, int))next;
        } while (next != 0);
    }
    func_00178DD8(0x168);
}

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

extern void debugEEExceptionMain(int a0, int a1, unsigned int a2, void *a3);
extern void iosReallocDebug(void *a0);
extern void func_00261188(void *a0, void *a1, ...);
extern char D_0060F3B0[];
extern char D_0060F3E8[];
extern void *D_0062A300;
extern char D_006FF890[];

void func_001AC5E8(void) {
    char *p;
    int y = 0x70;
    debugEEExceptionMain(0x18, 0x64, 0xFFFFFF00, D_0060F3B0);
    iosReallocDebug(D_0062A300);
    p = *(char **)((char *)D_0062A300 + 0x28);
    if (p != 0) {
        do {
            unsigned int sum = 0;
            unsigned int max = 0;
            char *e;
            int diff;
            iosReallocDebug(p);
            e = *(char **)(p + 0x44);
            if (e != 0) {
                do {
                    unsigned int v = *(int *)(e + 0x34) << 4;
                    if (max < v) {
                        max = v;
                    }
                    sum += v;
                    e = *(char **)(e + 0x2C);
                } while (e != 0);
            }
            diff = *(int *)(p + 0x3C) - *(int *)(p + 0x38) + 0x10;
            func_00261188(D_006FF890, D_0060F3E8, p + 0x10, p, sum, diff, max);
            debugEEExceptionMain(0x64, y, 0xFFFFFF00, D_006FF890);
            y += 8;
            p = *(char **)(p + 0x24);
        } while (p != 0);
    }
}


INCLUDE_ASM("asm/aug6/nonmatchings/common/src/icoMisc", func_001AC728);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/icoMisc", func_001ACA38);


/* recovered struct shapes */
typedef struct {
    unsigned short     f_2;  /* 0x02 */
    unsigned short     f_4;  /* 0x04 */
} S_004AF050;

/* end struct shapes */
