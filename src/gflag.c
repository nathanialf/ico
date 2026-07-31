#include "common.h"














extern int isysGObjSearchFromObjKindID_begin();
extern int isysGObjSearchFromObjLayoutID();
extern void func_00154668();
extern unsigned char D_005F2FB8[];
extern char D_00561928[];
extern void backStageProcessOutStage(int val);
extern void stgmgrForceSwitchWithFade(int val);
extern int D_00631990;
extern void func_001EB310();
extern void func_001EB418();
extern void func_001EB3A8();
extern int isysGObjAddHead();
extern void GetOtherStageGirlOrient(char *a0);
extern int func_001D4B40();
extern void func_0014B768(int a0);
extern int iosOmBeforeFuncStandard(char *self_arg, int val5, int val6);
extern void func_00243978();
extern int dispPlane();
extern void debug_assertMessage();
extern void InitCageFixGeo(char *self, float val);
extern const char D_00559E60[];
extern void func_001F19F0();
extern int actSt25aQueenDeadChk();
extern void func_001F1868(void *a0);

void gflagInit(void) {
    void *r = actSt25aQueenDeadChk();
    if (r) {
        func_001F1868(r);
    }
}

void gflagSave(void)
{
    int v = actSt25aQueenDeadChk();
    if (v) {
        func_001F19F0(v);
    }
}

void gflagLoad(float f12) {
    int *v = actSt25aQueenDeadChk();
    if (v) {
        InitCageFixGeo(v, f12);
    }
    debug_assertMessage(D_00559E60);
}

void gflagChk(int a0, int a1)
{
    int new_var;
    new_var = 1;
    if (new_var) {
        func_00243978(a1);
    }
    return dispPlane(a0, (0, a1));
}

INCLUDE_ASM("asm/nonmatchings/src/gflag", gflagOn);

extern void *D_00631AE4;
extern void *D_00631AE8;
extern int ExecMotionOrient(void *a0, int a1, int a2);
extern void actCommonSlowrun(int a0, int a1);
extern void func_001E4798(void *a0, int a1, int a2, int a3, int a4, int a5);

void gflagOff(void *a0, int a1) {
    int state = -1;
    int s3 = *(int *)((char *)a0 + 0x164);
    if (a0 == D_00631AE4) {
        state = 0x4BE;
    } else if (a0 == D_00631AE8) {
        state = 0x718;
    } else if (a0 == isysGObjAddHead(0x7AE)) {
        state = 0x83F;
    } else if ((*(int *)((char *)a0 + 0xC) ^ 4) == 0) {
        state = 0x837;
    }
    if (state < 0) {
        func_001E4798(a0, 0x71C, 0x839, -1, -1, a1);
        return;
    }
    actCommonSlowrun(state, a1);
    *(int *)(s3 + 0x120) = ExecMotionOrient(a0, 0xEC, s3 + 0x610);
}

void func_0017B4E0(int *self, int a1)
{
    int *p;
    func_0014B768((int)self);
    p = (int *)((int *)self[0x164 / 4])[0x670 / 4];
    p[0xC0 / 4] = a1;
    iosOmBeforeFuncStandard((int)self, 0x2D, (int)self);
}

void func_0017B528(int a0)
{
    int new_var;
    func_0014B768(a0);
    iosOmBeforeFuncStandard(a0, 0x2E, a0);
    new_var = func_001D4B40(a0, 0);
    return new_var;
}

void func_0017B568(int a0)
{
    iosOmBeforeFuncStandard(a0, 0x2F, a0);
    func_001D4B40(a0, 2);
}

extern void UpdateRootMatrixByDObj(void *a0, float x, float y, float z);

void func_0017B5A0(void *a0, float *rot)
{
    UpdateRootMatrixByDObj(a0, rot[0], rot[1], rot[2]);
}

INCLUDE_ASM("asm/nonmatchings/src/gflag", func_0017B5B0);

/* gflag .rodata run 0x559E60..0x55A1B0 -- byte-verified against baseelf;
 * defs interleave with INCLUDE_ASM stubs so .o section order == VMA order.
 * Heavily interleaved with src/script/src/warpGirl (SHARED/foreign blocks
 * per map_data_tus.py); all interior, safe per the conservative-edge rule. */
const char D_00559E60[0x48] = "ぶら下がりオブジェクトが見つかりません。(scpSetCageVelocityFriction)\n\0\0\0";
const char D_00559EA8[0x48] = "押し回しオブジェクトが見つかりません。(scpGetRotObjectRotCount)\n\0\0\0\0\0\0\0\0";
const char D_00559EF0[0x48] = "押し回しオブジェクトが見つかりません。(scpGetRotObjectZDirInclude)\n\0\0\0\0\0";
const char D_00559F38[0x48] = "LWSのスケルトンペアレント処理において,ノードが見つかりませんでした\n\0\0\0\0\0";
const char D_00559F80[0x70] = "scpGetWallCollision: (%4.3f, %4.3f, %4.3f) => (%4.3f, %4.3f, %4.3f)\n\t壁コリジョンが見つかりません。\n\0\0\0\0\0\0\0\0\0\0\0\0";
const unsigned int D_00559FF0[0x4] = { 0x00000000, 0x00000010, 0x00000020, 0x00000080 };
const unsigned int D_0055A000[0x4] = { 0x00000001, 0x00000002, 0x00000004, 0x00000000 };
const unsigned int D_0055A010[0x4] = { 0x00000001, 0x00000002, 0x00000004, 0xFFFFFFFF };
const unsigned int D_0055A020[0x4] = { 0x00000001, 0x00000002, 0x00000004, 0x00000011 };

INCLUDE_ASM("asm/nonmatchings/src/gflag", func_0017B760);

INCLUDE_ASM("asm/nonmatchings/src/gflag", func_0017B8B0);

const char D_0055A060[0x20] = "ADPCM一杯で開けませんでした。\n\0\0";
const char D_0055A080[0x58] = "戦闘曲を止めて,変わりにリクエストします。以降ステージ切り換えまで戦闘曲なりません。\n\0\0\0\0";
const char D_0055A0D8[0x60] = "戦闘曲なっていないので,プログラムを止めないために\n全部曲を止めて,変わりにリクエストします。\n\0\0\0\0";
const char D_0055A138[0x10] = "deamon start\0\0\0\0";

INCLUDE_ASM("asm/nonmatchings/src/gflag", func_0017BA00);

INCLUDE_ASM("asm/nonmatchings/src/gflag", func_0017BB98);

INCLUDE_RODATA("asm/nonmatchings/src/gflag", D_0055A198);
const unsigned int D_0055A1A0[0x4] = { 0x45CFB000, 0xC506D000, 0x4489C000, 0x00000000 };

INCLUDE_ASM("asm/nonmatchings/src/gflag", func_0017BF78);

INCLUDE_ASM("asm/nonmatchings/src/gflag", func_0017C5B8);

void func_0017C818(char *a0)
{
    long long *p = (long long *)(*(int *)(a0 + 0x164) + 0x18);
    *p &= ~((long long)0x400 << 32);
    return GetOtherStageGirlOrient(a0);
}

INCLUDE_ASM("asm/nonmatchings/src/gflag", func_0017C840);

void func_0017C8C0(void)
{
    int rc = isysGObjAddHead();
    if (rc) {
        iosOmBeforeFuncStandard(rc, 0x1F, rc);
    }
}

void func_0017C8F8(void)
{
    int rc = isysGObjAddHead();
    if (rc) {
        iosOmBeforeFuncStandard(rc, 0x20, rc);
    }
}

void func_0017C930(void)
{
    int v = isysGObjAddHead();
    if (v) {
        func_001EB3A8(v);
    }
}

void func_0017C960(void)
{
    int v = isysGObjAddHead();
    if (v) {
        func_001EB418(v);
    }
}

void func_0017C990(void)
{
    func_001EB310(isysGObjAddHead());
}

void func_0017C9B0(int idx)
{
  int new_var;
  char *p;
  char *q;
  int new_var2;
  short s;
  new_var = 0xA0;
  p = &D_005F2FB8[new_var];
  new_var = ((idx - 1) * 2) + (D_00631990 * 0x194);
  s = *((short *) (p + new_var));
  new_var2 = 0x28;
  ;
  q = &D_00561928[new_var];
  stgmgrForceSwitchWithFade(*((int *) ((&D_00561928[s * new_var2]) + 0x24)));
  backStageProcessOutStage(1);
}

void func_0017CA10(int a0, int a1, int a2, int a3)
{
    func_00154668(a0, a1, a2, a3);
}

void func_0017CA18(void)
{
    int v0 = isysGObjSearchFromObjLayoutID();
    while (v0 != 0) {
        *(int *)(v0 + 0x50) = 0;
        v0 = isysGObjSearchFromObjKindID_begin(v0);
    }
}

void func_0017CA58(int x)
{
  unsigned int new_var;
  int *p = isysGObjSearchFromObjLayoutID(x);
  while (p != 0)
  {
    new_var = (int) 0xFFFFFFFFU;
    p[0x50 / 4] = new_var;
    p = isysGObjSearchFromObjKindID_begin(p);
  }

}

void func_0017CAA0(void)
{
    int *p = isysGObjSearchFromObjLayoutID();
    while (p != 0) {
        p[0x16C / 4] = 1;
        p = isysGObjSearchFromObjKindID_begin(p);
    }
}

void func_0017CAE0(void)
{
    int v0 = isysGObjSearchFromObjLayoutID();
    while (v0 != 0) {
        *(int *)(v0 + 0x16C) = 0;
        v0 = isysGObjSearchFromObjKindID_begin(v0);
    }
}

