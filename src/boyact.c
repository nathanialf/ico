#include "common.h"

#include "ico/types.h"

typedef struct { int a, b, c; } S12;

typedef struct { char pad[4]; float f4; } CCPResult;

INCLUDE_ASM("asm/nonmatchings/src/boyact", findChainInJump);
INCLUDE_ASM("asm/nonmatchings/src/boyact", CorrectOrient_RopeCliff);
INCLUDE_ASM("asm/nonmatchings/src/boyact", func_001506E8);
INCLUDE_ASM("asm/nonmatchings/src/boyact", CheckCollisionAttr);
INCLUDE_ASM("asm/nonmatchings/src/boyact", UpdateGeo);
INCLUDE_ASM("asm/nonmatchings/src/boyact", BoyBgaManager);
INCLUDE_ASM("asm/nonmatchings/src/boyact", E3_StageStartBoy);
INCLUDE_ASM("asm/nonmatchings/src/boyact", GetChainSlope);
INCLUDE_ASM("asm/nonmatchings/src/boyact", func_00151908);
INCLUDE_ASM("asm/nonmatchings/src/boyact", func_00153180);
INCLUDE_ASM("asm/nonmatchings/src/boyact", PutWeapon);
INCLUDE_ASM("asm/nonmatchings/src/boyact", OtherStageGirlPinchCamera_After);
INCLUDE_ASM("asm/nonmatchings/src/boyact", ACTDispLwsBoyStonize_InQueenStage);
INCLUDE_ASM("asm/nonmatchings/src/boyact", PrivInsCamProcess);
INCLUDE_ASM("asm/nonmatchings/src/boyact", func_001537B0);
INCLUDE_ASM("asm/nonmatchings/src/boyact", func_00155770);
INCLUDE_ASM("asm/nonmatchings/src/boyact", pullup_check_heroin_position);
INCLUDE_ASM("asm/nonmatchings/src/boyact", ditch_check_heroin_position);
INCLUDE_ASM("asm/nonmatchings/src/boyact", func_00155BA8);
INCLUDE_ASM("asm/nonmatchings/src/boyact", func_00157388);
extern void ConvertStickToAbsCoord();
extern void _RotyGV();

void CorrectStickInfo(int a0)
{
    int buf[4];
    ConvertStickToAbsCoord(buf);
    _RotyGV(buf, a0);

}
INCLUDE_ASM("asm/nonmatchings/src/boyact", GetBoyWeaponGObj);
INCLUDE_ASM("asm/nonmatchings/src/boyact", func_00157828);
void func_001578C8(volatile int a0) {
    char *g = (char *)a0;
    ACTAdjustPlane(a0, *(char **)(*(char **)(g + 0x164) + 0x688) + 0x8B0);
    _ACTWait(0);
}
INCLUDE_ASM("asm/nonmatchings/src/boyact", func_00157900);
INCLUDE_ASM("asm/nonmatchings/src/boyact", func_00157CC0);
INCLUDE_ASM("asm/nonmatchings/src/boyact", func_00157D78);
INCLUDE_ASM("asm/nonmatchings/src/boyact", func_00157E30);
extern float _DistGV(CCPResult *a, CCPResult *b);
extern void *isysGObjSearchFromObjKindID_begin(int id);
extern void *isysGObjSearchFromObjKindID_next(void *);
extern void sceVu0SubVector(void *, CCPResult *, CCPResult *);
extern void *test_CURRENTORIENT(void *a0);
extern CCPResult *test_CURRENTROOT(void *a0);

void ACTSearchEnemy(void *a0, int *out_id, float *out_vec) {
    float buf[4];
    void *node;
    int best;
    float thresh = 300.0f;

    node = isysGObjSearchFromObjKindID_begin((*(int *)((char *)a0 + 0xC) ^ 1) ? 1 : 4);
    *out_id = 0;
    best = 0x5A;
    if (node != 0) {
        do {
            if (*(int *)((char *)node + 0x16C) != 0) {
                CCPResult *r1 = test_CURRENTROOT(a0);
                if (_DistGV(r1, test_CURRENTROOT(node)) < thresh) {
                    int sign;
                    int dist;
                    CCPResult *r4 = test_CURRENTROOT(node);
                    sceVu0SubVector(buf, r4, test_CURRENTROOT(a0));
                    sign = ((int (*)(void *, void *))_RotyGV)(buf, test_CURRENTORIENT(a0));
                    if (sign < 0) {
                        dist = -((int (*)(void *, void *))_RotyGV)(buf, test_CURRENTORIENT(a0));
                    } else {
                        dist = ((int (*)(void *, void *))_RotyGV)(buf, test_CURRENTORIENT(a0));
                    }
                    if (dist < best) {
                        best = dist;
                        out_vec[0] = buf[0];
                        out_vec[1] = buf[1];
                        out_vec[2] = buf[2];
                        *out_id = (int)node;
                    }
                }
            }
            node = isysGObjSearchFromObjKindID_next(node);
        } while (node != 0);
    }
}
INCLUDE_ASM("asm/nonmatchings/src/boyact", DeleteBoyWeapon);
INCLUDE_ASM("asm/nonmatchings/src/boyact", isLiftBoyEnable);
INCLUDE_ASM("asm/nonmatchings/src/boyact", SetKidnapInfo);
extern int D_006C0B30[];
void GetKidnapInfo(int *a0, int *a1) {
    *a0 = D_006C0B30[5];
    *a1 = D_006C0B30[6];
}
INCLUDE_ASM("asm/nonmatchings/src/boyact", PrivInsCamSet);
INCLUDE_ASM("asm/nonmatchings/src/boyact", BoyInfoUpdate_StageChange);
INCLUDE_ASM("asm/nonmatchings/src/boyact", IsBoyStatus_EnemyMustWait);
extern long long D_006C0AD8[];

int IsGirlEscortedInNextStage(void) {
    return (int)((unsigned char)((unsigned long long)D_006C0AD8[0] >> 35)) & 1;
}
extern unsigned char D_0063C1F4;

unsigned char IsGirlEscortedInCurrentStage(void) {
    return D_0063C1F4;
}
INCLUDE_ASM("asm/nonmatchings/src/boyact", GetSaveSofaLayoutID);
extern long long D_006C0AD0[];

void OnGirlEscortFlag(void) {
    D_006C0AD0[1] |= 0x800000000LL;
}
INCLUDE_ASM("asm/nonmatchings/src/boyact", SetBoyWeaponGObj);
INCLUDE_ASM("asm/nonmatchings/src/boyact", IsBoyStatus_NotDanger);
extern void ACTGame_StageChangeGObjDirect(void *a0, void *a1, void *a2, int a3);
extern char D_00552C10[];
extern void *D_00639EA4;
extern unsigned char D_006C0B20[];
extern int RequestStageChangeSimple(void *a0, int a1, int a2, int a3, float a4, float a5);

int RequestStageChangeKidnapEnd(void *a0, int a1) {
    char buf[0x10];
    int rv = 0;
    if (D_00639EA4 != 0) {
        rv = RequestStageChangeSimple(a0, 0, 0, 0, 0.25f, 4.0f) & 0xFF;
        if (rv != 0) {
            D_006C0B20[0] = 1;
            *(int *)(D_006C0B20 + 4) = a1;
            *(long *)buf = *(long *)D_00552C10;
            *(long *)(buf + 8) = *(long *)(D_00552C10 + 8);
            ACTGame_StageChangeGObjDirect(D_00639EA4, a0, buf, 0);
        }
    }
    return rv;
}
extern unsigned char D_006C0B20[];

int GetEfStageCameraTargetID(void)
{
    if (D_006C0B20[0]) {
        return *(int *)(D_006C0B20 + 4);
    }
    return 0;
}
int IsBackFromEfStage(void) {
    return D_006C0B20[0];
}
extern int D_006C0B8C[];
int PrivInsCamChk(void) {
    return D_006C0B8C[0] != 0;
}
extern unsigned char D_006C0B84[];

unsigned char PrivInsCamChk_Control(void) {
    return D_006C0B84[0];
}
extern int D_006C0B30[];

int *GetbufpCharacterPacket(void) {
    return D_006C0B30;
}
int GetsizeCharacterPacket(void) {
    return 32;
}
INCLUDE_ASM("asm/nonmatchings/src/boyact", MakeCharacterPacket);
INCLUDE_ASM("asm/nonmatchings/src/boyact", ReadCharacterPacket);
void ACTSearchGObj(void *a0, int a1, int a2, int *out_id, float *out_vec, float thresh) {
    float buf[4];
    void *node;
    int best;

    node = isysGObjSearchFromObjKindID_begin(a1);
    *out_id = 0;
    best = a2;
    if (node != 0) {
        do {
            if (*(int *)((char *)node + 0x16C) != 0) {
                CCPResult *r1 = test_CURRENTROOT(a0);
                if (_DistGV(r1, test_CURRENTROOT(node)) < thresh) {
                    int sign;
                    int dist;
                    CCPResult *r4 = test_CURRENTROOT(node);
                    sceVu0SubVector(buf, r4, test_CURRENTROOT(a0));
                    sign = ((int (*)(void *, void *))_RotyGV)(buf, test_CURRENTORIENT(a0));
                    if (sign < 0) {
                        dist = -((int (*)(void *, void *))_RotyGV)(buf, test_CURRENTORIENT(a0));
                    } else {
                        dist = ((int (*)(void *, void *))_RotyGV)(buf, test_CURRENTORIENT(a0));
                    }
                    if (dist < best) {
                        best = dist;
                        out_vec[0] = buf[0];
                        out_vec[1] = buf[1];
                        out_vec[2] = buf[2];
                        *out_id = (int)node;
                    }
                }
            }
            node = isysGObjSearchFromObjKindID_next(node);
        } while (node != 0);
    }
}
extern S12 InitialColInfo;
extern char D_0063A700[];
extern void RequestChangeHandMode(void *a0, int a1, int a2, int a3, void *a4, int a5, int a6);
extern void debug_StdPrintfDummy(void *msg);

void afterBoySwim(volatile int a0) {
    RequestChangeHandMode((void *)a0, 0, 3, 0, 0, 0, 0);
    *(S12 *)((char *)GOBJ_SUB(a0) + 0x1C0) = InitialColInfo;
    debug_StdPrintfDummy(D_0063A700);
}
INCLUDE_ASM("asm/nonmatchings/src/boyact", func_00158978);
void afterBoyHangG3M(int x) {
    volatile int local = x;
}
void afterBoyRescueGirlBhang(volatile int a0) {
    ACTGame_DisconnectHand();
}
extern void _ACTWait();

void func_00158AE0(int a0)
{
    volatile int local = a0;
    while (1) {
        _ACTWait(1);
    }
}
void func_00158B00(int *a0, int *a1) {
    int n;
    int i;
    if (a0 != 0) {
        ((int *)D_006C0AD0)[0] = a0[2];
    } else {
        ((int *)D_006C0AD0)[0] = 0;
    }
    i = 0;
    n = 1;
    if (a1 != i) {
        ((int *)D_006C0AD0)[n] = a1[2];
    } else {
        ((int *)D_006C0AD0)[n] = i;
    }
}
INCLUDE_ASM("asm/nonmatchings/src/boyact", GetBoyRootPositionForCamera);
INCLUDE_ASM("asm/nonmatchings/src/boyact", Boy_Init);
