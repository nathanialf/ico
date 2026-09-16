/*
 * ico2/sugipon/include/motionManager2.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what motionManager2.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef MOTIONMANAGER2_H
#define MOTIONMANAGER2_H

#include "typedef.h"

int AdjustMotionHeightToNearestField(char *self);
void AdjustRootPositionToVerticalSidePlaneOfWall(void *a0, void *a1, float f);
void AdjustVerticalSidePlaneOfWall(float *out, int *cfg, float *pos, float t);
int CheckFieldContact(char *info, char *self, float *pos, float lim);
int CheckFloorAttribute(char *self);
int CheckPureWallAttribute(char *self);
int CheckWallAttribute(char *self);
void ClearMotionBlendlessNode(char *a0);
void ClearMotionGeometryInfo(int *self);
void CopyMotion(void *dst, void *src, int n);
void DisableChangeRootUpdateMode(char *self);
void DisableMotionOrientUpdate(char *self);
void DispSkelton(GObj *self, int a1);
void EnableChangeRootUpdateMode(char *self);
void EnableMotionOrientUpdate(char *self);
void FeedbackWallWorkInfoToBrainSystem(char *a0);
float ForMotionViewer_GetCurrentAnimationFrame(char *self);
int ForMotionViewer_GetCurrentMotion(char *self);
void GetBlendedMotion(void *dst, float *dv, void *m1, float *v1, void *m0, float *v0, float t, int tbl, int n);
float GetDifferenceFromLastField(char *a0, int a1);
float GetDifferenceFromWallLowerPlane(char *self, int node);
float GetDifferenceFromWallUpperField(char *a0, int a1);
float GetDifferenceFromWallUpperPlane(char *self, int node);
float GetHeightOfFieldPlaneDifference(int *a, int *b);
int GetMotionFrameFlag1(char *self);
int GetMotionFrameFlag2(char *self);
int GetPureVerticalPlane(void *plane0, void *plane1, float *ptsIn, int *cfg, int flip);
void GetRootProjectionPosOfGObj(int a0, int a1);
int GetSkeltonFocusNode(char *a0, int a1);
int GetStreamMotion(char *dst, float *out, char *node, char *info);
int GetStreamShapeMotion(float *dst, void *sm);
void InitMotionGeoInfo(char *self, float x, float y, float z, float rx, float ry, float rz);
void InitMotionRotElem(int *a0, int count);
void InitMotionStateInfo(void *p);
void LockForceGroundParent(int gobj);
void SetMotionBlendlessNode(char *self, int *node);
void SetMotionDirection(void *a0, float *a1);
void SetMotionDirectionWithLimit(void *self, float *dir, float lim0, float lim1);
void SetMotionNodeFixModeParameter(char *self, char *obj, float x, float y, float z, int mode, int node, float w, void *quat);
void SetMotionPlaySpeedRatio(char *self, float val);
void SetRootUpdateMode(char *self, int val);
void SetSkeltonDispSwitch(int val);
void UnlockForceGroundParent(int gobj);
void _GetMotionDirection(int a0, int a1);
void _getMotion(void *dst, void *m, int node, int frame);
void _getS16MotRotElem(void *dst, void *src);

#endif /* MOTIONMANAGER2_H */
