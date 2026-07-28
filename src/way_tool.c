#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/way_tool", group_create);

INCLUDE_ASM("asm/nonmatchings/src/way_tool", group_select);

INCLUDE_ASM("asm/nonmatchings/src/way_tool", point_delete);

INCLUDE_ASM("asm/nonmatchings/src/way_tool", point_insert);

INCLUDE_ASM("asm/nonmatchings/src/way_tool", quick_load_wpfile);

INCLUDE_ASM("asm/nonmatchings/src/way_tool", ExtractWayData);

INCLUDE_ASM("asm/nonmatchings/src/way_tool", wp_print_out);

extern char D_004D06A0[];
extern unsigned char D_0061B668[];
extern int D_00632CBC;
extern int D_00633878;
extern int D_0071257C[];
extern void traceLine(int, int, int, void *);
extern char *visible_waypoint_of_all(int *, float);

int draw_way_group(void) {
    int *p;
    int v;

extern char D_004D06A0[];


    if (D_00632CBC & 1) {
        unsigned int color = 0xFF000000;
        traceLine(0x12, 0x36, color, D_0061B668);
    }
    v = D_0071257C[0];
    if (v & 0x20) {
        p = (int *)visible_waypoint_of_all((int *)D_004D06A0, 60.0f);
        if (p == 0) {
            return 0;
        }
        D_00633878 = p[1];
        if (p[1] >= 0) {
            p[10] ^= 1;
        }
    } else if (v & 0x40) {
        return -1;
    }
    return 0;
}

extern char D_0061B678[];
extern int D_00632590;
extern char D_006338A0[];
extern char D_006338A8[];
extern unsigned char D_007125F0[];
extern void debug_assertMessage();
extern int func_001AA4F0(void *a0, int a1);
extern int func_001AA550(int a0);
extern void func_00247C30(int a0, void *a1, int a2);
extern void func_00264DF8(void *a0, char *a1);

int way_toolDL(void) {
    char buf[0x70];
    int s0;
    int i;
    unsigned char *p;
    D_00632590 = 1;
    func_00264DF8(buf, D_006338A0);
    s0 = func_001AA4F0(buf, 0x202);
    if (s0 < 0) {
        debug_assertMessage((int)D_0061B678);
        D_00632590 = 0;
        return 0;
    }
    i = 0xF;
    p = &D_007125F0[i];
    do {
        *p = i;
        p--;
        i--;
    } while (i >= 0);
    func_00247C30(s0, D_007125F0, 0x10);
    func_001AA550(s0);
    debug_assertMessage((int)D_006338A8);
    D_00632590 = 0;
    return 1;
}

extern int iosPadStickCameraCoord(void *a0, int a1, int a2, int a3);
extern void iosPadNormalizeStick(void *a0);
extern void ACTDebugMove(int a0, int a1);
extern char D_00280FC0[];
extern int D_00631B00;

void debug_WayTool(volatile int a0) {
    int s1 = *(int *)(a0 + 0x164);
    void *s0 = (void *)(s1 + 0x2C8);
    iosPadStickCameraCoord(s0, 0, 0, D_00280FC0);
    for (;;) {
        iosPadNormalizeStick(s0);
        if (a0 == D_00631B00 && (*(int *)(s1 + 0x2D4) & 1)) {
            ACTDebugMove(a0, 1);
        }
        _ACTWait(1);
    }
}

extern int D_00275250[];
extern int D_006338E8;
extern int D_00633F8C;
extern int D_00631AE4;
extern float D_006314A4;
extern void actConte11Jimaku(float f);
extern void actCreateSubThread(void *f, int a1);
extern int actSt25aQueenDeadChk(int a0);
extern void actSt25aQueenDead(int a0, int a1, int a2, float f12, float f13);
extern int fightSoundClose(void);
extern void func_0017B258(int a0);
extern void func_00192040(void);
extern void func_00207A88(volatile int a0);
extern void play_way(volatile int a0);
extern void scpPlayStart(int a0, int *a1, int a2, int a3, int a4);
extern int scpPlayEnd(void);
extern void scpTrans(int a0, int a1);
extern void stage_CalcAnimationParent(int a0, int a1);

void func_002071E8(volatile int a0) {
    func_0017B258(6);
    *(int *)(actSt25aQueenDeadChk(0x924) + 0x16C) = 0;
    *(int *)(actSt25aQueenDeadChk(0x925) + 0x16C) = 0;
    actCreateSubThread(func_00207A88, 0x15);
    scpPlayStart(0xC, &D_006338E8, 0, 1, 1);
    { int v = D_006338E8; while (v == 0) { _ACTWait(1); v = D_006338E8; } }
    actConte11Jimaku(6.0f);
    actCreateSubThread(play_way, 0x15);
    func_00192040();
    while (fightSoundClose() != 0) { _ACTWait(1); }
    D_00633F8C = 0;
    for (;;) {
        if (D_00633F8C != 0) goto done;
        if ((D_00275250[1] & 0x800) != 0) {
            if (scpPlayEnd() == 0) break;
        }
        _ACTWait(1);
    }
    if (D_00633F8C != 0) goto done;
    if (D_006338E8 == 0) goto done;
    stage_CalcAnimationParent(0x44, 0);
    scpTrans(D_006338E8, 0x80);
    D_006338E8 = 0;
done:
    actSt25aQueenDead(1, D_00631AE4, 0, D_006314A4, 1.0f);
}

INCLUDE_ASM("asm/nonmatchings/src/way_tool", play_way);

INCLUDE_ASM("asm/nonmatchings/src/way_tool", point_nige);

INCLUDE_ASM("asm/nonmatchings/src/way_tool", quick_save_wpfile);

INCLUDE_ASM("asm/nonmatchings/src/way_tool", cursor_control);

INCLUDE_ASM("asm/nonmatchings/src/way_tool", func_00207A88);

INCLUDE_ASM("asm/nonmatchings/src/way_tool", func_00207AB0);

INCLUDE_ASM("asm/nonmatchings/src/way_tool", func_00207C48);

