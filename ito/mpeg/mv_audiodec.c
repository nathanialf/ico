#include "common.h"

extern int sceSifFreeIopHeap(int a0);
extern void debug_StdPrintfDummy(char *fmt, ...);
extern int SgStPcmClose(unsigned int a0);
extern void SgStPcmQuit(void);
extern char D_006231D0[];
extern char D_006231F0[];
extern int SgStPcmStop(unsigned long long a0);
extern void SgStPcmVolume(unsigned long long a0, unsigned int a1, int a2);
extern int SgStPcmLseek(unsigned int a0, unsigned int a1);
extern int SgStPcmPlay(unsigned long long a0);
/* prototypes: their order is the inline tail's emission order */
int audioDecDelete(int *self);
void audioDecReset(int *self);
int audioDecIsPreset(int *self);
void audioDecStart(int *self);
int audioDecPause(int a0);
void audioDecResume(int *self);
INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_audiodec", audioDecCreate);
inline int audioDecDelete(int *self)
{
    if (self[0x44 / 4]) {
        if (sceSifFreeIopHeap(self[0x44 / 4]) < 0) {
            debug_StdPrintfDummy(D_006231D0, self[0x44 / 4]);
        }
        debug_StdPrintfDummy(D_006231F0, self[0x44 / 4]);
        self[0x44 / 4] = 0;
    }
    if (*(signed char *)((char *)self + 0x61)) {
        SgStPcmClose(0);
    }
    if (*(signed char *)((char *)self + 0x62)) {
        SgStPcmClose(1);
    }
    if (*(signed char *)((char *)self + 0x60)) {
        SgStPcmQuit();
    }
    return 1;
}
inline void audioDecReset(int *self)
{
    SgStPcmVolume(3, 0, 0);
    SgStPcmStop(3);
    *(volatile int *)((char *)self + 0x50) = 0;
    *(volatile int *)((char *)self + 0) = 0;
    *(volatile int *)((char *)self + 0x2C) = 0;
    *(volatile int *)((char *)self + 0x34) = 0;
    *(volatile int *)((char *)self + 0x38) = 0;
    *(volatile int *)((char *)self + 0x40) = 0;
    *(volatile int *)((char *)self + 0x54) = 0;
    *(volatile int *)((char *)self + 0x4C) = 0;
}
INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_audiodec", audioDecEndPut);
inline int audioDecIsPreset(int *self) {
    return *(int *)((char *)self + 0x54) >= *(int *)((char *)self + 0x48);
}
inline void audioDecStart(int *self)
{
    SgStPcmLseek(0, 0);
    SgStPcmLseek(1, 0);
    if (*(signed char *)((char *)self + 0x58)) {
        int half = self[0x5C / 4] / 2;
        SgStPcmVolume(3, half, half);
    } else {
        SgStPcmVolume(1, 0, self[0x5C / 4]);
        SgStPcmVolume(2, self[0x5C / 4], 0);
    }
    SgStPcmPlay(3);
    self[0] = 2;
}
INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_audiodec", sendToIOP2area);
INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_audiodec", audioDecSendToIOP);
inline int audioDecPause(int a0)
{
    *(int *)a0 = 3;
    SgStPcmVolume(3, 0, 0);
    SgStPcmStop(3);
    return 0;
}
inline void audioDecResume(int *self)
{
    audioDecStart(self);
}
INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_audiodec", pcmCallback);
