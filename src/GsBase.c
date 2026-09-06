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
extern int stage_no;
extern char D_005F5D90[];
extern char D_0067BB88[];
extern char D_0054EF00[];
extern char D_0054EF40[];
extern char D_0054EF58[];
extern char D_0063A000[];
extern char D_0063A038[];
extern int D_00639F7C;

/* the line-2873 helper the PAL listing shows inlined at the head of
   updateOtherEditingLockFlag, createLockFile and removeLockFile */
/* static helper the listing places at GsBase.c line 2873, inlined at the head of
 * updateOtherEditingLockFlag, createLockFile and removeLockFile; never emitted
 * out of line, so it has no MAIN.MAP symbol and this name is ours. */
static inline char *makeLockFileName(void) {
    sprintf(D_0067BB88, D_0054EF00, D_005F5D90 + stage_no * 0x194);
    return D_0067BB88;
}

int createLockFile(void) {
    char buf[0x100];
    char *name = makeLockFileName();
    int fd = debugSceOpen(name, 0x602);
    if (fd < 0) {
        debug_StdPrintfDummy(D_0054EF40);
        return 0;
    }
    sprintf(buf, D_0063A038, D_0063A000);
    sceWrite(fd, buf, strlen(buf) + 1);
    debugSceClose(fd);
    debug_StdPrintfDummy(D_0054EF58, name, buf);
    D_00639F7C = 1;
    return 1;
}
extern char D_0054EF78[];
extern char D_0054EF90[];
extern char D_0063A040[];

int removeLockFile(void) {
    char buf[0x100];
    char *name = makeLockFileName();
    int fd = debugSceOpen(name, 0x602);
    if (fd < 0) {
        debug_StdPrintfDummy(D_0054EF78);
        return 0;
    }
    sprintf(buf, D_0063A038, D_0063A040);
    sceWrite(fd, buf, strlen(buf) + 1);
    debugSceClose(fd);
    debug_StdPrintfDummy(D_0054EF90, name, D_0063A000);
    D_00639F7C = 0;
    return 1;
}
extern void debug_PrintfDummy(int x, int y, unsigned int color, const char *fmt, ...);

typedef struct {
    int _0;
    int trg;   /* 0x4 */
    int _8;
    int rep;   /* 0xC */
} GsbPad;

typedef struct {
    char *name; /* 0x0 */
    int (*fn)(); /* 0x4 */
    int arg;    /* 0x8 */
} GsbMenuItem;

extern GsbPad D_0028F8F0[];
extern GsbMenuItem D_00290820[];
extern GsbMenuItem D_00290830[];
extern int D_0054F078[];
extern int D_0054F07C[];
extern char D_0054F080[];
extern char D_0063A050[];
extern int D_0063A048;
extern int D_0063A04C;

int gsb_StageSetting(void) {
    int i;
    D_00639F7C = 1;
    if (D_0063A04C >= 0) {
        if (D_00290830[D_0063A04C].fn != 0) {
            int r = D_00290830[D_0063A04C].fn(D_00290830[D_0063A04C].arg);
            if (r == -1) {
                D_0063A04C = r;
            }
            return 0;
        }
    }
    if (D_00639F7C) {
        for (i = 0; i < 11; i++) {
            debug_PrintfDummy(0x12, (i + 1) * 8 + 0x1E, D_0054F078[(D_0063A048 == i) ? 1 : 0], D_0063A050, D_00290830[i].name);
        }
        if (D_0028F8F0[0].rep & 0x4000) {
            D_0063A048++; if (D_0063A048 >= 11) D_0063A048 = 0;
        }
        if (D_0028F8F0[0].rep & 0x1000) {
            D_0063A048--; if (D_0063A048 < 0) D_0063A048 = 10;
        }
        if (D_0028F8F0[0].trg & 0x20) {
            D_0063A04C = D_0063A048;
        }
    } else {
        debug_PrintfDummy(0x1A, 0x16, 0xFFFFFFFF, D_0054F080);
        debug_PrintfDummy(0x12, 0x26, D_0054F07C[0], D_0063A050, D_00290820[0].name);
        if (D_0028F8F0[0].trg & 0x20) {
            D_00290820[0].fn(1);
        }
    }
    return (D_0028F8F0[0].trg & 0x40) ? -1 : 0;
}
extern unsigned char D_0067BCD0[];

inline void gsb_SetBGColor(void *a0, int r, int g, int b) {
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
inline void gsb_GetBGColor(unsigned char *a0)
{
    a0[0] = D_0067BCD0[0];
    a0[1] = D_0067BCD0[4];
    a0[2] = D_0067BCD0[8];
    a0[3] = D_0067BCD0[0xC];
}
extern void stage_SetLoopFlag(int key, int a1);
extern int CurrentTargetGObjSub;
extern int D_0054E3C0[];
extern char D_0054E3D8[];
extern char D_0054E3F0[];

inline void gsb_ResetFilmNoise(void) {
    int i;
    for (i = 0; i < 5; i++) {
        if (D_0054E3C0[i] != -1) {
            if (i == CurrentTargetGObjSub) {
                stage_SetLoopFlag(D_0054E3C0[i], 1);
                debug_StdPrintfDummy(D_0054E3D8, CurrentTargetGObjSub);
            } else {
                stage_SetLoopFlag(D_0054E3C0[i], 0);
                debug_StdPrintfDummy(D_0054E3F0, CurrentTargetGObjSub);
            }
        }
    }
}
extern float D_00639F88;
extern float D_00639F90;

inline void gsb_SetZoom(float a, float b) {
    D_00639F88 = a;
    D_00639F90 = b;
}
extern int sceGsSyncPath(int mode, int timeout);
extern void gsb_ResetGSSystem(void);
extern void gsb_PostEffect(void);
extern char D_0054E468[];
extern int D_00639FF8;

inline int gsb_SyncGSSystem(void) {
    if (sceGsSyncPath(1, 0)) {
        D_00639FF8++;
        if (D_00639FF8 >= 11) {
            debug_StdPrintfDummy(D_0054E468);
            gsb_ResetGSSystem();
            D_00639FF8 = 0;
        }
        return 1;
    }
    D_00639FF8 = 0;
    gsb_PostEffect();
    return 0;
}
extern int stage_no;
extern char D_005F5D90[];
extern char D_0054E488[];
extern char D_0054E4A8[];
extern char D_0054E4D8[];
extern char D_0028F720[];
inline int gsb_LoadStageSettings(void) {
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
extern int D_00639F78;
extern char D_0054E568[];
extern char D_0054E598[];
extern void appendLogFile(void);

inline int gsb_SaveStageSettings(void) {
    char buf[0x100];
    int fd;
    if (D_00639F78 == 0) {
        sprintf(buf, D_0054E488, D_005F5D90 + stage_no * 0x194);
        fd = debugSceOpen(buf, 0x602);
        if (fd < 0) {
            debug_StdPrintfDummy(D_0054E568);
            return -1;
        }
        sceWrite(fd, D_0028F720, 0x1D0);
        debug_StdPrintfDummy(D_0054E598, buf);
        debugSceClose(fd);
        appendLogFile();
    }
    return -1;
}
inline void gsb_ClearFrameBuffer(void) {
    volatile int local[96];
}
inline void gsb_ResetSnap(void) {
}
inline void gsb_TakeSnap(void) {
}
extern void updateOtherEditingLockFlag(void);

inline int lockOtherEditing(void) {
    updateOtherEditingLockFlag();
    if (D_00639F78 != 0) {
        return -1;
    }
    createLockFile();
    gsb_LoadStageSettings();
    return -1;
}

inline int unlockOtherEditing(void) {
    updateOtherEditingLockFlag();
    if (D_00639F78 != 0) {
        return -1;
    }
    gsb_LoadStageSettings();
    removeLockFile();
    return -1;
}
