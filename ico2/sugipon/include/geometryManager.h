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

int CylinderCollision(char *self, int group, float r, float h, float s);
int CylinderCollisionWithControlDynamics(char *self, int group, int ctrl, float r, float h, float s);
int *GetCharGObjList(void);
void GetGlobalDirectionOrient(int *self, int *other, char *p);
void GetInitialSkeltonMatrixByDObj(char *mdl);
float GetProjectionOfPlane(void *a0, void *a1, void *a2);
float GetProjectionOfPlaneWithKeepAway(void *a0, void *a1, void *a2, float f);
void GetProjectionPosOfPlane(void *a0, void *a1, void *a2);
void GetRootMatrix(void *a0, char *outer);
void GetRootMatrixRotOffset(void *a0, int a1);
void GetRootMatrixTransOffset(char *dst, char *src);
void GetRootMotionOrient(char *a0, char *a1);
void GetRootOrient(char *a0, char *a1);
void GetRootPosition(void *a0, char *outer);
void GetRootQuaternion(int a0, int a1);
void GetRootQuaternionByDObj(int a0, int *a1);
void GlobalizeGeometry(char *gobj);
int LimitExistGeometry(float *pos, int *exist);
void LocalizeDirectionOrient(int *self, int *a1);
void LocalizeGeometry(char *gobj, int *dobj);
void SetDirectRootPosition(char *self, void *v);
void SetDirectRootPositionNoFitting(char *self, void *v);
void SetDirectRootPositionNoFittingWithNodePoint(char *gobj, int node, float *pos, float t);
void SetDirectRootPositionNoFittingWithNodePointXZ(char *gobj, int node, float *pos, float t);
void SetDirectRootPositionWithNodePoint(char *gobj, int node, float *pos, float t);
void SetRootMatrixRotOffset(int a0, void *a1);
void SetRootMatrixWithTransOffset(int a0);
void SetRootPosition(char *a0, void *a1);
void SetRootQuaternion(char *a0, void *a1);
void UpdateRootMatrix(int a0);
void UpdateRootMatrixByDObj(char *a0);
int cylinderCollisionCheck(void *a0, void *a1, int a2, float f0, float f1, float f2, float f3, float f4, int a3, int a4);
void getInitialInverseMatrix(char *mat, char *mdl, int no);
void getInitialMatrix(char *mdl, int no);

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: one record for 3 TUs that carried 2 divergent local copies; this body is the one the ROM's bytes accept in the most of them. */
typedef union SubHandle {
    int i;
    char *p;
} SubHandle;

#endif /* GEOMETRYMANAGER_H */
