/*
 * ico2/sugipon/include/geometryManager.h
 *
 * The declarations of what geometryManager.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef GEOMETRYMANAGER_H
#define GEOMETRYMANAGER_H

struct GObj;

struct Sub15C;

int CylinderCollision(struct GObj *self, int group, float r, float h, float s);

int CylinderCollisionWithControlDynamics(struct GObj *self, int group, int ctrl, float r, float h,
                                         float s);

struct GObj **GetCharGObjList(void);
void GetGlobalDirectionOrient(float *dir, struct GObj *obj, void *src);
void GetInitialSkeltonMatrixByDObj(char *mdl);
float GetProjectionOfPlane(void *a0, void *a1, void *a2);
float GetProjectionOfPlaneWithKeepAway(void *a0, void *a1, void *a2, float f);
void GetProjectionPosOfPlane(void *a0, void *a1, void *a2);
void GetRootMatrix(void *mtx, struct GObj *obj);
void GetRootMatrixRotOffset(void *q, struct GObj *obj);
void GetRootMatrixTransOffset(float *dst, struct GObj *src);
void GetRootMotionOrient(char *a0, struct GObj *a1);
void GetRootOrient(char *a0, struct GObj *a1);
void GetRootPosition(void *pos, struct GObj *obj);
void GetRootPositionByDObj(void *pos, struct Sub15C *src);
void GetRootQuaternion(void *q, struct GObj *obj);
void GetRootQuaternionByDObj(void *q, struct Sub15C *dobj);
void GlobalizeGeometry(struct GObj *gobj);
int LimitExistGeometry(float *pos, float *move);
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

int cylinderCollisionCheck(struct GObj *self, float *ppos, struct GObj *target, float r, float rr,
                           float h, float s, float t, int ctrl, int exceptOwn);

/* the GObj's sub-object slot, read as an int, a byte pointer or a Sub15C */
typedef union SubHandle { /* field names derived */
    int i;
    char *p;
    struct Sub15C *sub;
} SubHandle; /* derived name */

int GetCylinderCollisionWithExceptOwnCollision(struct GObj *self, struct GObj *target, float r,
                                               float h, float s, float t, int ctrl);

void SetRootMatrixWithTransOffsetByDObj(struct Sub15C *dobj, float x, float y, float z);
void GetRootMatrixRotOffsetByDObj(void *q, struct Sub15C *dobj);
void SetRootMatrixRotOffsetByDObj(struct Sub15C *dobj, void *q);
void GetRootVelocity(float *vel, struct GObj *obj);
void GetInitialInverseMatrixByDObj(char *mat, char *mdl);
void GetInitialInverseMatrix(char *mat, struct GObj *gobj);
void MakeCharGObjList(void);

int GetCylinderCollision(struct GObj *self, struct GObj *target, float r, float h, float s,
                         int ctrl);

void GetRootMatrixByDObj(float *m, struct Sub15C *src);
void GetRootMatrixTransOffsetByDObj(float *dst, char *src);

#endif /* GEOMETRYMANAGER_H */
