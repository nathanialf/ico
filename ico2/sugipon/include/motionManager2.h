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

extern int AdjustMotionHeightToNearestField(char *self);
extern void AdjustRootPositionToVerticalSidePlaneOfWall(void *a0, void *a1, float f);
extern void AdjustVerticalSidePlaneOfWall(float *out, int *cfg, float *pos, float t);
extern int CheckFieldContact(char *info, char *self, float *pos, float lim);
extern int CheckFloorAttribute(char *self);
extern int CheckPureWallAttribute(char *self);
extern int CheckWallAttribute(char *self);
extern void ClearMotionBlendlessNode(char *a0);
extern void ClearMotionGeometryInfo(int *self);
extern void CopyMotion(void *dst, void *src, int n);
extern void DisableChangeRootUpdateMode(char *self);
extern void DisableMotionOrientUpdate(char *self);
extern void DispSkelton(GObj *self, int a1);
extern void EnableChangeRootUpdateMode(char *self);
extern void EnableMotionOrientUpdate(char *self);
extern void FeedbackWallWorkInfoToBrainSystem(char *a0);
extern float ForMotionViewer_GetCurrentAnimationFrame(char *self);
extern int ForMotionViewer_GetCurrentMotion(char *self);
extern void GetBlendedMotion(void *dst, float *dv, void *m1, float *v1, void *m0, float *v0, float t, int tbl, int n);
extern float GetDifferenceFromLastField(char *a0, int a1);
extern float GetDifferenceFromWallLowerPlane(char *self, int node);
extern float GetDifferenceFromWallUpperField(char *a0, int a1);
extern float GetDifferenceFromWallUpperPlane(char *self, int node);
extern float GetHeightOfFieldPlaneDifference(int *a, int *b);
extern int GetMotionFrameFlag1(char *self);
extern int GetMotionFrameFlag2(char *self);
extern int GetPureVerticalPlane(void *plane0, void *plane1, float *ptsIn, int *cfg, int flip);
extern void GetRootProjectionPosOfGObj(int a0, int a1);
extern int GetSkeltonFocusNode(char *a0, int a1);
extern int GetStreamMotion(char *dst, float *out, char *node, char *info);
extern int GetStreamShapeMotion(float *dst, void *sm);
extern void InitMotionGeoInfo(char *self, float x, float y, float z, float rx, float ry, float rz);
extern void InitMotionRotElem(int *a0, int count);
extern void InitMotionStateInfo(void *p);
extern void LockForceGroundParent(int gobj);
extern void SetMotionBlendlessNode(char *self, int *node);
extern void SetMotionDirection(void *a0, float *a1);
extern void SetMotionDirectionWithLimit(void *self, float *dir, float lim0, float lim1);
extern void SetMotionNodeFixModeParameter(char *self, char *obj, float x, float y, float z, int mode, int node, float w, void *quat);
extern void SetMotionPlaySpeedRatio(char *self, float val);
extern void SetRootUpdateMode(char *self, int val);
extern void SetSkeltonDispSwitch(int val);
extern void UnlockForceGroundParent(int gobj);
extern void _GetMotionDirection(int a0, int a1);
extern void _getMotion(void *dst, void *m, int node, int frame);
extern void _getS16MotRotElem(void *dst, void *src);

#endif /* MOTIONMANAGER2_H */
