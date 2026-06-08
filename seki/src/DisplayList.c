#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/DisplayList", dl_Init);

int dl_Clear(void) {
    return 0x14;
}

extern int D_00629F5C;

int dl_Swap(void) {
    return (0x3200 / D_00629F5C) / 2;
}

extern int D_0062BAE0, D_0062BAE4, D_0062BAE8, D_0062BAEC, D_0062BAF0;

void dl_PushPriority(void) {
    D_0062BAE0 = 0;
    D_0062BAF0 = 0x80;
    D_0062BAEC = 0x80;
    D_0062BAE8 = 0x80;
    D_0062BAE4 = 0x80;
}

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/DisplayList", dl_PopPriority);

extern int D_0062C25C;
extern int D_0062C260;
extern int D_0070A7C8[];
extern int D_0070A5C0[];
extern void func_001F8848(void);
extern void gif_SpriteSensitive(void);
extern void pac_openDmaTag(void);

void dl_Debug(void)
{
    int flag = D_0062C25C ^ 1;
    int *src = (int *)((char *)D_0070A7C8 + flag * 0x34);
    char *dst = (char *)D_0070A5C0;
    int i;
    D_0062C25C = flag;
    D_0062C260 = 0;
    for (i = 0xC; i >= 0; i--) {
        int v = *src;
        *(int *)dst = 0;
        src++;
        *(int *)(dst + 0x24) = v;
        *(int *)(dst + 0x20) = v;
        dst += 0x28;
    }
    func_001F8848();
    gif_SpriteSensitive();
    pac_openDmaTag();
}

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/DisplayList", dl_CloseDma);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/DisplayList", dl_Out);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/DisplayList", dl_SetDLPriority);

extern int D_00613700[];
extern void debug_assertMessage(int *a0, int a1);

void dl_OpenDma(void)
{
    int *entry = &D_0070A5C0[D_0062C260 * 10];
    unsigned int end = entry[9];
    unsigned int start = entry[1];
    unsigned int count = (end - start) >> 4;
    return debug_assertMessage(D_00613700, count - 1);
}

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/DisplayList", dl_GetPri);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/DisplayList", func_001F8660);


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
    unsigned int       f_4;  /* 0x04 */
    unsigned long long f_8;  /* 0x08 */
    unsigned int       f_10;  /* 0x10 */
    unsigned long long f_18;  /* 0x18 */
    unsigned int       f_24;  /* 0x24 */
} S_0070A5C0;  /* stride 0x28 */

typedef struct {
    char               f_0;  /* 0x00 */
    char               f_1;  /* 0x01 */
} S_004C3750;  /* stride 0x2 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_0070A830;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_00613750;  /* stride 0x4 */

/* end struct shapes */
