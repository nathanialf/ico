#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/debug_exception", initLineTraceTable);
INCLUDE_ASM("asm/nonmatchings/src/debug_exception", traceLine);
INCLUDE_ASM("asm/nonmatchings/src/debug_exception", dispSource);
INCLUDE_ASM("asm/nonmatchings/src/debug_exception", display);
INCLUDE_ASM("asm/nonmatchings/src/debug_exception", debugEEExceptionMain);
INCLUDE_ASM("asm/nonmatchings/src/debug_exception", debugIOPExceptionMain);
INCLUDE_ASM("asm/nonmatchings/src/debug_exception", debugExceptionInit);
void debugIOPExceptionInit(void) {}
void debug_assertMessage(char *file, int line, char *mes) {
    for (;;)
        ;
}
void debug_assert(char *file, int line) {
    for (;;)
        ;
}
typedef unsigned int u128_dbgscr __attribute__((mode(TI)));
/* sceVif1Packet: 0x20 bytes (two per drawSprite frame at sp+0x00 / sp+0x20).
 * Field offsets 0x00/0x04/0x0C/0x14 are the ones the libpkt bodies in
 * src/cod/vendor_25EC00.c touch; 0x08/0x10/0x18 are unused here. */
typedef struct {
    int *cur;
    int *base;
    int *f_8;
    int *directTag;
    int *f_10;
    int *gifTag;
    int f_18[2];
} Vif1Packet;

extern void sceVif1PkInit();
extern void sceVif1PkReset();
extern void sceVif1PkCnt();
extern void sceVif1PkOpenDirectCode();
extern void sceVif1PkOpenGifTag(void *packet, u128_dbgscr tag);
extern void sceVif1PkAddGsData(void *packet, unsigned long long data);
extern int D_0063B370;
extern unsigned int D_0063B374;
extern unsigned int D_0063B378;
extern u128_dbgscr D_0061CF20[];
extern u128_dbgscr D_0061CF30[];
extern void CloseVif1DirectPacket(int a0);
extern void SendVif1DirectPacket(int *a0);

inline void OpenVif1DirectPacket(void *packet) {
    sceVif1PkInit(packet, (D_0063B370 << 13) | 0x70000000);
    sceVif1PkReset(packet);
    sceVif1PkCnt(packet, 0);
    sceVif1PkOpenDirectCode(packet, 0);
    D_0063B370 = (D_0063B370 + 1) & 1;
}
inline void SetPrimColor(int prim, int r, int g, int b, int a) {
    Vif1Packet packet;
    OpenVif1DirectPacket(&packet);
    sceVif1PkOpenGifTag(&packet, D_0061CF20[0]);
    sceVif1PkAddGsData(&packet, prim | 0x40);
    sceVif1PkAddGsData(&packet,
                       (unsigned long long)r | ((unsigned long long)g << 8) |
                           ((unsigned long long)b << 16) | ((unsigned long long)a << 24) |
                           ((unsigned long long)D_0063B374 << 32));
    CloseVif1DirectPacket((int)&packet);
    SendVif1DirectPacket((int *)&packet);
}
inline void SetPrimColorTex(int prim, int r, int g, int b, int a, int fst) {
    Vif1Packet packet;
    unsigned long long data;
    OpenVif1DirectPacket(&packet);
    sceVif1PkOpenGifTag(&packet, D_0061CF30[0]);
    data = prim | 0x10;
    if (fst != 0) {
        data |= 0x100;
    }
    sceVif1PkAddGsData(&packet, data);
    sceVif1PkAddGsData(&packet,
                       (unsigned long long)r | ((unsigned long long)g << 8) |
                           ((unsigned long long)b << 16) | ((unsigned long long)a << 24) |
                           ((unsigned long long)D_0063B378 << 32));
    CloseVif1DirectPacket((int)&packet);
    SendVif1DirectPacket((int *)&packet);
}
