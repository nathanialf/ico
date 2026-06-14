#include "common.h"
#include "vu0.h"

typedef struct Light { char _pad0[0x44]; short f_44; char _pad46[2]; struct Light *next; struct Light *prev; } Light;
typedef struct AmbientVolume { char _pad0[0x90]; int f_90; struct AmbientVolume *next; struct AmbientVolume *prev; } AmbientVolume;

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Light", light_killLinkLight);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Light", light_killLinkAmbient);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Light", light_AddLight);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Light", light_getNearLight);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Light", light_getAmbientLight);

extern unsigned char D_0066CA10[];

void light_MakeLightMatrix(unsigned char *a0) {
    a0[0] = D_0066CA10[0];
    a0[1] = D_0066CA10[4];
    a0[2] = D_0066CA10[8];
    a0[3] = D_0066CA10[0xC];
}

extern float D_00629EC0;
extern float D_00629EC8;

void light_DispVolume(float a0, float a1) {
    D_00629EC0 = a0;
    D_00629EC8 = a1;
}

extern int func_0023EB60(int a0, int a1);
extern void debug_assertMessage();
extern void gsb_SetBGColor(void);
extern int D_00629F18;
extern char D_0054EB30[];

int light_GetColorAnalog(void) {
    if (func_0023EB60(1, 0)) {
        if (++D_00629F18 >= 0xB) {
            debug_assertMessage(D_0054EB30);
            gsb_SetBGColor();
            D_00629F18 = 0;
        }
        return 1;
    }
    D_00629F18 = 0;
    return 0;
}

extern int D_00629C90;
extern char D_005EBC88[];
extern char D_0054EB50[];
extern char D_0054EB70[];
extern char D_0054EBA0[];
extern char D_002714A0[];
extern void func_00261188(void *a0, void *a1, void *a2);
extern int func_001A7A88(void *a0, int a1);
extern void func_00243EE0(int a0, void *a1, int a2);
extern void func_001A7AE8(int a0);

int light_DrawCursor(void) {
    char buf[0x100];
    int s0;
    func_00261188(buf, D_0054EB50, &D_005EBC88[D_00629C90 * 0x190]);
    s0 = func_001A7A88(buf, 1);
    if (s0 < 0) {
        debug_assertMessage(D_0054EB70);
    } else {
        debug_assertMessage(D_0054EBA0, buf);
        func_00243EE0(s0, D_002714A0, 0x130);
        func_001A7AE8(s0);
    }
    return -1;
}

extern int D_00629C90;
extern char D_005EBC88[];
extern char D_0054EB50[];
extern char D_0054EBC0[];
extern char D_0054EBF0[];
extern char D_002714A0[];
extern void func_00261188(void *a0, void *a1, void *a2);
extern int func_001A7A88(void *a0, int a1);
extern void func_00244150(int a0, void *a1, int a2);
extern void func_001A7AE8(int a0);

int light_Tool(void) {
    char buf[0x100];
    int s0;
    func_00261188(buf, D_0054EB50, &D_005EBC88[D_00629C90 * 0x190]);
    s0 = func_001A7A88(buf, 0x602);
    if (s0 < 0) {
        debug_assertMessage(D_0054EBC0);
    } else {
        func_00244150(s0, D_002714A0, 0x130);
        debug_assertMessage(D_0054EBF0, buf);
        func_001A7AE8(s0);
    }
    return -1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Light", light_InitLight);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Light", light_KillAllFixLight);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Light", light_KillAllAmbient);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Light", light_AddAmbientObject);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Light", light_resetFlatLight);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Light", func_00115CA8);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Light", func_00116308);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Light", func_001163E8);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Light", func_001169D8);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Light", func_00116CB8);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Light", func_00117038);

extern int D_0062BF30;
extern int D_0062BF34;
extern int D_00629F70;

void func_00117B80(void) {
    D_0062BF30 = 0;
    D_0062BF34 = 0;
    D_00629F70 = 0;
}

extern int D_0062BF38;
extern void light_KillAllFixLight(char *node);

void func_00117B90(void)
{
    Light *p = (Light *)D_0062BF30;
    while (p != 0) {
        short v = p->f_44;
        if (v < 4) {
            if (v >= 2) {
                Light *node = p;
                p = p->prev;
                light_KillAllFixLight((char *)node);
                continue;
            }
        }
        p = p->prev;
    }
    D_0062BF38 = 0;
}

extern void light_KillAllAmbient(char *node);

void func_00117BF0(void)
{
    AmbientVolume *p = (AmbientVolume *)D_0062BF34;
    while (p != 0) {
        int v = p->f_90;
        if (v < 3) {
            if (v >= 0) {
                AmbientVolume *node = p;
                p = p->prev;
                light_KillAllAmbient((char *)node);
                continue;
            }
        }
        p = p->prev;
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Light", func_00117C48);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Light", func_00117CB8);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Light", func_00117D78);

float func_00118048(float a0) {
    register float ret __asm__("$f0");
    __asm__ __volatile__(
        ".set noreorder\n"
        "mfc1 $6, $f12\n"
        "qmtc2.ni $6, $vf1\n"
        ".word 0x4A0103BD\n"
        "vwaitq\n"
        "cfc2.ni $7, $vi22\n"
        "mtc1 $7, $f0\n"
        ".set reorder\n"
        : "=f"(ret) :: "$6", "$7");
    return ret;
}

void func_00118068(void) {
    __asm__ __volatile__(
        ".set noreorder\n"
        "vmove.xyzw $vf7, $vf0\n"
        "vmr32.xyzw $vf6, $vf7\n"
        "vmr32.xyzw $vf5, $vf6\n"
        "vmr32.xyzw $vf4, $vf5\n"
        "viaddi $vi15, $vi0, 0x0\n"
        ".set reorder\n");
}

void func_00118088(void) {
    __asm__ __volatile__(
        ".set noreorder\n"
        "vmove.xyzw $vf7, $vf0\n"
        "vmr32.xyzw $vf6, $vf7\n"
        "vmr32.xyzw $vf5, $vf6\n"
        "vmr32.xyzw $vf4, $vf5\n"
        "viaddi $vi15, $vi0, 0x0\n"
        ".set reorder\n");
}

void func_001180A8(void) {
    VU0_MEM("vsqi.xyzw $vf4, ($vi15++)");
    VU0_MEM("vsqi.xyzw $vf5, ($vi15++)");
    VU0_MEM("vsqi.xyzw $vf6, ($vi15++)");
    VU0_MEM("vsqi.xyzw $vf7, ($vi15++)");
    VU0_NOP();
}

void func_001180C0(void) {
    VU0_MEM("vlqd.xyzw $vf7, (--$vi15)");
    VU0_MEM("vlqd.xyzw $vf6, (--$vi15)");
    VU0_MEM("vlqd.xyzw $vf5, (--$vi15)");
    VU0_MEM("vlqd.xyzw $vf4, (--$vi15)");
    VU0_NOP();
}

void func_001180D8(void *a0) {
    __asm__ __volatile__(
        ".set noreorder\n"
        "lqc2 $vf8, 0x0($4)\n"
        "vmulax.xyzw $ACC, $vf4, $vf8x\n"
        "vmadday.xyzw $ACC, $vf5, $vf8y\n"
        "vmaddaz.xyzw $ACC, $vf6, $vf8z\n"
        "vmaddw.xyzw $vf7, $vf7, $vf8w\n"
        ".set reorder\n" : : : "memory");
}

void func_001180F8(void *a0) {
    VU0_LSV_R(lqc2, 8, 0x0, a0);
    VU0_V2OP(vmove.xyzw, 7, 8);
    VU0_NOP();
}

void func_00118108(void) {
    VU0_V2OP(vmove.xyzw, 7, 0);
    VU0_NOP();
}

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Light", func_00118118);


/* recovered struct shapes */
typedef struct {
    unsigned int       f_4;  /* 0x04 */
    unsigned int       f_C;  /* 0x0C */
    unsigned char      f_54;  /* 0x54 */
    unsigned char      f_55;  /* 0x55 */
    unsigned char      f_57;  /* 0x57 */
    unsigned int       f_58;  /* 0x58 */
    unsigned int       f_5C;  /* 0x5C */
    unsigned char      f_AC;  /* 0xAC */
    unsigned char      f_AD;  /* 0xAD */
    unsigned char      f_AE;  /* 0xAE */
    unsigned char      f_AF;  /* 0xAF */
} S_002715D0;  /* stride 0x58 */

typedef struct {
    unsigned int       f_80;  /* 0x80 */
    unsigned int       f_90;  /* 0x90 */
    unsigned int       f_94;  /* 0x94 */
    unsigned int       f_98;  /* 0x98 */
    unsigned int       f_9C;  /* 0x9C */
    unsigned int       f_A0;  /* 0xA0 */
    unsigned int       f_A4;  /* 0xA4 */
    unsigned int       f_A8;  /* 0xA8 */
    unsigned char      f_D0;  /* 0xD0 */
    unsigned char      f_D4;  /* 0xD4 */
    unsigned char      f_D8;  /* 0xD8 */
    unsigned int       f_E8;  /* 0xE8 */
    unsigned int       f_F8;  /* 0xF8 */
    unsigned int       f_FC;  /* 0xFC */
    unsigned int       f_100;  /* 0x100 */
    unsigned int       f_104;  /* 0x104 */
    unsigned char      f_110;  /* 0x110 */
    unsigned char      f_114;  /* 0x114 */
    unsigned char      f_118;  /* 0x118 */
    unsigned char      f_11C;  /* 0x11C */
    unsigned char      f_120;  /* 0x120 */
} S_002714A0;

typedef struct {
    unsigned int       f_4;  /* 0x04 */
    unsigned int       f_8;  /* 0x08 */
} S_00272528;

typedef struct {
    unsigned int       f_4;  /* 0x04 */
    unsigned int       f_8;  /* 0x08 */
    unsigned int       f_C;  /* 0x0C */
} S_0066CA10;

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_002724E0;  /* stride 0x4 */

typedef struct {
    unsigned int       f_4;  /* 0x04 */
} S_002724E8;  /* stride 0x8 */

/* end struct shapes */
