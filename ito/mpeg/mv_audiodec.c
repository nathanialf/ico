#include "common.h"

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_audiodec", audioDecCreate);
INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_audiodec", audioDecEndPut);
INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_audiodec", sendToIOP2area);
INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_audiodec", audioDecSendToIOP);
INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_audiodec", pcmCallback);
INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_audiodec", audioDecDelete);
extern int SgStPcmStop(unsigned long long a0);
extern void SgStPcmVolume(unsigned long long a0, unsigned int a1, int a2);

void audioDecReset(int *self)
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
int audioDecIsPreset(int *self) {
    return *(int *)((char *)self + 0x54) >= *(int *)((char *)self + 0x48);
}
extern int SgStPcmLseek(unsigned int a0, unsigned int a1);
extern int SgStPcmPlay(unsigned long long a0);

void audioDecStart(int *self)
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
int audioDecPause(int a0)
{
    *(int *)a0 = 3;
    SgStPcmVolume(3, 0, 0);
    SgStPcmStop(3);
    return 0;
}
void audioDecResume(int *self)
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
