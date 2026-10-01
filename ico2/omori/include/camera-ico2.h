/*
 * ico2/omori/include/camera-ico2.h
 *
 * The declarations of what camera-ico2.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef CAMERA_ICO2_H
#define CAMERA_ICO2_H

extern int current_group;
struct S4C;
struct CamSetFile;

void GetHandCameraStickInfo(float *outX, float *outZ, float *outMag);
void SetCameraZoomOffsetRatio(float val);
int GetCameraGroupCurrent(void);
int GetCameraGroupFromGObj(void *obj);
int GetCameraGroupFromPosition(float *pos);
void AddPluralCameraSet(int id, char *name);
void InitPluralCameraSet(void);
void *GetPluralCameraSet(int id);
void MakeCameraSetBinary(struct S4C *src, int count, struct S4C *dst);
int GetSizeOfCameraSetBinary(struct S4C *p, int n);
void SetCameraTargetPosition(void *a0, void *a1, float a2);

void CameraMove(int group, float *pos, float *out, float *ofsA, float *ofsB);
void CameraSetCameraSet(int id);
void CameraSetCameraSet_Default(void);
void InitIco2Camera(void);
void *ReadCameraSet(struct CamSetFile *f, int stage);
void ReflectCameraSetBinary(struct S4C *src, int count);
void SetCameraMatrix_Ico2(int flag);

#endif /* CAMERA_ICO2_H */
