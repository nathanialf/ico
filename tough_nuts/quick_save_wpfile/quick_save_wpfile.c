#include "common.h"

extern int D_0062BB80;

extern void sprintf(void *a0, char *a1);
extern int debugSceOpen(void *a0, int a1);
extern void debug_StdPrintfDummy(int a0, ...);
extern void FlushCache(int a0);
extern void sceRead(int a0, void *a1, int a2);
extern int debugSceClose(int a0);
extern int D_0062A870;
extern char D_00614220[], D_0062DA28[], D_0062DA38[], D_0062DA40[], D_0062DA48[];
extern unsigned char D_0070BC70[];
extern signed char D_0070BC7F[];

int group_create(void) {
    char buf[0x70];
    int r;
    int i;
    signed char *p;
    signed char *end;
    signed char *iq;
    signed char (*ep)[];
    D_0062A870 = 1;
    sprintf(buf, D_0062DA28);
    r = debugSceOpen(buf, 1);
    if (r < 0) {
        debug_StdPrintfDummy((int) D_00614220);
        D_0062A870 = 0;
        return 0;
    }
    FlushCache(0);
    i = 0x1F;
    iq = (signed char *) D_0070BC70 + i;
    do {
        *iq = -1;
        iq--;
        i--;
    } while (i >= 0);
    ep = &D_0070BC7F;
    end = *ep + 0x11;
    sceRead(r, D_0070BC7F, 0x10);
    debugSceClose(r);
    p = D_0070BC7F - 0xF;
    do {
        debug_StdPrintfDummy((int) D_0062DA38, *p);
        p++;
    } while ((int) p < (int) end);
    debug_StdPrintfDummy((int) D_0062DA40);
    debug_StdPrintfDummy((int) D_0062DA48);
    D_0062A870 = 0;
    return 1;
}



INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_tool", group_select);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_tool", point_delete);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_tool", point_insert);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_tool", quick_load_wpfile);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_tool", ExtractWayData);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_tool", wp_print_out);

extern int D_0062AF84;
extern int D_0070BBFC[];
extern unsigned char D_006141F8[];
extern void traceLine(int, int, int, void *);
extern char *visible_waypoint_of_all(int *, float);

int draw_way_group(void) {
    int *p;
    int v;

extern char D_004CB2B0[];


    if (D_0062AF84 & 1) {
        unsigned int color = 0xFF000000;
        traceLine(0x12, 0x36, color, D_006141F8);
    }
    v = D_0070BBFC[0];
    if (v & 0x20) {
        p = (int *)visible_waypoint_of_all((int *)D_004CB2B0, 60.0f);
        if (p == 0) {
            return 0;
        }
        D_0062BB80 = p[1];
        if (p[1] >= 0) {
            p[10] ^= 1;
        }
    } else if (v & 0x40) {
        return -1;
    }
    return 0;
}

/* m2c scaffold from asm/aug6/nonmatchings/fumi/src/way_tool/way_toolDL.s (target mipsel-gcc-c, context-free).
 * NOT a match — reshape into a goto-CFG-mirror + recover intent (see decomp-match skill). */
extern void debug_StdPrintfDummy(int a0, ...);
extern void sprintf(void *a0, char *a1);
extern int debugSceOpen(void *a0, int a1);
extern void sceWrite(int a0, void *a1, int a2);
extern int debugSceClose(int a0);
extern char D_00614208[];
extern int D_0062A870;
extern char D_0062DA28[];
extern char D_0062DA30[];
extern unsigned char D_0070BC70[];

int way_toolDL(void) {
    char buf[0x70];
    int s0;
    int i;
    unsigned char *p;
    D_0062A870 = 1;
    sprintf(buf, D_0062DA28);
    s0 = debugSceOpen(buf, 0x202);
    if (s0 < 0) {
        debug_StdPrintfDummy((int)D_00614208);
        D_0062A870 = 0;
        return 0;
    }
    i = 0xF;
    p = &D_0070BC70[i];
    do {
        *p = i;
        p--;
        i--;
    } while (i >= 0);
    sceWrite(s0, D_0070BC70, 0x10);
    debugSceClose(s0);
    debug_StdPrintfDummy((int)D_0062DA30);
    D_0062A870 = 0;
    return 1;
}


INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_tool", debug_WayTool);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_tool", play_way);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_tool", point_nige);

extern void CheckPoint(void);
extern void func_00178DD8(int a0);
extern void lt_fade_status(int a0);
extern void func_001790A8(void *a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern void gflagOff(void *a0, int a1);
extern void _ACTWait(int a0);
extern int func_0012A958(int a0);
extern void *ContinueCorrectPosition(void *a0);
extern void sceVu0SubVector(void *a0, void *a1, void *a2);
extern void gflagChk(void *a0, void *a1);
extern void func_001790E8(void *a0);
extern void scpTrans(void *a0, short a1);

typedef struct { long long _0; long long _8; } WpData16;
extern WpData16 D_00614370;
extern void *D_00629DE4;
extern int D_0062A894;
extern void *D_0062BBF0;

void quick_save_wpfile(int arg0) {
    volatile int home;
    WpData16 buf2;
    WpData16 buf1;
    void *ret;
    void *t;

    home = arg0;
    CheckPoint();
    func_00178DD8(7);
    lt_fade_status(0x33);
    D_0062A894 = 1;
    func_001790A8(D_00629DE4);
    stage_KillPlayBgAnimation(0x228, 1, 0);
    gflagOff(D_00629DE4, 0x12D);
    while (func_0012A958(0x228) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    gflagOff(D_00629DE4, 0);
    buf2 = D_00614370;
    ret = ContinueCorrectPosition(D_00629DE4);
    sceVu0SubVector(&buf1, &buf2, ret);
    gflagChk(D_00629DE4, &buf1);
    func_001790E8(D_00629DE4);
    D_0062A894 = 0;
    lt_fade_status(0x32);
    _ACTWait(0x3C);
    t = D_0062BBF0;
    if (t != 0) {
        scpTrans(t, 0x50);
        D_0062BBF0 = 0;
    }
    _ACTWait(0);
}


INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_tool", cursor_control);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_tool", func_00204EF0);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_tool", func_002050B0);


/* recovered struct shapes */
typedef struct {
    unsigned int       f_4;  /* 0x04 */
} S_004CB550;  /* stride 0x8 */

/* end struct shapes */
