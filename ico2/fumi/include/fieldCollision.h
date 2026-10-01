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

/* The object pointer pair a clip resets its wall and floor sources to, copied
   as one unaligned 8-byte block. */
typedef struct { /* field names derived */
    unsigned int lo;
    unsigned char m[3];
    unsigned char hi;
} FcBlk8; /* derived name */

extern FcBlk8 InitialObjPointer;
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
} FcWallEnt; /* derived name */

/* fieldCollision.c's `inline` functions (all but the sixteen it compiles in
 * place), in the order of their definitions' out-of-line copies at the end of
 * the object (first-declaration order). */
void ClipWallDebug(void *a0);
inline void ClipWall(void *a0);
void ClipWallR(void *a0);
void ClipWallWaveForce(void *a0);
void ClipWallFuchiHangWalkStop(void *a0);
void ClipWallField(void *a0);
void ClipWallEField(void *a0);
void ClipWallBoxStop(void *a0);
void ClipWallAdjustPos(void *a0);
void ClipWallE(void *a0);
void ClipWallCheckCB(void *a0, int a1);
void ClipWallFieldCheckCB(void *a0, int a1);
void ClipFloor(void *a0);
void ClipFloorE(void *a0);
void ClipFloorR(void *a0);
void ClipFloorIH(void *a0);
void ClipFloorCheckCB(void *a0, int a1);
void ClipCollision(int *self);
int ChangeFieldCollisionDebugMode(int a0);
void LoadCollision(int *self, int a1);
void DrawCollision(int a0);
int ClipPlane(int a0);
void GetOrientOfWall(void *a0, void *a1, int *a2);
void SetSimplePlane(float *self, float a, float b, float c, float d);
int GetWallAttribute(struct ClipWork *w);
int GetFloorAttribute(struct ClipWork *w);
int CompareAttribute(unsigned int a, unsigned int b);
void GetWallGlobalInfo(char *pts, void *nrm, char *w, void *m);
inline float GetDistanceFromPlane(void *a0, void *a1);
float GetYDistanceFromPlane(float *a0, float *a1);
float GetYProjectionOfPlane(float *a0, float *a1);
void ResetCollisionPC(void);
int PositionOfExit(struct GObj *a0, int a1);
void GetGlobalWallPlane(float *plane, int *r);
/* compiled in place */
void ClipFloorByGObj(char *work, char *gobj);
void DrawCollisionRay(char *ray);
void DrawGObjFloorCollision(char *gobj, int col);
void DrawGObjWallCollision(char *gobj, int col);
void GetReflectionElement(char *a0, float arg0, float arg1);
void MakeExitAttributeIndex(void);
void _Clip(char *a0, int a1);
int clip_floor_1(void *a0, int a1, int a2);
int clip_wall_1(void *a0, FcWallEnt *a1, int a2, int a3);
void MakeCollisionDependGObjList(void);

#endif /* FIELDCOLLISION_H */
