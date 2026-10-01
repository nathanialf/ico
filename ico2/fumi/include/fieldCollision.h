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

typedef struct { /* field names derived */
    float x, y, z, w;
} FcVec4; /* derived name */

/* one floor of a collision set, 0x70 bytes (the table stride): the polygon
 * clip_floor_1 tests, its plane, and the attribute the _clipF filters,
 * ClipFloorByGObj and MakeExitAttributeIndex read (its low nibble the exit
 * slot). */
typedef struct FcFloorEnt { /* field names derived */
    FcVec4 v[4];            /* 0x00, the polygon's corners */
    float nx, ny, nz, npad; /* 0x40, the plane normal */
    float d;                /* 0x50, the plane distance */
    int nex;                /* 0x54, the corners past the first three */
    char pad58[8];
    int attr; /* 0x60 */
    char pad64[12];
} FcFloorEnt; /* derived name */

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
void ClipCollision(ClipWork *self);
int ChangeFieldCollisionDebugMode(int drawRay);
void LoadCollision(int *self, int fname);
void DrawCollision(int mode);
int ClipPlane(int work);
void GetOrientOfWall(void *out, void *wallEnt, ObjNode *src);
void SetSimplePlane(float *self, float a, float b, float c, float d);
int GetWallAttribute(ClipWork *w);
int GetFloorAttribute(ClipWork *w);
int CompareAttribute(unsigned int a, unsigned int b);
void GetWallGlobalInfo(char *pts, void *nrm, char *w, void *m);
inline float GetDistanceFromPlane(void *plane, void *pos);
float GetYDistanceFromPlane(float *plane, float *pos);
float GetYProjectionOfPlane(float *plane, float *pos);
void ResetCollisionPC(void);
int PositionOfExit(float *pos, int attr);
void GetGlobalWallPlane(float *plane, WallCfg *wall);
/* compiled in place */
void ClipFloorByGObj(char *work, struct GObj *gobj);
void DrawCollisionRay(ClipWork *ray);
void DrawGObjFloorCollision(struct GObj *gobj, int col);
void DrawGObjWallCollision(struct GObj *gobj, int col);
void GetReflectionElement(ClipWork *work, float arg0, float arg1);
void MakeExitAttributeIndex(void);
void MakeCollisionDependGObjList(void);

#endif /* FIELDCOLLISION_H */
