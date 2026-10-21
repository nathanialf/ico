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
void Camctrl_ExitEveRock(void);
void Camctrl_SetTarget(struct GObj *gobj, struct GObj *subGObj, int pri);
void CameraChangeTargetParallel(struct GObj *oldTarget, struct GObj *newTarget);
int CameraGetMode(void);
void CameraGetOtherObjOffset(float *pos, float *outDist, int *outAngle);
struct GObj *CameraGetTarget(void);
void CameraGetTargets(struct GObj **gobj, struct GObj **subGObj);
void CameraSetMode(int mode);
void *GetCameraPos(void);
int *GetCurrentCameraSet2(void);
void InitCamera(void);
void InsertCamera_Exec(float *cam, int *cut, int *enable);
void InsertCamera_Set(float *pos, float *tgt, int frames);

void InsertCamera_SetNoraml(float *pos, float *tgt, int frames);

struct CameraSet2;

void MakeCameraMatrix(struct CameraSet2 *cs);
void SetCameraFlag_LwsCutBack(void);
void SetCameraMatrix(struct GObj *self);
void SetMonitorCameraInitializeFlag(void);
void SetWSMatrix(void *src);
void CameraSetTargetGObj(struct GObj *gobj, struct GObj *subGObj);

void GetCameraInfomationFromGlobalPosition(float *pos, float *outDist, int *outAngle, float *fov,
                                           float *zoom);

struct GObj *GetCameraDefaultTargetGObj(void);
void CameraSetCameraPosition(float *src);
void CameraSetTargetPos(void);
void GetCameraInfo_tmp(void *dst, float *out);
void testcamerazoom(void);

#endif /* CAMERA_ROOT_H */
