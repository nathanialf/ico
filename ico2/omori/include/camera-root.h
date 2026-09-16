/*
 * ico2/omori/include/camera-root.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what camera-root.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef CAMERA_ROOT_H
#define CAMERA_ROOT_H

extern void Camctrl_ExitEveRock(void);
extern void Camctrl_SetTarget(int a0, int a1, int a2);
extern void CameraChangeTargetParallel(int a0, int a1);
extern void CameraEditManual();
extern int CameraGetMode(void);
extern void CameraGetOtherObjOffset(float *pos, float *outDist, int *outAngle);
extern int CameraGetTarget(void);
extern void CameraGetTargets(int *a0, int *a1);
extern void CameraSetMode(int x);
extern void *GetCameraPos(void);
extern int *GetCurrentCameraSet2(void);
extern void InitCamera(void);
extern void InsertCamera_Exec(float *cam, int *cut, int *cutType, int *enable);
extern void InsertCamera_SetDetail(float *pos, float *tgt, int gobj, int cutType, int b37, int b38, float blend);
extern void InsertCamera_SetNoraml(float *pos, float *tgt, int gobj, int cutType);
extern int InsertCamera_isEnable(void);
extern void MakeCameraMatrix();
extern void ResetHandCameraLimitInDemo(void);
extern void ResetZoomMaxValInDemo(void);
extern void SetCameraFlag_GamecamCutBack(void);
extern void SetCameraFlag_LwsCutBack(void);
extern void SetCameraMatrix(void);
extern void SetHandCameraLimitInDemo(int a0, int a1);
extern void SetMonitorCameraInitializeFlag(void);
extern void SetWSMatrix(void *a0);
extern void SetZoomMaxValInDemo(int a0);

#endif /* CAMERA_ROOT_H */
