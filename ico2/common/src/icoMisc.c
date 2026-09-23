#include "common.h"
#include "debug.h"
#include "memory.h"
#include "fieldCollision.h"
#include "Light.h"
#include "StageAnimation.h"
#include "darkVolume.h"
#include "lineManager.h"
#include "matrixDrive.h"
#include "motionManager.h"
#include "motionManager2.h"
#include "particleEffect.h"
#include "spiderGroupManager.h"
#include "stageMultiBgaManager.h"
#include "icoMisc.h"
#include <stdio.h>

extern char D_0061D3E0[];
extern char D_0061D418[];
extern void *D_0063A428;
extern int D_0063A054;
extern int D_0063A064;
extern int D_0063A068;
extern int D_0063B130;
extern void *D_0063A430;
extern void *D_0063A43C;
extern void *D_0063A444;
extern void *D_0063A448;
extern unsigned int D_0063B428;
extern char D_0061D340[];
extern char D_0061D3B8[];
extern char D_0063B430[];
extern char D_0063B438[];
extern int D_004E3B00[];
extern int D_004E3B10[];
/* kept local: this TU's use of gif_MakeSpriteNoTexture does not fit the
   prototype in GifPacket.h (the colour word arrives as a 32-bit unsigned,
   which the ROM materialises with lui + ori). */
extern void gif_MakeSpriteNoTexture(int x, int y, int w, int h, unsigned int col,
                                    unsigned int *tint, int mode);

/* .bss, owned by icoMisc.o (MAIN.MAP sizes the run 0x80 and names no
   symbol in it): the line buffer the memory report is printed through. */
/* */
static char printBuf[128];

inline void ExitIcoMisc(void) {}

/* kept local: this TU's uses of gif_StartPacketPri do not fit the prototype in GifPacket.h */
extern void gif_StartPacketPri(int pri);
/* kept local: this TU's uses of gif_SetAlpha do not fit the prototype in GifPacket.h */
extern void gif_SetAlpha(int a0, int a1, int a2);
/* kept local: this TU's uses of gif_EndPacket do not fit the prototype in GifPacket.h */
extern void gif_EndPacket(void);

/* two-dimensional screen position handed to Draw2DLine */
typedef struct {
    int x;
    int y;
    int z;
    int w;
} D2Pos;

/* Compiled-out debug hook, the same construct clothAnimation.c carries: the
   Jan-2002 listing emits nothing for icoMisc.c:636-647, twelve source lines
   between the last gif_SetAlpha (line 635) and gif_EndPacket (line 648), and
   the ROM's schedule for that basic block needs exactly the one zero-byte
   insn an inlined empty body leaves behind.  ee-gcc emits `(use (const_int
   0))` for an inlined call; with two issue slots per clock it takes the free
   second slot at clock 2, which pushes the third loop's `i = 0` out to clock
   3, so `addiu $a2,$0,0x80` stays adjacent to the first call and reorg fills
   gif_SetAlpha's delay slot with it and gif_EndPacket's with `daddu
   $s5,$0,$0`.  Without the hook the init takes that free slot and the two
   delay slots come out swapped, with a nop in the second.  The name is ours:
   the listing records no symbol for an inlined empty body.  Evidence rung:
   ROM bytes (0x1B7AF0..0x1B7B1C) plus the listing's line map. */
static __inline__ void partitionBarDebugDisp(void) {}

void disp_memory_partition_bar(void)
{
    char *parts[5] = {D_0063A430, D_0063A448, D_0063A444, D_0063A43C, 0};
    D2Pos st;
    D2Pos ed;
    char buf[1024];
    char *p;
    char *e;
    int i = 0;
    int j;
    int k;
    int size;
    int total;
    int used;
    int max;
    int x;

    if (D_0063A054 != 0) {
        return;
    }
    max = 0;
    gif_StartPacketPri(12);
    for (; parts[i] != 0; i++) {
        p = parts[i];
        size = *(int *)(p + 0x3C) - *(int *)(p + 0x38) + 0x10;
        if (max < size) {
            max = size;
        }
    }
    st.z = ed.z = 0;
    st.w = ed.w = 0;
    st.y = (D_0063A068 / 2 + 1898) << 4;
    ed.y = st.y + 1280;
    if (D_0063B130 == 2) {
        gif_SetAlpha(1, 2, 32);
        gif_MakeSpriteNoTexture((-(D_0063A064 >> 1) + 2178) << 4, (D_0063A068 / 2 + 1898) << 4,
                                (D_0063A064 - 200) << 4, 768, 0xFFFFFFFF, &D_0063B428, 1);
    }
    gif_SetAlpha(1, 2, 112);
    for (j = 0, k = 0; j < max; j += 0x100000) {
        st.x = ed.x = (int)(((float)(-(D_0063A064 >> 1) + 130) + 2048.0f) * 16.0f +
                            (float)j * (float)(D_0063A064 - 200) / (float)max * 16.0f);
        if (k % 10) {
            Draw2DLine((int *)&st, (int *)&ed, D_004E3B10, -1);
        } else {
            Draw2DLine((int *)&st, (int *)&ed, D_004E3B00, -1);
        }
        k++;
    }
    for (i = 0; parts[i] != 0; i++) {
        used = 0;
        p = parts[i];
        e = *(char **)(p + 0x44);
        total = *(int *)(p + 0x3C) - *(int *)(p + 0x38) + 0x10;
        if (e != 0) {
            do {
                used += *(int *)(e + 0x34) << 4;
                e = *(char **)(e + 0x2C);
                if ((unsigned int)e > 0x1FEFFF0) {
                    sprintf(buf, D_0061D340, p + 0x10, e);
                    debug_assertMessage(D_0061D3B8, 609, buf);
                    __assert(D_0061D3B8, 609, D_0063B430);
                }
            } while (e != 0);
        }
        gif_SetAlpha(0, 2, 112);
        gif_SetAlpha(1, 2, 112);
        st.y = ed.y = (D_0063A068 / 2 + i * 18 + 1907) << 4;
        st.x = (int)(((float)(-(D_0063A064 >> 1) + 130) + 2048.0f) * 16.0f);
        ed.x = (int)((float)st.x +
                     (float)(total - used) * (float)(D_0063A064 - 200) / (float)max * 16.0f);
        Draw2DLine((int *)&st, (int *)&ed, D_004E3B00, -1);
        x = (int)(((float)(-(D_0063A064 >> 1) + 130) + 2048.0f) * 16.0f);
        st.x = (int)((float)x + (float)total * (float)(D_0063A064 - 200) / (float)max * 16.0f);
        ed.x = (int)((float)x +
                     (float)(total - used) * (float)(D_0063A064 - 200) / (float)max * 16.0f);
        Draw2DLine((int *)&st, (int *)&ed, D_004E3B10, -1);
    }
    gif_SetAlpha(1, 4, 128);
    partitionBarDebugDisp();
    gif_EndPacket();
    for (i = 0; parts[i] != 0; i++) {
        p = parts[i];
        debug_PrintfDummy(D_0063A064 / 2 - (D_0063A064 >> 1) + 30,
                          (D_0063A068 / 2 - 150 + D_0063A068 / 2 + i * 18) / 2, 0xFFFFFF80,
                          D_0063B438, p + 0x10);
    }
}

void disp_memory_partition(void)
{
    char *p;
    int y = 0x70;
    debug_PrintfDummy(24, 100, 0xFFFFFF00, D_0061D3E0);
    iosMallocCheckLeak(D_0063A428);
    p = *(char **)((char *)D_0063A428 + 0x28);
    if (p != 0) {
        do {
            unsigned int sum = 0;
            unsigned int max = 0;
            char *e;
            int diff;
            iosMallocCheckLeak(p);
            e = *(char **)(p + 0x44);
            if (e != 0) {
                do {
                    unsigned int v = *(int *)(e + 0x34) << 4;
                    if (max < v) {
                        max = v;
                    }
                    sum += v;
                    e = *(char **)(e + 0x2C);
                } while (e != 0);
            }
            diff = *(int *)(p + 0x3C) - *(int *)(p + 0x38) + 0x10;
            sprintf(printBuf, D_0061D418, p + 0x10, p, sum, diff, max);
            debug_PrintfDummy(100, y, 0xFFFFFF00, printBuf);
            y += 8;
            p = *(char **)(p + 0x24);
        } while (p != 0);
    }
}

extern int D_0063B174;
extern int D_0063B14C;
extern int D_0063B448;
extern int D_0063A3E0;
extern int D_0063B140;
extern int D_0063B13C;
extern int D_0063B1A4;
extern int D_0063B60C;
extern int D_0063B444;
extern int D_0063B440;
extern int D_0063B150;
extern int graphics_ready;
extern int kanbanCommonRead;
extern int stage_no;
extern int title_fading_out;
extern float D_0063A64C;
extern float D_0063AA0C;
extern char *D_00639EA4;
extern char *D_00639EA8;
extern char D_0061D430[];
extern char D_0061D440[];
extern char D_0061D458[];
extern int D_0028F4C0[];
extern char jimaku_msg[];
extern void disp_memory_partition(void);
extern void disp_memory_partition_bar(void);
extern void debug_SESlotDisp(void);
extern int iosCdvdDiskStatusGet(void);
/* debug_Printf comes from debug.h */
extern void iosOmGetGObjStatus(int *a0, int *a1);
extern void exec_layout_texture(void);
extern void kanbanBootMain(void);
extern void kanbanExec(void);
extern void ExecParticleEffects(void);
extern void ExecStreamMotionManager(void);
extern void ExecWindManager(void);
extern void ExecSpiderGroupManager(void);
extern void ExecGameOverEffect(void);
extern void gamesysBackStageProcess(void);
extern void warpGirlOutStage(int stage, int flag);
extern int GetCameraPos(void);
extern void soundSeEnvPlay(void);
extern void soundReqTickProc(void);
extern void scpGirlHintVoiceTickProc(int cam);
extern void fightSoundProcess(void);
extern void eBrainProcess(void);
extern void lt_switch_layout(int id);
extern void jimakuDisp(char *self);

void ExecIcoMisc(void)
{
    int total;
    int used;
    int cam;

    if (D_0063B174 == 1) {
        disp_memory_partition();
    }
    if (D_0063B14C == 1) {
        debug_SESlotDisp();
    }
    if (iosCdvdDiskStatusGet() != 0) {
        if (D_0063B448++ < 15) {
            debug_PrintfDummy(250, 100, 0xFF000000, (int)D_0061D430);
        } else if (D_0063B448 >= 31) {
            D_0063B448 = 0;
        }
    }
    if (D_0063A3E0 != 0) {
        debug_PrintfDummy(250, 100, 0xFF000000, (int)D_0061D440, D_0063A3E0);
    }
    iosOmGetGObjStatus(&total, &used);
    if (D_0063B140 != 0 || (D_0063B13C & 1) != 0) {
        debug_Printf(470, 10, (used * 100 / total > 90) ? 0xFF300080 : 0xC0FF80, (int)D_0061D458,
                     used, total);
    }
    if (D_0063B1A4 != 0) {
        disp_memory_partition_bar();
    }
    if (graphics_ready == 0) {
        if (iosCdvdDiskStatusGet() == 0) {
            exec_layout_texture();
        }
    }
    if (kanbanCommonRead != 0) {
        if (stage_no == 1) {
            kanbanBootMain();
        }
    }
    kanbanExec();
    if (graphics_ready != 0) {
        return;
    }
    if (D_0028F4C0[5] == 0) {
        ExecParticleEffects();
        ExecStreamMotionManager();
        ExecWindManager();
        D_0063A64C = D_0063AA0C;
        ExecSpiderGroupManager();
        ExecGameOverEffect();
        D_0063B444 = 0;
    } else {
        if (D_0063B60C == 28) {
            D_0063B444 = 1;
        }
        if (D_0063B444 != 0) {
            D_0063A64C = 0.0f;
        } else if (D_0063AA0C > 0.5f) {
            D_0063A64C = 0.5f;
        }
    }
    if (D_0028F4C0[6] == 0) {
        gamesysBackStageProcess();
        if (D_0063B150 == 1) {
            warpGirlOutStage(stage_no, 1);
        }
        cam = GetCameraPos();
        if (D_0063B440 == 0) {
            if (cam != 0) {
                soundSeEnvPlay();
            }
        }
        D_0063B440 = cam;
        if (cam != 0) {
            soundReqTickProc();
            scpGirlHintVoiceTickProc(cam);
        }
        fightSoundProcess();
    }
    eBrainProcess();
    if (title_fading_out != 0) {
        if (D_00639EA4 != 0) {
            if (*(float *)(*(char **)(D_00639EA4 + 0x15C) + 0x55C) > 1000.0f) {
                lt_switch_layout(62);
            }
        }
        if (D_00639EA8 != 0) {
            if (*(float *)(*(char **)(D_00639EA8 + 0x15C) + 0x55C) > 1000.0f) {
                lt_switch_layout(62);
            }
        }
    }
    jimakuDisp(jimaku_msg);
}

/* per-scene preset: twelve (time, effect id) pairs then the scene label at 0xC0 */
typedef struct {
    struct {
        float t;
        int id;
    } ent[12];

    char _60[0xC0 - 0x60];
    char name[0x194 - 0xC0];
} ScnPre;

/* particle-effect entry: package id at 0x18, attribute word at 0x20 whose
   bit 0 marks the entry as already handled */
typedef struct {
    char _0[0x18];
    int pkg; /* 0x18 */
    char _1C[0x4];
    unsigned int done : 1; /* 0x20 */
    unsigned int _21 : 31;
} EffEnt;

extern StgPre D_005F5D50[];
extern const ScnPre D_0055FE58[];
/* the effect table is read-only here; the const frees its loads and is what the
   ROM's schedule shows (RTX_UNCHANGING_P, see the printf site in the scan loop) */
extern const EffEnt D_00626278[];
extern char D_0062A278[][0x50];
extern int D_0028F4C0[];
extern int debugMoveMode;
extern int motionFrameUpdate;
extern int thisIsYourStartStage;
extern int frame_count;
extern int graphics_ready;
extern int stage_no;
extern int D_0063AA08;
extern unsigned char D_0063B44C;
extern int D_0063B450;
extern int D_0063B454;
extern int D_0063B458;
extern int D_0063B0D8;

/* .sbss, owned by icoMisc.o (MAIN.MAP does not name it: the member has no
   named sbss symbols); the frame stamp the load-time report below prints. */
static int load_time;

extern char D_004DA788[];
extern char D_004DD700[];
extern char D_0061D468[];
extern char D_0061D480[];
extern char D_0061D498[];
extern char D_0061D4B8[];
extern char D_0061D508[];
extern char D_0061D520[];
extern char D_0061D538[];
extern char D_0061D548[];
extern char D_0061D560[];
extern char D_0061D578[];
extern char D_0061D5B8[];
extern char D_0061D628[];
extern char D_0061D640[];
extern char D_0061D658[];
extern char D_0063B460[];
extern char D_0063B468[];
extern char D_0063B470[];
extern char D_0063B478[];
extern void debug_StdPrintfDummy();
extern void InitializeStaticBlur(void);
extern void InitStreamMotionManager(void);
extern void InitFlyManager(void);
extern void gamesysMemoryLoad(void *a0, void *a1, int a2);
extern void ACTGame_SetActors_Debug(int stage, int a1);
extern void light_InitLight(void);
extern void InitStageLight(int stage);
extern void enemy_Initialize(void);
extern void InitCharFileManager(void);
extern void ResetCharFileManager(void);
extern void debugCdvdLoadInfoSegInit(int a0);
extern char *GetDataFileName();
extern char *GetDataFileName2();
extern void iosCdvdLoadPackFile(int a0, char *name, int a2);
extern void kanbanInit(int a0);
extern void kanbanBootInit(void);
extern void kanbanBootStart(void);
extern void ResetStatic2MotionManager(int a0);
extern void InitWayPointSystem(void);
extern void fog_MakeFogClut(void);
extern void InitParticleEffects(void);
extern void InitializeWaterDot(void);
extern void InitSceneObjects(int stage);
extern void InitWindManager(int stage);
extern void init_layout_texture(int stage);
extern int *GetParticleEffectPackage(int id);
extern void gsb_ResetFilmNoise(void);
extern void stage_Init(void);
extern void ObjAction_Init(void);
extern void InitStageChange(void);
extern void sndInit(int stage);
extern void iosPadActInit(void);
extern void MakeCollisionDependGObjList(void);
extern void gamesysObjInfoStageInitPosSaveUnlock(void);
extern void iosThreadDestroy(int a0);

void InitIcoMisc(int *arg)
{
    int stage = *arg;
    int i;
    int j;
    int id;
    int found;
    int pack;
    char *fname;

    debugMoveMode = 0;
    motionFrameUpdate = 1;

    InitializeStaticBlur();
    InitStreamMotionManager();
    InitSpiderGroupManager();
    InitFlyManager();

    if (D_0028F4C0[3] != 0 && D_0028F4C0[4] != 0) {
        gamesysMemoryLoad(D_004DA788, D_004DD700, 0);
        D_0063AA08 = 0;
        D_0028F4C0[4] = 0;
    }
    if (thisIsYourStartStage != 1 && D_0063B44C != 0) {
        ACTGame_SetActors_Debug(stage, 0);
        D_0063B44C = 0;
    }
    debug_StdPrintfDummy(D_0061D468);
    light_InitLight();
    InitStageLight(stage);
    enemy_Initialize();
    debug_StdPrintfDummy(D_0061D480);
    load_time = frame_count;
    if (D_0063B450 == 0) {
        InitCharFileManager();
    } else {
        ResetCharFileManager();
    }
    D_0063B450 = 1;
    debug_StdPrintfDummy(D_0061D498);
    pack = D_0063B0D8;
    if (D_0063B454 == 0) {
        debugCdvdLoadInfoSegInit(0);
        iosCdvdLoadPackFile(pack, GetDataFileName(-1, pack), 0);
        kanbanInit(0);
        kanbanBootInit();
        D_0063B454 = 1;
    }
    if (stage_no == 1) {
        kanbanBootStart();
    }
    if (D_0063B458 != D_005F5D50[stage].mot) {
        /* the listing's dispatch tests ==2, <3, ==3 in that order: case 1 shares
           the default arm, which is what puts a low-bound test in the tree */
        switch (D_005F5D50[stage].mot) {
        case 1:
        default:
            fname = GetDataFileName2(D_0063B460, pack);
            break;
        case 2:
            fname = GetDataFileName2(D_0063B468, pack);
            break;
        case 3:
            fname = GetDataFileName2(D_0063B470, pack);
            break;
        }
        if (D_0063B458 != -1) {
            debug_StdPrintfDummy(D_0061D4B8);
            ResetStatic2MotionManager(D_0063B458);
        }
        iosMallocResetPartition(D_0063A448);
        iosCdvdLoadPackFile(pack, fname, 0);
        D_0063B458 = D_005F5D50[stage].mot;
    }
    debug_StdPrintfDummy(D_0061D508);
    debugCdvdLoadInfoSegInit(1);
    iosCdvdLoadPackFile(pack, GetDataFileName(stage, pack), 1);
    load_time = frame_count - load_time;
    debug_StdPrintfDummy(D_0061D520);
    InitWayPointSystem();
    debug_StdPrintfDummy(D_0061D538);
    fog_MakeFogClut();
    debug_StdPrintfDummy(D_0061D548);
    InitParticleEffects();
    InitStageMultiBgaManager();
    InitializeWaterDot();
    debug_StdPrintfDummy(D_0061D560, stage);
    InitSceneObjects(stage);
    InitWindManager(stage);
    debug_StdPrintfDummy(D_0063B478, D_005F5D50[stage_no].name);
    init_layout_texture(stage);

    found = 0;
    for (i = 0; i < 1145; i++) {
        for (j = 0; j < 12; j++) {
            id = D_0055FE58[i].ent[j].id;
            if (id > 0xFFFF) {
                continue;
            }
            if (D_00626278[id].done) {
                continue;
            }
            if (id == 24) {
                continue;
            }
            if (GetParticleEffectPackage(D_00626278[id].pkg)[1] != 1) {
                continue;
            }
            debug_StdPrintfDummy(D_0061D578, D_0055FE58[i].name, D_0062A278[D_00626278[id].pkg]);
            found = 1;
        }
    }
    if (found != 0) {
        debug_StdPrintfDummy(D_0061D5B8);
    }
    debug_StdPrintfDummy(D_0061D628);
    gsb_ResetFilmNoise();
    stage_Init();
    debug_StdPrintfDummy(D_0061D640);
    ObjAction_Init();
    InitStageChange();
    graphics_ready = 0;
    debug_StdPrintfDummy(D_0061D658, load_time / 60.0f);
    sndInit(stage);
    iosPadActInit();
    if (D_005F5D50[stage_no].initproc != 0) {
        D_005F5D50[stage_no].initproc();
    }
    MakeCollisionDependGObjList();
    gamesysObjInfoStageInitPosSaveUnlock();
    D_0028F4C0[5] = 0;
    D_0028F4C0[6] = 0;
    iosThreadDestroy(0);
}

extern int D_0063B138;
extern int D_0063B148;
extern int D_0063B150;
extern int D_0063B164;
extern char D_004E3B20[];
/* kept local: this TU's uses of _UnitMatrix do not fit the prototype in Matrix.h */
extern void _UnitMatrix(void *m);
/* kept local: this TU's uses of gif_StartPacketPri do not fit the prototype in GifPacket.h */
extern void gif_StartPacketPri(int pri);
/* kept local: this TU's uses of gif_SetAlpha do not fit the prototype in GifPacket.h */
extern void gif_SetAlpha(int a0, int a1, int a2);
/* kept local: this TU's uses of gif_EndPacket do not fit the prototype in GifPacket.h */
extern void gif_EndPacket(void);
/* kept local: this TU's uses of GetWindVector do not fit the prototype in windField.h */
extern void *GetWindVector(int a0, void *pos);
/* kept local: this TU's uses of _ScaleVectorXYZ do not fit the prototype in Matrix.h */
extern void _ScaleVectorXYZ(void *dst, void *src, float k);
/* kept local: this TU's uses of _AddVectorXYZ do not fit the prototype in Matrix.h */
extern void _AddVectorXYZ(void *dst, void *a, void *b);

void DispIcoMisc(void)
{
    int i = 0;
    int j;

    stage_DispAnimation();
    DispStageMultiBgaManager();
    DispParticleEffects();
    DispGameOverEffect();
    SetSkeltonDispSwitch(D_0063B148);
    SetHitCollisionDisplay(D_0063B150, D_0063B150);
    if (D_0063B164 > 0) {
        DrawCollision(D_0063B164 == 1 ? 0 : -10);
    }
    if (D_0063B138 != 0) {
        DispAllSpiderGroups();
    }
    if (D_0063B148 != 0) {
        MatrixDrive_PushMatrix();
        _UnitMatrix(MatrixDrive_GetMatrix());
        gif_StartPacketPri(0xB);
        gif_SetAlpha(1, 5, 0x80);
        for (j = -10; j < 20; j++) {
            for (i = -10; i < 10; i++) {
                float pos[4] = {j * 100.0f, -10.0f, i * 100.0f, 1.0f};
                float tip[4];

                _ScaleVectorXYZ(tip, GetWindVector(0, pos), 10.0f);
                _AddVectorXYZ(tip, pos, tip);
                DrawLineG(tip, D_004E3B20, pos, D_004E3B20, 0);
            }
        }
        gif_EndPacket();
        MatrixDrive_PopMatrix();
    }
    light_DispVolume();
}
