/*
 * ico2/omori/include/camera-ico2.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what camera-ico2.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef CAMERA_ICO2_H
#define CAMERA_ICO2_H

/* MAIN.MAP global */
extern int current_group;
struct S4C;
struct CamSetFile;

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order camera-ico2.c's inline tail has. */
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
