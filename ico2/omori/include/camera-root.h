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

void Camctrl_ExitEveRock(void);
void Camctrl_SetTarget(int a0, int a1, int a2);
void CameraChangeTargetParallel(int a0, int a1);
void CameraEditManual();
int CameraGetMode(void);
void CameraGetOtherObjOffset(float *pos, float *outDist, int *outAngle);
int CameraGetTarget(void);
void CameraGetTargets(int *a0, int *a1);
void CameraSetMode(int x);
void *GetCameraPos(void);
int *GetCurrentCameraSet2(void);
void InitCamera(void);
void InsertCamera_Exec(float *cam, int *cut, int *cutType, int *enable);
void InsertCamera_SetDetail(float *pos, float *tgt, int gobj, int cutType, int b37, int b38, float blend);
void InsertCamera_SetNoraml(float *pos, float *tgt, int gobj, int cutType);
int InsertCamera_isEnable(void);
void MakeCameraMatrix();
void ResetHandCameraLimitInDemo(void);
void ResetZoomMaxValInDemo(void);
void SetCameraFlag_GamecamCutBack(void);
void SetCameraFlag_LwsCutBack(void);
void SetCameraMatrix(void);
void SetHandCameraLimitInDemo(int a0, int a1);
void SetMonitorCameraInitializeFlag(void);
void SetWSMatrix(void *a0);
void SetZoomMaxValInDemo(int a0);

#endif /* CAMERA_ROOT_H */
