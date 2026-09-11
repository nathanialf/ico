#include "common.h"

/* header prototypes (order fixes the inline tail) */
/* prototypes: their order is the inline tail's emission order */
void ExitIcoMisc(void);
void ExitIcoMisc(void);
extern char D_0061D3E0[];
extern char D_0061D418[];
extern void *D_0063A428;
extern char D_0071CA90[];
extern void debug_PrintfDummy(int a0, int a1, unsigned int a2, void *a3);
extern void iosMallocCheckLeak(void *a0);
extern void sprintf();

inline void ExitIcoMisc(void) {}

INCLUDE_ASM("asm/nonmatchings/src/icoMisc", disp_memory_partition_bar);

void disp_memory_partition(void)
{
    char *p;
    int y = 0x70;
    debug_PrintfDummy(0x18, 0x64, 0xFFFFFF00, D_0061D3E0);
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
            sprintf(D_0071CA90, D_0061D418, p + 0x10, p, sum, diff, max);
            debug_PrintfDummy(0x64, y, 0xFFFFFF00, D_0071CA90);
            y += 8;
            p = *(char **)(p + 0x24);
        } while (p != 0);
    }
}

INCLUDE_ASM("asm/nonmatchings/src/icoMisc", ExecIcoMisc);
INCLUDE_ASM("asm/nonmatchings/src/icoMisc", InitIcoMisc);

extern int D_0063B138;
extern int D_0063B148;
extern int D_0063B150;
extern int D_0063B164;
extern char D_004E3B20[];
extern void stage_DispAnimation(void);
extern void DispStageMultiBgaManager(void);
extern void DispParticleEffects(void);
extern void DispGameOverEffect(void);
extern void SetSkeltonDispSwitch(int a0);
extern void SetHitCollisionDisplay(int a0, int a1);
extern void DrawCollision(int a0);
extern void DispAllSpiderGroups(void);
extern void MatrixDrive_PushMatrix(void);
extern void MatrixDrive_PopMatrix(void);
extern void *MatrixDrive_GetMatrix(void);
extern void _UnitMatrix(void *m);
extern void gif_StartPacketPri(int pri);
extern void gif_SetAlpha(int a0, int a1, int a2);
extern void gif_EndPacket(void);
extern void *GetWindVector(int a0, void *pos);
extern void _ScaleVectorXYZ(void *dst, void *src, float k);
extern void _AddVectorXYZ(void *dst, void *a, void *b);
extern void DrawLineG(void *a, void *ca, void *b, void *cb, int z);
extern void light_DispVolume(void);

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
