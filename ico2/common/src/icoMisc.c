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
#include "gamesys.h"
#include "s_init.h"
#include "script.h"
#include <stdio.h>
#include "GsBase.h"
#include "ios.h"
#include "layout_texture.h"
#include "kanban.h"
#include "kanbanBoot.h"
#include "Matrix.h"
#include "cdvd.h"
#include "sceneManager.h"
#include "charFileManager.h"
#include "access.h"
#include "warpGirl.h"
#include "jimaku.h"
#include "streamMotionManager.h"
#include "motionFileManager.h"
#include "way_llf.h"
#include "waterDot.h"
#include "windManager.h"
#include "objact.h"
#include "soundManager.h"
#include "pad.h"
#include "thread.h"
#include "obj_manager.h"
#include "camera-root.h"
#include "act-game.h"
#include "main.h"
#include "windField.h"
#include "debug_exception.h"
#include "fightSound.h"
#include "ebrain.h"
#include "EnemyInit.h"
#include "ZFog.h"
#include "flyManager.h"
#include "staticBlur.h"
#include <assert.h>
#include "include_asm.h"

static void disp_memory_partition_bar(void);
/* debug.h leaves it out (see there) */
extern int debug_bar_flag;

/* .sdata: the partition bar's backdrop tint; ExecIcoMisc's three state
   words; InitIcoMisc's four; the six debug words dbgC0..dbgC5 (declared in
   icoMisc.h). */
typedef struct { /* field names derived */
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} MiscColor; /* derived name */

static MiscColor partitionBarTint = {255, 255, 255, 128}; /* derived name */

/* .data: the partition bar's two line colours and the wind-field line colour,
   RGBA as Draw2DLine and DrawLineG take them. */
static int partitionFreeColor[4] = {255, 128, 64, 128}; /* derived name */

static int partitionUsedColor[4] = {64, 128, 255, 128}; /* derived name */

/* GifPacket.h's entry points, which this TU does not include: its call
   passes gif_MakeSpriteNoTexture's z as a 32-bit unsigned int, where the
   header takes a long long */
extern void gif_StartPacketPri(int pri);
extern void gif_SetAlpha(long long alpha, long long mode, long long fix);
extern void gif_EndPacket(void);
extern void gif_MakeSpriteNoTexture(int x, int y, int w, int h, unsigned int z, MiscColor *col,
                                    int prim);

/* .bss: the line buffer the memory report is printed through */
static char printBuf[128]; /* derived name */

/* two-dimensional screen position handed to Draw2DLine */
typedef struct { /* field names derived */
    int x;
    int y;
    int z;
    int w;
} D2Pos; /* derived name */

/* The partition bar's TTY trace, built only when DEBUG is defined; the
   retail build does not define it, so the helper has no body there (the
   trace text derived). */
static __inline__ void partitionBarDebugDisp(void) /* derived name */
{
#ifdef DEBUG
    scePrintf("disp_memory_partition_bar\n");
#endif
}

static void disp_memory_partition_bar(void)
{
    IosMemPart *parts[5] = {ios_partition_isys, ios_partition_s2motion, ios_partition_smotion,
                            ios_partition_common, 0};
    D2Pos st;
    D2Pos ed;
    char buf[1024];
    IosMemPart *p;
    IosMemNode *e;
    int i = 0;
    int j;
    int k;
    int size;
    int total;
    int used;
    int max;
    int x;

    if (fbKeep != 0) {
        return;
    }
    max = 0;
    gif_StartPacketPri(12);
    for (; parts[i] != 0; i++) {
        p = parts[i];
        size = p->end - p->start + 0x10;
        if (max < size) {
            max = size;
        }
    }
    st.z = ed.z = 0;
    st.w = ed.w = 0;
    st.y = (ScreenHeight / 2 + 1898) << 4;
    ed.y = st.y + 1280;
    if (debug_bar_flag == 2) {
        gif_SetAlpha(1, 2, 32);
        gif_MakeSpriteNoTexture((-(ScreenWidth >> 1) + 2178) << 4, (ScreenHeight / 2 + 1898) << 4,
                                (ScreenWidth - 200) << 4, 768, 0xFFFFFFFF, &partitionBarTint, 1);
    }
    gif_SetAlpha(1, 2, 112);
    for (j = 0, k = 0; j < max; j += 0x100000) {
        st.x = ed.x = (int)(((float)(-(ScreenWidth >> 1) + 130) + 2048.0f) * 16.0f +
                            (float)j * (float)(ScreenWidth - 200) / (float)max * 16.0f);
        if (k % 10) {
            Draw2DLine((int *)&st, (int *)&ed, partitionUsedColor, -1);
        } else {
            Draw2DLine((int *)&st, (int *)&ed, partitionFreeColor, -1);
        }
        k++;
    }
    for (i = 0; parts[i] != 0; i++) {
        used = 0;
        p = parts[i];
        e = p->head;
        total = p->end - p->start + 0x10;
        if (e != 0) {
            do {
                used += e->size << 4;
                e = e->free_next;
                if ((unsigned int)e > 0x1FEFFF0) {
                    sprintf(
                        buf,
                        "DISP_MEMORY_PARTITION_BAR():\n\tINVALID MEMORY FREE AREA INDICATED IN PARTITION \"%s\"\n\tMALLOCED MEMORY'S NEXT_FREE: %p\n",
                        p->name, e);
                    debug_assertMessage(__FILE__, 609, buf);
                    __assert(__FILE__, 609, "e");
                }
            } while (e != 0);
        }
        gif_SetAlpha(0, 2, 112);
        gif_SetAlpha(1, 2, 112);
        st.y = ed.y = (ScreenHeight / 2 + i * 18 + 1907) << 4;
        st.x = (int)(((float)(-(ScreenWidth >> 1) + 130) + 2048.0f) * 16.0f);
        ed.x = (int)((float)st.x +
                     (float)(total - used) * (float)(ScreenWidth - 200) / (float)max * 16.0f);
        Draw2DLine((int *)&st, (int *)&ed, partitionFreeColor, -1);
        x = (int)(((float)(-(ScreenWidth >> 1) + 130) + 2048.0f) * 16.0f);
        st.x = (int)((float)x + (float)total * (float)(ScreenWidth - 200) / (float)max * 16.0f);
        ed.x = (int)((float)x +
                     (float)(total - used) * (float)(ScreenWidth - 200) / (float)max * 16.0f);
        Draw2DLine((int *)&st, (int *)&ed, partitionUsedColor, -1);
    }
    gif_SetAlpha(1, 4, 128);
    partitionBarDebugDisp();
    /* a draw in white, compiled out of the retail build (the call derived) */
    if (0) {
        Draw2DLine((int *)&st, (int *)&ed, (sceVu0IVECTOR){255, 255, 255, 128}, -1);
    }
    gif_EndPacket();
    for (i = 0; parts[i] != 0; i++) {
        p = parts[i];
        debug_PrintfDummy(ScreenWidth / 2 - (ScreenWidth >> 1) + 30,
                          (ScreenHeight / 2 - 150 + ScreenHeight / 2 + i * 18) / 2, 0xFFFFFF80,
                          "%10s", p->name);
    }
}

static void disp_memory_partition(void)
{
    IosMemPart *p;
    int y = 0x70;
    debug_PrintfDummy(24, 100, 0xFFFFFF00, "partition             total free/all      max free");
    iosMallocCheckLeak(ios_partition_root);
    p = ios_partition_root->child;
    if (p != 0) {
        do {
            unsigned int sum = 0;
            unsigned int max = 0;
            IosMemNode *e;
            int diff;
            iosMallocCheckLeak(p);
            e = p->head;
            if (e != 0) {
                do {
                    unsigned int v = e->size << 4;
                    if (max < v) {
                        max = v;
                    }
                    sum += v;
                    e = e->free_next;
                } while (e != 0);
            }
            diff = p->end - p->start + 0x10;
            sprintf(printBuf, "%8s%8x: %8x/%8x %x", p->name, p, sum, diff, max);
            debug_PrintfDummy(100, y, 0xFFFFFF00, printBuf);
            y += 8;
            p = p->next;
        } while (p != 0);
    }
}

static void *prevCameraPos = 0; /* derived name */

static int seEnvMute = 0; /* derived name */

static int diskErrorBlink = 0; /* derived name */

INCLUDE_ASM(ExecIcoMisc);

/* per-scene preset: twelve (time, effect id) pairs then the scene label at 0xC0 */
typedef struct { /* field names derived */

    struct {
        float t;
        int id;
    } ent[12];

    char pad60[0xC0 - 0x60];
    char name[0x194 - 0xC0];
} ScnPre; /* derived name */

/* particle-effect entry: package id at 0x18, attribute word at 0x20 whose
   bit 0 marks the entry as already handled */
typedef struct { /* field names derived */
    char pad0[24];
    int pkg; /* 0x18 */
    char pad1C[4];
    unsigned int done : 1; /* 0x20 */
    unsigned int pad21 : 31;
} EffEnt; /* derived name */

/* motionOrientManager.h carries MotionDef and declares no motionKind */
extern const ScnPre motionKind[];
/* the effect table, read-only here and read as EffEnt;
   frameDependSequence.h declares EffEntry */
extern const EffEnt motionEffKind[];

static unsigned char setActorsDebugPending = 1; /* derived name */

static int charFileManagerReady = 0; /* derived name */

static int commonPackLoaded = 0; /* derived name */

static int loadedMotionSeg = -1; /* derived name */

/* .sbss: the frame stamp the load-time report below prints */
static int load_time; /* derived name */

INCLUDE_ASM(InitIcoMisc);

int dbgC0 = 0;

int dbgC1 = 0;

int dbgC2 = 0;

int dbgC3 = 0;

int dbgC4 = 0;

int dbgC5 = 0;

static int windLineColor[4] = {0, 128, 255, 128}; /* derived name */

void DispIcoMisc(void)
{
    int i = 0;
    int j;

    stage_DispAnimation();
    DispStageMultiBgaManager();
    DispParticleEffects();
    DispGameOverEffect();
    SetSkeltonDispSwitch(debug_skel_flag);
    SetHitCollisionDisplay(debug_wallcheck_flag, debug_wallcheck_flag);
    if (debug_fieldcollision_flag > 0) {
        DrawCollision(debug_fieldcollision_flag == 1 ? 0 : -10);
    }
    if (debug_brain_bar_flag != 0) {
        DispAllSpiderGroups();
    }
    if (debug_skel_flag != 0) {
        MatrixDrive_PushMatrix();
        _UnitMatrix(MatrixDrive_GetMatrix());
        gif_StartPacketPri(11);
        gif_SetAlpha(1, 5, 0x80);
        for (j = -10; j < 20; j++) {
            for (i = -10; i < 10; i++) {
                float pos[4] = {j * 100.0f, -10.0f, i * 100.0f, 1.0f};
                float tip[4];

                _ScaleVectorXYZ(tip, GetWindVector(0, pos), 10.0f);
                _AddVectorXYZ(tip, pos, tip);
                DrawLineG(tip, windLineColor, pos, windLineColor, 0);
            }
        }
        gif_EndPacket();
        MatrixDrive_PopMatrix();
    }
    light_DispVolume();
}

INCLUDE_ASM(ExitIcoMisc);

INCLUDE_ASM(func_001B8908);
