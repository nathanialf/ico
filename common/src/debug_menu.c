#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_menu", debug_TargetGObj);

extern int D_0062AF3C;

void init_debug_menu(void) {
    D_0062AF3C = 0;
}

void debug_TargetGObj_Func(int a0) {
    *(volatile int *)0x10000800 = 0;
    *(volatile int *)0x10000810 = a0 | 0x80;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_menu", func_001A7350);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_menu", func_001A7420);

typedef struct { char pad0[4]; char f4; char pad5[0x33]; } Entry;
extern Entry D_006EB120[];
extern int D_0062ACAC;

void func_001A7480(void) {
    int i;
    for (i = 0x1A; i >= 0; i--) {
        D_006EB120[i].f4 = 0;
    }
    D_0062ACAC = 0;
}

extern int D_0062ACFC;

void func_001A74B8(int a0) {
    D_0062ACFC = a0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_menu", func_001A74C0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_menu", func_001A7578);

extern int D_0062AF58, D_0062AF5C, D_0062AF60, D_0062AF64, D_0062AF68, D_0062AF6C, D_0062C148;

void func_001A7630(void) {
    D_0062AF68 = 0;
    *(volatile int *)0x10000000 = 0;
    D_0062AF64 = 0;
    D_0062AF60 = 0;
    D_0062AF5C = 0;
    D_0062AF58 = 0;
    D_0062AF6C = 0;
    D_0062C148 = 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_menu", func_001A7658);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_menu", func_001A7700);

extern void initLineTraceTable(int *p, int a1);

void func_001A77A8(int *a0)
{
    int *p = a0;
    int i;
    for (i = 3; i >= 0; i--) {
        initLineTraceTable(p, 0);
        p = (int *)((char *)p + 0x10);
    }
}

void func_001A77F0(void) {
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_menu", func_001A77F8);

int func_001A7A80(void) {
    return -1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_menu", func_001A7A88);

extern int D_0062AF48;
extern int func_00243B28();

int func_001A7AE8(int a0) {
    if (a0 == D_0062AF48) {
        D_0062AF48 = -1;
    }
    return func_00243B28();
}

int func_001A7B18(void) {
    int h = D_0062AF48;
    int r = 0;
    if (h != -1) {
        D_0062AF48 = -1;
        r = func_00243B28(h);
        D_0062AF48 = -1;
    }
    return r;
}

void func_001A7B50(void) {
}

extern int D_006F26D0[];

void func_001A7B58(int idx)
{
  int *p;
  char *new_var2;
  int new_var;
  int i;
  new_var2 = (char *) D_006F26D0;
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

extern int D_006F26D0_fwd[] __asm__("D_006F26D0");

void func_001A7BA0(int a0, int a1, int a2) {
    int *p = (int *)(a1 * 8 + a0 * 0xD0 + (int)(char *)D_006F26D0_fwd);
    *p += a2;
}


void func_001A7BD0(int a0, int a1) {
    *(int *)((char *)D_006F26D0 + a1 * 8 + a0 * 0xD0) = 0;
}

extern char D_00271270[];
extern void gsb_antiAlias(void *a0);

int func_001A7BF8(void) {
    gsb_antiAlias(D_00271270);
    return 1;
}

extern int D_0062ACB0;

int func_001A7C20(void) {
    D_0062ACB0 = *(volatile int *)0x10000000;
    return 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_menu", func_001A7C38);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_menu", func_001A7CE8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_menu", func_001A7F90);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_menu", func_001A8238);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_menu", func_001A8320);


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
    unsigned int       f_4;  /* 0x04 */
} S_006F26D0;

typedef struct {
    unsigned int       f_4;  /* 0x04 */
    unsigned int       f_8;  /* 0x08 */
} S_004AE440;  /* stride 0xC */

/* end struct shapes */
