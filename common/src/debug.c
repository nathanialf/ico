#include "common.h"

typedef struct { int w[6]; } AssertRec;
extern AssertRec D_006DE110[];

int debug_Assert(int a0) {
    return D_006DE110[a0].w[0];
}

extern void func_00265130(char *buf, const char *fmt, void *va);
extern void func_001AACE0(char *a0, int a1, char *a2);
extern void func_00260380(char *a0, int a1, char *a2);
extern void func_001AAD00(char *a0, int a1);
extern char D_0060D3B0[];
extern char D_0062CB40[];
extern char D_0062CB48[];

void debug_openLog(const char *fmt, ...) {
    char buf[0x100];
    func_00265130(buf, fmt, (char *)__builtin_next_arg(fmt) - 0x38);
    func_001AACE0(D_0060D3B0, 0x4F4, buf);
    func_00260380(D_0060D3B0, 0x4F4, D_0062CB40);
    func_001AAD00(D_0060D3B0, 0x4F5);
    func_00260380(D_0060D3B0, 0x4F5, D_0062CB48);
}

extern int D_0062ACCC;

void debug_LogPrintf(void) {
    char buf[0x100];
    D_0062ACCC = -1;
}

extern void func_00265130(char *buf, const char *fmt, void *va);
extern void *func_0026160C(char *buf);
extern void func_00244150(int target, char *buf, void *info);

void debug_SaveDebugOptionFile(const char *fmt, ...) {
    char buf[0x100];
    void *info;
    func_00265130(buf, fmt, (char *)__builtin_next_arg(fmt) - 0x38);
    info = func_0026160C(buf);
    func_00244150(D_0062ACCC, buf, info);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug", debug_GetDebugOption);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug", debug_SetDmaCallback);

extern unsigned int D_0062ACD4;
extern int func_00100230(int a, int b, int c);
extern void func_00100250(int a, int b);
extern void func_001A7C20(void);
extern void func_00100B40(int a);

void debug_VariableInit(void)
{
    if ((int)D_0062ACD4 != -1) {
        func_00100250(1, D_0062ACD4);
    }
    D_0062ACD4 = func_00100230(1, (int)func_001A7C20, -1);
    func_00100B40(1);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug", debug_Init);

extern int D_0062AF58;
extern int D_0062AF5C;
extern int D_0062AF60;
extern int D_0062B00C;
extern int D_0062AF64;
extern int D_0062AF68;
extern int D_0062AF6C;
extern void func_001A7480(void);
extern void debug_PrintCharacter(void);

void debug_Load(void) {
    func_001A7480();
    D_0062AF58 = 0;
    D_0062AF5C = 0;
    D_0062AF60 = 0;
    D_0062AF64 = 0;
    D_0062AF68 = 0;
    D_0062AF6C = 0;
    D_0062B00C = 0;
    *(volatile int *)0x10000010 = 0x82;
    *(volatile int *)0x10000810 = 0x82;
    debug_PrintCharacter();
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug", debug_MakeFont);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug", debug_makeBackImage);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug", debug_PrintCharacter);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug", debug_PrintFont);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug", debug_FlushFontWindow);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug", debug_FlushFont);

extern void debug_FlushFont(void);

void draw_batsu(void) {
    debug_FlushFont();
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug", draw_shikaku);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug", debug_brainBar);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug", debug_MakeBarString);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug", debug_DrawBar);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug", debug_DispBar);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug", debug_ResizeSnapShot);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug", debug_WriteBMP);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug", debug_SnapShot);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug", debug_DispQW);


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
    char               f_C;  /* 0x0C */
    char               f_D;  /* 0x0D */
    char               f_E;  /* 0x0E */
    char               f_F;  /* 0x0F */
    unsigned int       f_10;  /* 0x10 */
    short              f_14;  /* 0x14 */
    unsigned int       f_18;  /* 0x18 */
} S_006EB6D0;  /* stride 0x1C */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_0060D910;  /* stride 0x4 */

/* end struct shapes */
