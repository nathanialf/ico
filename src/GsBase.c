#include "common.h"

#include "vu0.h"

INCLUDE_ASM("asm/nonmatchings/src/GsBase", gsb_SetFrame);
INCLUDE_ASM("asm/nonmatchings/src/GsBase", gsb_Init);
INCLUDE_ASM("asm/nonmatchings/src/GsBase", gsb_Reduction);
INCLUDE_ASM("asm/nonmatchings/src/GsBase", gsb_KeepFrameBuffer);
INCLUDE_ASM("asm/nonmatchings/src/GsBase", gsb_fade);
INCLUDE_ASM("asm/nonmatchings/src/GsBase", gsb_SetMotionBlur);
INCLUDE_ASM("asm/nonmatchings/src/GsBase", gsb_scissorOnDemo);
INCLUDE_ASM("asm/nonmatchings/src/GsBase", gsb_controlBrightness);
INCLUDE_ASM("asm/nonmatchings/src/GsBase", gsb_antiAlias);
extern int dl_GetPri(void);
extern void dl_SetDLPriority();
extern void gif_EndPacketPath1(void);
extern void gif_SetGsReg(int a0, long long a1);
extern void gif_StartPacketPriPath1(int a0);

void gsb_setNormalReg(void) {
    dl_SetDLPriority();
    gif_StartPacketPriPath1(dl_GetPri());
    gif_SetGsReg(0x47, 0x50000);
    gif_SetGsReg(0x4E, 0x300000C0);
    gif_SetGsReg(0x4A, 0);
    gif_SetGsReg(0x3B, 0x8000000080LL);
    gif_EndPacketPath1();
}
void gsb_setSemitransReg(void) {
    dl_SetDLPriority();
    gif_StartPacketPriPath1(dl_GetPri());
    gif_SetGsReg(0x47, 0x5140D);
    gif_SetGsReg(0x4E, 0x300000C0);
    gif_SetGsReg(0x4A, 0);
    gif_SetGsReg(0x3B, 0x810000807FLL);
    gif_EndPacketPath1();
}
void gsb_setSpecularReg(void) {
    dl_SetDLPriority();
    gif_StartPacketPriPath1(dl_GetPri());
    gif_SetGsReg(0x47, 0x5C000);
    gif_SetGsReg(0x4E, 0x1300000C0LL);
    gif_SetGsReg(0x4A, 0);
    gif_SetGsReg(0x3B, 0x8000000080LL);
    gif_EndPacketPath1();
}
void gsb_setParticleReg(void) {
    dl_SetDLPriority();
    gif_StartPacketPriPath1(dl_GetPri());
    gif_SetGsReg(0x47, 0x50000);
    gif_SetGsReg(0x4E, 0x1300000C0LL);
    gif_SetGsReg(0x4A, 0);
    gif_SetGsReg(0x3B, 0x8000000080LL);
    gif_EndPacketPath1();
}
INCLUDE_ASM("asm/nonmatchings/src/GsBase", gsb_MakeCommonMatrix);
INCLUDE_ASM("asm/nonmatchings/src/GsBase", gsb_SetGsDefault);
INCLUDE_ASM("asm/nonmatchings/src/GsBase", gsb_filmNoise);
INCLUDE_ASM("asm/nonmatchings/src/GsBase", gsb_PostEffect);
INCLUDE_ASM("asm/nonmatchings/src/GsBase", gsb_InitGSSystem);
INCLUDE_ASM("asm/nonmatchings/src/GsBase", gsb_UpdateGSSystem);
INCLUDE_ASM("asm/nonmatchings/src/GsBase", gsb_ResetGSSystem);
INCLUDE_ASM("asm/nonmatchings/src/GsBase", gsb_SetVSMatrixSub);
INCLUDE_ASM("asm/nonmatchings/src/GsBase", gsb_SetVSMatrix);
INCLUDE_ASM("asm/nonmatchings/src/GsBase", gsb_ClipBox);
INCLUDE_ASM("asm/nonmatchings/src/GsBase", appendLogFile);
INCLUDE_ASM("asm/nonmatchings/src/GsBase", gsb_FilmNoiseTool);
INCLUDE_ASM("asm/nonmatchings/src/GsBase", gsb_StageSettingTool);
INCLUDE_ASM("asm/nonmatchings/src/GsBase", updateOtherEditingLockFlag);
INCLUDE_ASM("asm/nonmatchings/src/GsBase", createLockFile);
INCLUDE_ASM("asm/nonmatchings/src/GsBase", removeLockFile);
INCLUDE_ASM("asm/nonmatchings/src/GsBase", gsb_StageSetting);
extern unsigned char D_0067BCD0[];

void gsb_SetBGColor(void *a0, int r, int g, int b) {
    unsigned long long bg = ((long long)b << 16) | ((long long)g << 8);
    unsigned long long v = r | 0x3F80000000000000ULL;
    v |= bg;
    *(int *)&D_0067BCD0[0] = r;
    v |= 0x80000000;
    *(int *)&D_0067BCD0[4] = g;
    *(int *)&D_0067BCD0[8] = b;
    *(int *)&D_0067BCD0[0xC] = 0x80;
    *(unsigned long long *)((char *)a0 + 0x1F0) = v;
    *(unsigned long long *)((char *)a0 + 0x100) = v;
}
void gsb_GetBGColor(unsigned char *a0)
{
    a0[0] = D_0067BCD0[0];
    a0[1] = D_0067BCD0[4];
    a0[2] = D_0067BCD0[8];
    a0[3] = D_0067BCD0[0xC];
}
INCLUDE_ASM("asm/nonmatchings/src/GsBase", gsb_ResetFilmNoise);
extern float D_00639F88;
extern float D_00639F90;

void gsb_SetZoom(float a, float b) {
    D_00639F88 = a;
    D_00639F90 = b;
}
INCLUDE_ASM("asm/nonmatchings/src/GsBase", gsb_SyncGSSystem);
extern int stage_no;
extern char D_005F5D90[];
extern char D_0054E488[];
extern char D_0054E4A8[];
extern char D_0054E4D8[];
extern char D_0028F720[];
int gsb_LoadStageSettings(void) {
    char buf[0x100];
    int fd;
    sprintf(buf, D_0054E488, D_005F5D90 + stage_no * 0x194);
    fd = debugSceOpen(buf, 1);
    if (fd < 0) {
        debug_StdPrintfDummy(D_0054E4A8);
    } else {
        debug_StdPrintfDummy(D_0054E4D8, buf);
        sceRead(fd, D_0028F720, 0x1D0);
        debugSceClose(fd);
    }
    return -1;
}
INCLUDE_ASM("asm/nonmatchings/src/GsBase", gsb_SaveStageSettings);
void gsb_ClearFrameBuffer(void) {
    volatile int local[96];
}
void gsb_ResetSnap(void) {
}
void gsb_TakeSnap(void) {
}
INCLUDE_ASM("asm/nonmatchings/src/GsBase", lockOtherEditing);
INCLUDE_ASM("asm/nonmatchings/src/GsBase", unlockOtherEditing);
