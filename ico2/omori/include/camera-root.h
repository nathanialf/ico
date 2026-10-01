/*
 * ico2/omori/include/camera-root.h
 *
 * The declarations of what camera-root.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef CAMERA_ROOT_H
#define CAMERA_ROOT_H

extern int CameraCalclated_f;
extern struct GObj *default_cameratarget_gobj;
extern int InsertCameraWorkingFlag;
extern int FixViewInGameCameraFlag;
extern int monitorCameraHold;      /* the title shortcut holds the monitor camera */
extern int insertCameraBlendTimer; /* frames left of the blend after an insert camera */
void Camctrl_ExitEveRock(void);
void Camctrl_SetTarget(struct GObj *gobj, struct GObj *subGObj, int pri);
void CameraChangeTargetParallel(struct GObj *from, struct GObj *to);
int CameraGetMode(void);
void CameraGetOtherObjOffset(float *pos, float *outDist, int *outAngle);
struct GObj *CameraGetTarget(void);
void CameraGetTargets(struct GObj **gobj, struct GObj **subGObj);
void CameraSetMode(int x);
void *GetCameraPos(void);
int *GetCurrentCameraSet2(void);
void InitCamera(void);
void InsertCamera_Exec(float *cam, int *cut, int *cutType, int *enable);
void InsertCamera_Set(float *pos, float *tgt, int frames);

void InsertCamera_SetDetail(float *pos, float *tgt, int frames, int cutType, int zoom, int cutBack,
                            float blend);

void InsertCamera_SetNoraml(float *pos, float *tgt, int frames, int cutType);

struct CameraSet2;

void MakeCameraMatrix(struct CameraSet2 *cs);
void ResetHandCameraLimitInDemo(void);
void ResetZoomMaxValInDemo(void);
void SetCameraFlag_GamecamCutBack(void);
void SetCameraFlag_LwsCutBack(void);
void SetCameraMatrix(void);
void SetHandCameraLimitInDemo(int limitP, int limitV);
void SetMonitorCameraInitializeFlag(void);
void SetWSMatrix(void *src);
void SetZoomMaxValInDemo(int zoom);
void CameraSetTargetGObj(struct GObj *a, struct GObj *b);
int UpdateHandCameraLimitP(void);
int UpdateHandCameraLimitV(void);
int UpdateZoomMaxVallInDemo(void);

#endif /* CAMERA_ROOT_H */
