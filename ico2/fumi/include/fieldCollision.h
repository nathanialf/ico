/*
 * ico2/fumi/include/fieldCollision.h
 *
 * The declarations of what fieldCollision.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef FIELDCOLLISION_H
#define FIELDCOLLISION_H

#include "typedef.h"

struct GObj;

struct ClipWork;

/* The empty wall-hit record (no object, node -1, no wall) a character's
   collision filter is reset to. */
extern WallCfg InitialColInfo;
/* The empty object and node pair (no object, node -1) a clip resets its wall
   and floor sources to and a display object's parent link is cleared to. */
extern ObjNode InitialObjPointer;
extern int collision_pick;

/* one wall of a collision set, 0x50 bytes (the table
 * stride). The corners are what GetWallGlobalInfo transforms, the height
 * and normal are what clip_wall_1 reads, the angle is GetWallGlobalInfo's
 * 0x44 short and the attribute is the word the _clipW filters test. */
typedef struct FcWallEnt { /* field names derived */
    float pt[4][4];        /* 0x00 corners */
    float height;          /* 0x40 */
    short angle;           /* 0x44 */
    char pad46[2];
    int attr;      /* 0x48 */
    float *normal; /* 0x4C */
} FcWallEnt;       /* derived name */

/* fieldCollision.c's `inline` functions (all but the sixteen it compiles in
 * place), in the order of their definitions' out-of-line copies at the end of
 * the object (first-declaration order). */
void ClipWallDebug(void *work);
inline void ClipWall(void *work);
void ClipWallR(void *work);
void ClipWallWaveForce(void *work);
void ClipWallFuchiHangWalkStop(void *work);
void ClipWallField(void *work);
void ClipWallEField(void *work);
void ClipWallBoxStop(void *work);
void ClipWallAdjustPos(void *work);
void ClipWallE(void *work);
void ClipWallCheckCB(void *work, int filter);
void ClipWallFieldCheckCB(void *work, int filter);
void ClipFloor(void *work);
void ClipFloorE(void *work);
void ClipFloorR(void *work);
void ClipFloorIH(void *work);
void ClipFloorCheckCB(void *work, int filter);
void ClipCollision(int *self);
int ChangeFieldCollisionDebugMode(int drawRay);
void LoadCollision(int *self, int fname);
void DrawCollision(int mode);
int ClipPlane(int work);
void GetOrientOfWall(void *out, void *wallEnt, int *src);
void SetSimplePlane(float *self, float a, float b, float c, float d);
int GetWallAttribute(struct ClipWork *w);
int GetFloorAttribute(struct ClipWork *w);
int CompareAttribute(unsigned int a, unsigned int b);
void GetWallGlobalInfo(char *pts, void *nrm, char *w, void *m);
inline float GetDistanceFromPlane(void *plane, void *pos);
float GetYDistanceFromPlane(float *plane, float *pos);
float GetYProjectionOfPlane(float *plane, float *pos);
void ResetCollisionPC(void);
int PositionOfExit(float *pos, int attr);
void GetGlobalWallPlane(float *plane, int *r);
/* compiled in place */
void ClipFloorByGObj(char *work, char *gobj);
void DrawCollisionRay(char *ray);
void DrawGObjFloorCollision(char *gobj, int col);
void DrawGObjWallCollision(char *gobj, int col);
void GetReflectionElement(char *work, float arg0, float arg1);
void MakeExitAttributeIndex(void);
void MakeCollisionDependGObjList(void);

#endif /* FIELDCOLLISION_H */
