#include "common.h"










extern int D_006329E8;
extern void gsb_antiAlias();
extern int D_00274EF0[];
extern int D_006F8EE0[];
extern void func_00264DF8();
extern int D_00632C88[];
extern char D_00615B48[];
extern int D_00632C80;
extern char D_006EE030[];
extern int func_00247380();
extern void initLineTraceTable();
extern int D_00632C90;
extern int D_00632CA0;
extern int D_00632C98;
extern int D_00633E58;
extern int D_00632C9C;
extern int D_00632CA4;
extern int D_00632C94;
extern int D_00632A34;
extern int D_006329E4;
extern char D_006F1930[];
extern int D_00632C74;
INCLUDE_ASM("asm/nonmatchings/src/debug_menu", debug_TargetGObj);

void init_debug_menu(void) {
    D_00632C74 = 0;
}

void debug_TargetGObj_Func(int a0) {
    *(volatile int *)0x10000800 = 0;
    *(volatile int *)0x10000810 = a0 | 0x80;
}

INCLUDE_ASM("asm/nonmatchings/src/debug_menu", func_001A9DB8);

INCLUDE_ASM("asm/nonmatchings/src/debug_menu", func_001A9E88);

void func_001A9EE8(void)
{
    char *p = D_006F1930;
    int i;
    p += 0x5B4;
    for (i = 0x1A; i >= 0; i--) {
        *p = 0;
        p -= 0x38;
    }
    D_006329E4 = 0;
}

void func_001A9F20(int val) {
    D_00632A34 = val;
}

INCLUDE_ASM("asm/nonmatchings/src/debug_menu", func_001A9F28);

INCLUDE_ASM("asm/nonmatchings/src/debug_menu", func_001A9FE0);

void func_001AA098(void)
{
    D_00632CA0 = 0;
    *(volatile int *)0x10000000 = 0;
    D_00632C9C = 0;
    D_00632C98 = 0;
    D_00632C94 = 0;
    D_00632C90 = 0;
    D_00632CA4 = 0;
    D_00633E58 = 0;
}

INCLUDE_ASM("asm/nonmatchings/src/debug_menu", func_001AA0C0);

INCLUDE_ASM("asm/nonmatchings/src/debug_menu", func_001AA168);

void func_001AA210(int *a0)
{
    int *p = a0;
    int i;
    for (i = 3; i >= 0; i--) {
        initLineTraceTable(p, 0);
        p = (int *)((char *)p + 0x10);
    }
}

void func_001AA258(void) {}

INCLUDE_ASM("asm/nonmatchings/src/debug_menu", func_001AA260);

int func_001AA4E8(void) {
    return -1;
}

int func_001AA4F0(int *self, int *other)
{
    int r;
    func_00264DF8(D_006EE030, D_00632C88, D_00615B48, self);
    r = func_00247380(D_006EE030, other);
    D_00632C80 = r;
    return r;
}

extern int func_00247608(void);

int func_001AA550(int a0) {
    if (a0 == D_00632C80) {
        D_00632C80 = -1;
    }
    return func_00247608();
}

/* The sibling above calls this kernel entry with no argument; here it takes
 * the old handle, so bind a correctly-typed name to the same symbol. */
extern int func_00247608_h(int handle) __asm__("func_00247608");

int func_001AA580(void)
{
    int r = 0;
    int h = D_00632C80;
    if (h != -1) {
        D_00632C80 = -1;
        r = func_00247608_h(h);
        D_00632C80 = -1;
    }
    return r;
}

void func_001AA5B8(void) {}

void func_001AA5C0(int idx)
{
  int *p;
  char *new_var2;
  int new_var;
  int i;
  new_var2 = (char *) D_006F8EE0;
  p = (int *) ((new_var2 + (idx * 0xD0)) + 0xC8);
  if (1)
  {
    for (i = 0x19; i >= 0; i--)
    {
      new_var = (*p = 0);
      p = (p = (int *) (((char *) p) - 8));
    }

  }
}

void func_001AA608(int page, int idx, int delta)
{
    *(int *)((char *)D_006F8EE0 + (page * 0xD0 + idx * 8)) += delta;
}

void func_001AA638(int page, int idx)
{
    *(int *)((char *)D_006F8EE0 + (page * 0xD0 + idx * 8)) = 0;
}

int func_001AA660(void)
{
    gsb_antiAlias(D_00274EF0);
    return 1;
}

int func_001AA688(void)
{
    D_006329E8 = *(volatile int *)0x10000000;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/src/debug_menu", func_001AA6A0);

INCLUDE_ASM("asm/nonmatchings/src/debug_menu", func_001AA750);

INCLUDE_ASM("asm/nonmatchings/src/debug_menu", func_001AA9F8);

INCLUDE_ASM("asm/nonmatchings/src/debug_menu", func_001AACA0);

INCLUDE_ASM("asm/nonmatchings/src/debug_menu", func_001AAD88);

