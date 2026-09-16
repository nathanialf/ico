/*
 * ico2/sugipon/include/geometryManager.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what geometryManager.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef GEOMETRYMANAGER_H
#define GEOMETRYMANAGER_H

extern int CylinderCollision(char *self, int group, float r, float h, float s);
extern int CylinderCollisionWithControlDynamics(char *self, int group, int ctrl, float r, float h, float s);
extern int *GetCharGObjList(void);
extern void GetGlobalDirectionOrient(int *self, int *other, char *p);
extern void GetInitialSkeltonMatrixByDObj(char *mdl);
extern float GetProjectionOfPlane(void *a0, void *a1, void *a2);
extern float GetProjectionOfPlaneWithKeepAway(void *a0, void *a1, void *a2, float f);
extern void GetProjectionPosOfPlane(void *a0, void *a1, void *a2);
extern void GetRootMatrix(void *a0, char *outer);
extern void GetRootMatrixRotOffset(void *a0, int a1);
extern void GetRootMatrixTransOffset(char *dst, char *src);
extern void GetRootMotionOrient(char *a0, char *a1);
extern void GetRootOrient(char *a0, char *a1);
extern void GetRootPosition(void *a0, char *outer);
extern void GetRootQuaternion(int a0, int a1);
extern void GetRootQuaternionByDObj(int a0, int *a1);
extern void GlobalizeGeometry(char *gobj);
extern int LimitExistGeometry(float *pos, int *exist);
extern void LocalizeDirectionOrient(int *self, int *a1);
extern void LocalizeGeometry(char *gobj, int *dobj);
extern void SetDirectRootPosition(char *self, void *v);
extern void SetDirectRootPositionNoFitting(char *self, void *v);
extern void SetDirectRootPositionNoFittingWithNodePoint(char *gobj, int node, float *pos, float t);
extern void SetDirectRootPositionNoFittingWithNodePointXZ(char *gobj, int node, float *pos, float t);
extern void SetDirectRootPositionWithNodePoint(char *gobj, int node, float *pos, float t);
extern void SetRootMatrixRotOffset(int a0, void *a1);
extern void SetRootMatrixWithTransOffset(int a0);
extern void SetRootPosition(char *a0, void *a1);
extern void SetRootQuaternion(char *a0, void *a1);
extern void UpdateRootMatrix(int a0);
extern void UpdateRootMatrixByDObj(char *a0);
extern int cylinderCollisionCheck(void *a0, void *a1, int a2, float f0, float f1, float f2, float f3, float f4, int a3, int a4);
extern void getInitialInverseMatrix(char *mat, char *mdl, int no);
extern void getInitialMatrix(char *mdl, int no);

#endif /* GEOMETRYMANAGER_H */
