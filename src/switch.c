/* src/switch.c — __FILE__ anchor at .rodata 0x00618630 */

__attribute__((section(".rodata.0x00618630"))) const char D_00618630[16] = "src/switch.c";

#include "include_asm.h"
#include "regpin.h"
#include "matching.h"

INCLUDE_ASM("asm/nonmatchings/src/switch", func_001C09C4);
extern int D_00632010;
extern int func_0013A0F8(int handle, int size, const char *file, int line);
extern unsigned char D_004BEFD0[];
extern unsigned int D_0028CA88[];
extern int func_0019F310(int x, void *y);
typedef struct { long long w[4]; } __attribute__((packed)) SwitchBuf20_09C8;
int *func_001C09C8(char *self, void *arg1)
{
    int *buf = (int *)func_0013A0F8(D_00632010, 0x20, D_00618630, 0x8D);
    int *entry;
    *(SwitchBuf20_09C8 *)buf = *(SwitchBuf20_09C8 *)D_004BEFD0;
    if (((int *)arg1)[0x30 / 4] != 0) {
        buf[0x14 / 4] = 1;
    } else {
        buf[0x14 / 4] = 0;
    }
    entry = (int *)((char *)D_0028CA88 + (*(int **)(self + 0x15C))[0x814 / 4] * 0x28);
    buf[0xC / 4] = func_0019F310(entry[0], arg1);
    KEEP_LIVE_MEM(buf);
    {
        register void *a1 REG("$5") = arg1;
        register int *t1 REG("$3");
        register int idx2 REG("$2");
        KEEP_LIVE(a1);
        t1 = *(int **)(self + 0x15C);
        idx2 = t1[0x814 / 4];
        entry = (int *)((char *)D_0028CA88 + idx2 * 0x28);
        buf[0x10 / 4] = func_0019F310(entry[1], a1);
    }
    return buf;
}

/* Override ee-gcc's default .align 3 (8-byte) function alignment so the
 * matched body lands at its expected 4-aligned VMA offset 0x114 (the
 * VMA 0x1C0AD8 is 4-aligned but not 8-aligned within this .o). */
__asm__(".align 2");

short func_001C0AD8(char *self) {
    char *sub = *(char **)(self + 0x15C);
    char *p = *(char **)(sub + 0x800);
    return *(short *)(p + 0x2);
}

INCLUDE_ASM("asm/nonmatchings/src/switch", func_001C0AE8);

int func_001C0BE0(char *self) {
    char *sub = *(char **)(self + 0x15C);
    char *p = *(char **)(sub + 0x800);
    return *(int *)(p + 0x4) == 0;
}

INCLUDE_ASM("asm/nonmatchings/src/switch", func_001C0BF4);
int func_001C0BF8(char *self)
{
    register int accum REG("$4");
    short *p = *(short **)(*(char **)(self + 0x15C) + 0x800);
    if (__builtin_abs((int)p[1]) < 0xBB9) {
        accum = 0;
        MATERIALIZE(accum);
        if (__builtin_abs((int)p[0]) < 0xBB9) goto done;
    }
    accum = 1;
done:
    MATERIALIZE(accum);
    return accum;
}
TRAILING_PAD_NOP();
extern int D_00632010;
extern int func_0013A0F8(int handle, int size, const char *file, int line);
extern unsigned char D_004BEFD0[];
extern unsigned int D_0028CA88[];
extern int func_0019F310(int x, void *y);
typedef struct { long long w[4]; } __attribute__((packed)) SwitchBuf20;
int *func_001C0C40(char *self, void *arg1)
{
    int *buf = (int *)func_0013A0F8(D_00632010, 0x20, D_00618630, 0x12C);
    int *entry;
    *(SwitchBuf20 *)buf = *(SwitchBuf20 *)D_004BEFD0;
    if (((int *)arg1)[0x30 / 4] != 0) {
        buf[0x14 / 4] = 1;
    } else {
        buf[0x14 / 4] = 0;
    }
    entry = (int *)((char *)D_0028CA88 + (*(int **)(self + 0x15C))[0x814 / 4] * 0x28);
    buf[0xC / 4] = func_0019F310(entry[0], arg1);
    KEEP_LIVE_MEM(buf);
    {
        register void *a1 REG("$5") = arg1;
        register int *t1 REG("$3");
        register int idx2 REG("$2");
        KEEP_LIVE(a1);
        t1 = *(int **)(self + 0x15C);
        idx2 = t1[0x814 / 4];
        entry = (int *)((char *)D_0028CA88 + idx2 * 0x28);
        buf[0x10 / 4] = func_0019F310(entry[1], a1);
    }
    return buf;
}
