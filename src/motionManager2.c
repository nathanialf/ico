#include "common.h"













extern int D_00631B48;
extern void func_00243AD0();
extern char D_00275850[];
extern void GetRootMatrixByDObj();
extern void GetMatrixFromQuaternion();
extern float func_00168C18();
extern int func_00168A80();
extern void _SetCurrentMatrix();
extern void func_00168AE0();
extern float D_0063094C;
extern void LoadCollision();
extern float D_00630948;
extern void ChangeFieldCollisionDebugMode();
extern void MatrixDrive_GetTurnXAngleZY();
extern void GetRootMatrixRotOffset();
#include "ico/types.h"
extern void MatrixDrive_TurnObjectMatrix();
void GetWaterReaction(int a0, int a1)
{
    MatrixDrive_TurnObjectMatrix(a0, (int)((GObj *)(a1))->p_15C + 0x5C0);
}

void CheckFieldContact(int a0, int a1)
{
    MatrixDrive_TurnObjectMatrix(a0, (int)((GObj *)(a1))->p_15C + 0x590);
}

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", dispPlane);

void GetOrientOfWallOfGObj(int a0, int a1)
{
    GetRootMatrixRotOffset(a0, a1, (int)((GObj *)(a1))->p_15C + 0x520);
}

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", GetOrientOfCliffOfGObj);

void SetMotionDirection(int a0, int *a1)
{
  int *p = (int *)((GObj *)(a1))->p_15C;
  char *new_var;
  new_var = ((char *) p) + 0xA0;
  MatrixDrive_TurnObjectMatrix(a0, (int) (((char *) p) + 0x130));
  MatrixDrive_GetTurnXAngleZY(a0, a0, (int) new_var);
}

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", _GetMotionDirection);

void SetMotionDirectionWithLimit(int a0, int a1)
{
    MatrixDrive_TurnObjectMatrix(a0, a1);
    MatrixDrive_TurnObjectMatrix(a0 + 0x10, a0);
    *(float *)(a0 + 0x14) = *(float *)(a0 + 0x14) + D_00630948;
    ChangeFieldCollisionDebugMode(a0);
}

void GetRootPosOfNextFrame(int a0, int a1)
{
    MatrixDrive_TurnObjectMatrix(a0, a1);
    MatrixDrive_TurnObjectMatrix(a0 + 0x10, a0);
    *(float *)(a0 + 0x14) = *(float *)(a0 + 0x14) + D_0063094C;
    LoadCollision(a0);
}

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", AdjustMotionHeightToField);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", GetLowerPlaneCollision);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", getLowerPlaneCollisionE);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", calcFootIK);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", InitMotionGeoInfo);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", dispSkeltonHierarchy);

void DispSkelton(int *self, int *p, int *cfg)
{
    int *obj = (int *)cfg[0];
    int sh = cfg[1] << 6;
    int *p15c = (int *)((GObj *)(obj))->p_15C;
    int v_c = p15c[0xC / 4];

    func_00168AE0(self, p, cfg[2], v_c + sh);
    p[1] = 0;
    _SetCurrentMatrix(p, p);
}

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", SlopeIKControl);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", GetPureVerticalPlaneOfCurrentPosition);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", getVerticalElementOfWallNormal);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", AdjustVerticalSidePlaneOfWall);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", GetPureVerticalPlane);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", _getS16MotRotElem);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", _getMotion);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", GetMotion);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", GetStreamMotion);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", copyMotionWithNodeHrc);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", CopyMotionWithNodeHrc);

void *GetFloatingMotion(char *self) {
    return (char *)((GObj *)(self))->p_15C + 0x680;
}

int MakeMirrorMotion(char *self) {
    return ((GObj *)(self))->p_15C->f_1E0;
}

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", GetFloatingShapeMotion);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", FeedbackWallWorkInfoToBrainSystem);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", GetMotionPointer);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", GetCollisionOfLastActiveField);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", DebugDisp1Collision);

char DebugDisp1CollisionWithColor(char *self, int idx) {
    char *sub = ((GObj *)(self))->p_15C;
    char *table = *(char **)(sub + 0x810);
    return table[idx];
}

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", SetMotionBlendlessNode);

void ClearMotionBlendlessNode(char *self, int val) {
    ((GObj *)(self))->p_15C->f_4D8 = val;
}

float InitMotionStateInfo(char *self) {
    return *(float *)(*(char **)(self + 0x15C) + 0x4AC);
}

int GetSkeltonFocusNode(char *self) {
    return ((GObj *)(self))->p_15C->f_4A0;
}

void AdjustMotionHeightToNearestField(char *self) {
    ((GObj *)(self))->p_15C->f_4E4 = 0;
}

void SetRootUpdateMode(char *self) {
    ((GObj *)(self))->p_15C->f_4E4 = 1;
}

int ForMotionViewer_GetCurrentAnimationFrame(char *self) {
    char *sub = ((GObj *)(self))->p_15C;
    return func_00168A80(*(int *)(sub + 0x5F8));
}

int ForMotionViewer_GetCurrentMotion(char *self) {
    char *sub = ((GObj *)(self))->p_15C;
    return func_00168A80(*(int *)(sub + 0x5F4));
}

int EnableMotionOrientUpdate(char *self) {
    char *sub = ((GObj *)(self))->p_15C;
    return func_00168A80(*(int *)(sub + 0x5EC));
}

int DisableMotionOrientUpdate(char *self) {
    char *sub = ((GObj *)(self))->p_15C;
    return func_00168A80(*(int *)(sub + 0x5F0));
}

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", CheckFloorAttribute);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", CheckWallAttribute);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", CheckPureWallAttribute);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", CheckPureCliffAttribute);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", GetStreamShapeMotion);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", GetDifferenceFromWallUpperField);

void GetDifferenceFromLastField(char *self) {
    char *sub = ((GObj *)(self))->p_15C;
    *(int *)(sub + 0x4D0) = 1;
}

void GetDifferenceFromLowerField(char *self) {
    char *sub = ((GObj *)(self))->p_15C;
    *(int *)(sub + 0x4D0) = 0;
}

float GetDifferenceFromWallLowerPlane(char *self) {
    char *sub = ((GObj *)(self))->p_15C;
    return *(float *)(sub + 0x618);
}

int GetDifferenceFromWallUpperPlane(char *self) {
    char *sub = ((GObj *)(self))->p_15C;
    return *(int *)(sub + 0x600);
}

int DisableChangeRootUpdateMode(char *self) {
    char *sub = ((GObj *)(self))->p_15C;
    return *(int *)(sub + 0x604);
}

float EnableChangeRootUpdateMode(int *a, int *b)
{
    int *pa;
    int *pb;
    float r1;
    float r2;
    pa = (int *)((GObj *)(a))->p_15C;
    r1 = func_00168C18((int *)((char *)pa + 0x1D0), (int *)((char *)pa + 0xA0));
    pb = (int *)((GObj *)(b))->p_15C;
    r2 = func_00168C18((int *)((char *)pb + 0x1D0), (int *)((char *)pb + 0xA0));
    return r1 - r2;
}

float GetRopeHangablePos(char *self) {
    char *sub = ((GObj *)(self))->p_15C;
    return *(float *)(sub + 0x5A0);
}

float GetMotionFrameFlag1(char *self) {
    char *sub = ((GObj *)(self))->p_15C;
    return *(float *)(sub + 0x580);
}

void GetMotionFrameFlag2(int *a0, int count)
{
    int *p;
    int i;
    if (count <= 0) return;
    p = a0;
    i = count;
loop:
    p[0] = 0;
    {
        int *call_arg = p + 4;
        p += 8;
        GetMatrixFromQuaternion(call_arg);
    }
    --i;
    if (i != 0) goto loop;
}

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", GetHeightOfFieldPlaneDifference);

void GetHeightOfWallFromGObj(int a0, int a1)
{
    GetRootMatrixByDObj(a0, a1);
    *(float *)(a0 + 0x4) += *(float *)((int)((GObj *)(a1))->p_15C + 0x270);
}

void GetHeightOfCliffFromGObj(char *self, float val) {
    *(float *)(*(char **)(self + 0x15C) + 0x4B8) = val;
}

void InitMotionRotElem(int *self)
{
  int *p = (int *)((GObj *)(self))->p_15C;
  int *p1 = (int *) (((char *) p) + 0x230);
  int *p2 = (int *) (((char *) p) + 0xA0);
  int ret;
  MatrixDrive_TurnObjectMatrix(p1, D_00275850);
  func_00243AD0((int *) (((char *) p) + 0x250), p2, p1);
  ret = -1;
  *((int *) (((char *) p2) + 0x180)) = ret;
  return ret;
}

void SetMotionNodeFixModeParameter(int val) {
    D_00631B48 = val;
}

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", GetRootProjectionPosOfGObj);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", SetMotionPlaySpeedRatio);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", ClearMotionGeometryInfo);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", SetSkeltonDispSwitch);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", CopyMotion);

void GetMotionRootPos(float *dst, char *a1, int idx, int count)
{
    int i = 0;
    int m = *(int *)a1 - 1;
    int rem = idx - m * (idx / m);
    for (; i < count; i++) {
        char *t = *(char **)(a1 + 0x10);
        int *elem = *(int **)(*(char **)(t + 4) + i * 4);
        if (elem != 0) {
            dst[i] = ((float *)elem)[rem];
        } else {
            dst[i] = 0;
        }
    }
}

