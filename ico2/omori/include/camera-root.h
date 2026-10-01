/*
 * ico2/omori/include/camera-root.h
 *
 * The declarations of what camera-root.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef CAMERA_ROOT_H
#define CAMERA_ROOT_H

extern int CameraCalclated_f;
extern int default_cameratarget_gobj;
extern int InsertCameraWorkingFlag;
extern int FixViewInGameCameraFlag;
extern int monitorCameraHold;      /* the title shortcut holds the monitor camera */
extern int insertCameraBlendTimer; /* frames left of the blend after an insert camera */
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

void InsertCamera_SetDetail(float *pos, float *tgt, int frames, int cutType, int zoom, int cutBack,
                            float blend);

void InsertCamera_SetNoraml(float *pos, float *tgt, int frames, int cutType);
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
void DebugCameraManual(void);
void DebugCameraSemiAuto(void);
void BackToGameCamera(void);
void CameraSetTargetGObj(int a, int b);
int UpdateHandCameraLimitP(void);
int UpdateHandCameraLimitV(void);
int UpdateZoomMaxVallInDemo(void);

#endif /* CAMERA_ROOT_H */
