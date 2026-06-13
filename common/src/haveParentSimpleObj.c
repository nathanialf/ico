#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/haveParentSimpleObj", ParentSimpleObjGeo);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/haveParentSimpleObj", ParentSimpleObjDL);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/haveParentSimpleObj", InitParentSimpleObjGeo);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/haveParentSimpleObj", func_001AA268);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/haveParentSimpleObj", func_001AA680);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/haveParentSimpleObj", func_001AAAD0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/haveParentSimpleObj", func_001AAC60);

void func_001AACD8(void) {
}

void func_001AACE0(void) {
    for (;;) {
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/haveParentSimpleObj", func_001AAD00);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/haveParentSimpleObj", func_001AAD88);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/haveParentSimpleObj", func_001AAE80);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/haveParentSimpleObj", func_001AAFA0);

extern int D_0062C14C;
extern int D_0062C150;
extern int D_0062C154;

void func_001AB108(void) {
    D_0062C14C = 0;
    D_0062C150 = 1;
    D_0062C154 = 0;
}

extern void *AllocPObj(void);
extern char D_0029F060[];

char *func_001AB120(void) {
    int idx = *(int *)((char *)AllocPObj() + 0xC);
    return D_0029F060 + idx * 0x64;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/haveParentSimpleObj", func_001AB158);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/haveParentSimpleObj", func_001AB1B0);

extern int D_0062B234;
extern unsigned short D_004AF010[];
extern unsigned char D_004AEE68[];
extern void func_001ABE38(void *a0, void *a1, int a2);

void func_001AB248(void *a0) {
    func_001ABE38(a0, &D_0062B234, 4);
    func_001ABE38(a0, D_004AF010, 0x2D80);
    func_001ABE38(a0, D_004AEE68, 0x1A0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/haveParentSimpleObj", func_001AB298);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/haveParentSimpleObj", func_001AB470);

extern unsigned short D_004AF010[];
extern int D_0062B234;
extern short D_0062B238;
extern void backStageSave(void);

void func_001AB720(void) {
    if (D_004AF010[0x21] == 0x82) {
        D_0062B238 = D_004AF010[0x22];
    }
    D_0062B234++;
    backStageSave();
}

extern void debug_assertMessage(char *p, int y);
extern char D_0060F2F8[];

void func_001AB750(int *self, int n, int a2)
{
    if (n != 0) {
        func_002604B8(self[0] + self[1], n);
    }
    self[1] += a2;
    debug_assertMessage(D_0060F2F8, self[1]);
}

extern void MakeGeneratorPacket(int a0);
extern int GetbufpGeneratorPacket(void);
extern int GetsizeGeneratorPacket(void);

void func_001AB7A8(int a0)
{
    MakeGeneratorPacket(a0);
    {
        int s0 = GetbufpGeneratorPacket();
        int s1 = GetsizeGeneratorPacket();
        return func_001AB750(a0, s0, s1);
    }
}

extern int GetbufpGeneratorPacket(void);
extern int GetsizeGeneratorPacket(void);
extern void func_002604B8(int a0, int a1, int a2);
extern void ReadGeneratorPacket(void);

void func_001AB7F0(int *a0)
{
    int s1 = GetbufpGeneratorPacket();
    int s2 = GetsizeGeneratorPacket();
    if (s1 != 0) {
        func_002604B8(s1, a0[0] + a0[1], s2);
    }
    a0[1] += s2;
    return ReadGeneratorPacket();
}

extern void actBoyHangBefore(int a0);
extern int actBoyItemAfter(void);
extern int actBoyCliffHesitate(void);

void func_001AB858(int a0)
{
    actBoyHangBefore(a0);
    {
        int s0 = actBoyItemAfter();
        int s1 = actBoyCliffHesitate();
        return func_001AB750(a0, s0, s1);
    }
}

extern int actBoyItemAfter(void);
extern int actBoyCliffHesitate(void);
extern void func_002604B8(int a0, int a1, int a2);
extern void actBoyReadyMove(void);

void func_001AB8A0(int *a0)
{
    int s1 = actBoyItemAfter();
    int s2 = actBoyCliffHesitate();
    if (s1 != 0) {
        func_002604B8(s1, a0[0] + a0[1], s2);
    }
    a0[1] += s2;
    return actBoyReadyMove();
}

void func_001AB908(void)
{
    int mask = 0xFFFF;
    char *p = D_004AF010;
    int i = 0x8B;
    p += 0xA80;
    do {
        *(short *)(p + 2) = 0;
        *(short *)(p + 4) = (short)mask;
        p += 0x40;
        i--;
    } while (i >= 0);
}

void func_001AB948(void) {
    long long *p = (long long *)D_004AF010;
    long long mask = -2;
    int i;
    for (i = 0xB5; i >= 0; i--) {
        *p &= mask;
        p = (long long *)((char *)p + 0x40);
    }
}

void func_001AB980(void) {
    long long *p = (long long *)D_004AF010;
    long long mask = -3;
    int i;
    for (i = 0xB5; i >= 0; i--) {
        *p &= mask;
        p = (long long *)((char *)p + 0x40);
    }
}

extern int *func_001AB470(int a0, int a3);

int *func_001AB9B8(int a0, int a1, int a2, int a3)
{
    int *p = func_001AB470(a0, a3);
    p[12] = a1;
    p[13] = a2;
    return p;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/haveParentSimpleObj", func_001AB9F8);


/* recovered struct shapes */
typedef struct {
    unsigned short     f_2;  /* 0x02 */
    unsigned long long f_40;  /* 0x40 */
    unsigned short     f_42;  /* 0x42 */
    unsigned short     f_44;  /* 0x44 */
} S_004AF010;  /* stride 0x40 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
    unsigned int       f_4;  /* 0x04 */
} S_004AE610;  /* stride 0x8 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_004AEE68;  /* stride 0x4 */

/* end struct shapes */
