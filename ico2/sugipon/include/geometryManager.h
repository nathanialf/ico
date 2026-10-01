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

struct GObj;

struct Sub15C;

int CylinderCollision(char *self, int group, float r, float h, float s);

int CylinderCollisionWithControlDynamics(struct GObj *self, int group, int ctrl, float r, float h,
                                         float s);

int *GetCharGObjList(void);
void GetGlobalDirectionOrient(float *dir, struct GObj *obj, void *src);
void GetInitialSkeltonMatrixByDObj(char *mdl);
float GetProjectionOfPlane(void *a0, void *a1, void *a2);
float GetProjectionOfPlaneWithKeepAway(void *a0, void *a1, void *a2, float f);
void GetProjectionPosOfPlane(void *a0, void *a1, void *a2);
void GetRootMatrix(float *m, struct GObj *obj);
void GetRootMatrixRotOffset(void *q, struct GObj *obj);
void GetRootMatrixTransOffset(char *dst, struct GObj *src);
void GetRootMotionOrient(char *a0, struct GObj *a1);
void GetRootOrient(char *a0, struct GObj *a1);
void GetRootPosition(float *pos, struct GObj *obj);
void GetRootPositionByDObj(float *pos, struct Sub15C *src);
void GetRootQuaternion(void *q, struct GObj *obj);
void GetRootQuaternionByDObj(void *q, struct Sub15C *dobj);
void GlobalizeGeometry(struct GObj *gobj);
int LimitExistGeometry(float *pos, int *exist);
void LocalizeDirectionOrient(struct GObj *self, int *link);
void LocalizeGeometry(struct GObj *gobj, int *dobj);
void SetDirectRootPosition(struct GObj *self, void *v);
void SetDirectRootPositionNoFitting(struct GObj *self, void *v);
void SetDirectRootPositionNoFittingWithNodePoint(struct GObj *gobj, int node, float *pos, float t);

void SetDirectRootPositionNoFittingWithNodePointXZ(struct GObj *gobj, int node, float *pos,
                                                   float t);

void SetDirectRootPositionWithNodePoint(struct GObj *gobj, int node, float *pos, float t);
void SetRootMatrixRotOffset(struct GObj *obj, void *q);
void SetRootMatrixWithTransOffset(struct GObj *obj, float x, float y, float z);
void SetRootPosition(struct GObj *obj, void *pos);
void SetRootQuaternion(struct GObj *obj, void *quat);
void SetRootBaseQuaternion(struct GObj *obj, void *q);
void UpdateRootMatrix(struct GObj *obj);
void UpdateRootMatrixByDObj(struct Sub15C *dobj);

int cylinderCollisionCheck(void *a0, void *a1, int a2, float f0, float f1, float f2, float f3,
                           float f4, int a3, int a4);

void getInitialInverseMatrix(char *mat, char *mdl, int no);
void getInitialMatrix(char *mdl, int no);

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: one record for 3 TUs that carried 2 divergent local copies; this body is the one the ROM's bytes accept in the most of them. */
typedef union SubHandle {
    int i;
    char *p;
    struct Sub15C *sub;
} SubHandle;

int GetCylinderCollisionWithExceptOwnCollision(char *self, int target, float r, float h, float s,
                                               float t, int ctrl);

#endif /* GEOMETRYMANAGER_H */
