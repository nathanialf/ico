#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_menu", debug_TargetGObj);

extern int D_0062AF3C;

void init_debug_menu(void) {
    D_0062AF3C = 0;
}

void debug_BeginTimer(int a0) {
    *(volatile int *)0x10000800 = 0;
    *(volatile int *)0x10000810 = a0 | 0x80;
}

typedef struct { float f[4]; } __attribute__((packed)) Blk16;
extern Blk16 D_0060D738;

float debug_GetTimerSec(void) {
    Blk16 buf;
    int v;
    float f2;

    buf = D_0060D738;
    if (*(volatile unsigned int *)0x10000810 & 0x800) {
        return -1.0f;
    }
    v = *(volatile int *)0x10000800;
    f2 = (float)(unsigned int)v;
    return f2 / buf.f[*(volatile unsigned int *)0x10000810 & 3] / 60.0f;
}

float debug_GetTimerCount(void) {
    if ((*(volatile int *)0x10000810) & 0x800) {
        return -1.0f;
    }
    return (float)(*(volatile unsigned int *)0x10000800);
}

typedef struct { char pad0[4]; char f4; char pad5[0x33]; } Entry;
extern Entry D_006EB120[];
extern int D_0062ACAC;

void debug_ClearFontWindow(void) {
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

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_menu", debug_SetBar);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_menu", debug_SetBar2);

extern int D_0062AF58, D_0062AF5C, D_0062AF60, D_0062AF64, D_0062AF68, D_0062AF6C, D_0062C148;

void debug_ResetBar(void) {
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

void debug_DispMatrix(int *a0)
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

extern void sprintf(void *a0, void *a1, void *a2, int a3);
extern int sceOpen(void *a0, int a1);
extern int D_006E7820[];
extern int D_0062CDD0[];
extern int D_0060E548[];
extern int D_0062AF48;

int debugSceOpen(int a0, int a1) {
    sprintf(D_006E7820, D_0062CDD0, D_0060E548, a0);
    return D_0062AF48 = sceOpen(D_006E7820, a1);
}

extern int D_0062AF48;
extern int sceClose();

int debugSceClose(int a0) {
    if (a0 == D_0062AF48) {
        D_0062AF48 = -1;
    }
    return sceClose();
}

int debugSceCloseFdNew(void) {
    int h = D_0062AF48;
    int r = 0;
    if (h != -1) {
        D_0062AF48 = -1;
        r = sceClose(h);
        D_0062AF48 = -1;
    }
    return r;
}

void func_001A7B50(void) {
}

extern int D_006F26D0[];

void debugCdvdLoadInfoSegInit(int idx)
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

void debugCdvdLoadInfoSegAdd(int a0, int a1, int a2) {
    int *p = (int *)(a1 * 8 + a0 * 0xD0 + (int)(char *)D_006F26D0_fwd);
    *p += a2;
}


void debugCdvdLoadInfoSegCls(int a0, int a1) {
    *(int *)((char *)D_006F26D0 + a1 * 8 + a0 * 0xD0) = 0;
}

extern char D_00271270[];
extern void gsb_antiAlias(void *a0);

int gsResetFunc(void) {
    gsb_antiAlias(D_00271270);
    return 1;
}

extern int D_0062ACB0;

int func_001A7C20(void) {
    D_0062ACB0 = *(volatile int *)0x10000000;
    return 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_menu", debug_SaveStartStageFile);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_menu", _debug_SelectCsvWindow);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_menu", debug_SelectCsvWindowWithLineColor);

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
