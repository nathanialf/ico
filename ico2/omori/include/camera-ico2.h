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

extern void AddPluralCameraSet(int id, char *name);
extern void CameraMove(int group, float *pos, float *out, float *ofsA, float *ofsB);
extern void CameraSetCameraSet(int id);
extern void CameraSetCameraSet_Default(void);
extern int GetCameraGroupCurrent(void);
extern void InitIco2Camera(void);
extern void InitPluralCameraSet(void);
extern void *ReadCameraSet(char *name, int stage);
extern void ReflectCameraSetBinary(int a0, int a1);
extern void SetCameraTargetPosition(void *a0, float a1);

#endif /* CAMERA_ICO2_H */
