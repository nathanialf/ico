/*
 * ico2/sugipon/include/motionManager2.h
 *
 * The declarations of what motionManager2.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef MOTIONMANAGER2_H
#define MOTIONMANAGER2_H

/* the 32-byte motion record CopyMotion and CopyMotionWithNodeHrc copy
   (motionManager2.c) */
struct Pack32;
struct ClipBuf;

#include "typedef.h"

int AdjustMotionHeightToNearestField(GObj *self);
void AdjustRootPositionToVerticalSidePlaneOfWall(void *a0, void *a1, float f);
void AdjustVerticalSidePlaneOfWall(float *out, WallCfg *cfg, float *pos, float t);
int CheckFieldContact(struct ClipBuf *info, GObj *self, float *pos, float lim);
/* the GObj and the attribute mask (act_bird.c passes 0x40 and 0x50;
   boyact, script, a_p_1 and frameDependSequence do the same) */
int CheckFloorAttribute(GObj *self, int attr);
int CheckPureWallAttribute(GObj *self, int attr);
int CheckWallAttribute(GObj *self, int attr);
int CheckPureCliffAttribute(GObj *self, int attr);
void ClearMotionBlendlessNode(GObj *a0);
void ClearMotionGeometryInfo(GObj *self);
void CopyMotion(void *dst, void *src, int n);
void DebugDisp1Collision(WallCfg *cfg);
void DebugDisp1CollisionWithColor(WallCfg *cfg, void *color);
void DisableChangeRootUpdateMode(GObj *self);
void DisableMotionOrientUpdate(GObj *self);
void DispSkelton(GObj *self, int a1);
void EnableChangeRootUpdateMode(GObj *self);
void EnableMotionOrientUpdate(GObj *self);
void FeedbackWallWorkInfoToBrainSystem(GObj *a0);
float ForMotionViewer_GetCurrentAnimationFrame(GObj *self);
int ForMotionViewer_GetCurrentMotion(GObj *self);

void GetBlendedMotion(void *dst, float *dv, void *m1, float *v1, void *m0, float *v0, float t,
                      int tbl, int n);

float GetDifferenceFromLastField(GObj *a0, int a1);
float GetDifferenceFromWallLowerPlane(GObj *self, int node);
float GetDifferenceFromWallUpperField(GObj *a0, int a1);
float GetDifferenceFromWallUpperPlane(GObj *self, int node);
float GetHeightOfFieldPlaneDifference(GObj *a, GObj *b);
int GetMotionFrameFlag1(GObj *self);
int GetMotionFrameFlag2(GObj *self);
int GetPureVerticalPlane(void *plane0, void *plane1, float *ptsIn, WallCfg *cfg, int flip);
int GetPureVerticalPlaneOfCurrentPosition(void *plane0, void *plane1, float *ptsIn, WallCfg *cfg,
                                          int flip, float *pos);
void GetRootProjectionPosOfGObj(float *pos, GObj *obj);
int GetSkeltonFocusNode(GObj *a0, int a1);
int GetStreamMotion(char *dst, float *out, char *node, char *info);
int GetStreamShapeMotion(float *dst, void *sm);
void InitMotionGeoInfo(char *self, float x, float y, float z, float rx, float ry, float rz);
void InitMotionRotElem(int *a0, int count);
void InitMotionStateInfo(void *p);
void LockForceGroundParent(GObj *gobj);
void SetMotionBlendlessNode(GObj *self, int *node);
void SetMotionDirection(GObj *a0, float *a1);
void SetMotionDirectionWithLimit(GObj *self, float *dir, float lim0, float lim1);

void SetMotionNodeFixModeParameter(GObj *self, GObj *obj, int mode, int node, void *quat, float x,
                                   float y, float z, float w);

void SetMotionPlaySpeedRatio(GObj *self, float val);
void SetRootUpdateMode(GObj *self, int val);
void SetSkeltonDispSwitch(int val);
void UnlockForceGroundParent(GObj *gobj);
void _GetMotionDirection(float *dir, GObj *obj);
void _getMotion(void *dst, void *m, int node, int frame);
void _getS16MotRotElem(void *dst, void *src);
void SlopeIKControl(GObj *self, char *arg, int a2, Vec4 *vel);
void CopyMotionWithNodeHrc(struct Pack32 *dst, struct Pack32 *src, char *hrc, int node, int flag);
void GetFloatingShapeMotion(float *dst, char *m, float t, int count);
void GetFloatingMotionRootPos(float *dst, void *m, float t);
void GetOutOutsideOfWall(GObj *obj, float threshold);

#endif /* MOTIONMANAGER2_H */
