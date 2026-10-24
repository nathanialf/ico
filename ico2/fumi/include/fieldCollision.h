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
#ifdef VERSION_JUN26
void ClipCollision(ClipWork *self);
/* the wall clip ClipWall dispatches through (__ClipWall) */
extern void (*clipWallFunc)(ClipWork *work, int mode); /* derived name */
/* the floor clip ClipFloor dispatches through (__ClipFloor) */
extern void (*clipFloorFunc)(ClipWork *work, int mode); /* derived name */

/* this build has no ClipWall, ClipFloor or ClipWallField function: every
   caller loads the pointer and passes the mode itself (act-game.c's
   ACTCheckViewCl: $gp clipWallFunc with 1, clipFloorFunc with 12) */
#define ClipWall(work) clipWallFunc((work), 1)
#define ClipFloor(work) clipFloorFunc((work), 12)
/* mode 3: the field walls (act-game.c's ACTCheckCollis_WAY) */
#define ClipWallField(work) clipWallFunc((work), 3)
/* mode 10: the walls that stop a pushed box (box.c's execNormalMove) */
#define ClipWallBoxStop(work) clipWallFunc((work), 10)
/* mode 4 (box.c's avoidCharGObj) */
#define ClipWallE(work) clipWallFunc((work), 4)
/* mode 2 (motionManager.c's checkWallState and checkCliffState) */
#define ClipWallR(work) clipWallFunc((work), 2)
/* mode 5: the field walls of ClipWallE (motionManager.c's _wallHitReaction) */
#define ClipWallEField(work) clipWallFunc((work), 5)
/* mode 6: the wave force (motionManager.c's rootUpdateXZ) */
#define ClipWallWaveForce(work) clipWallFunc((work), 6)
/* mode 7: the edge walls that stop a hang walk (motionManager.c's checkSideWall) */
#define ClipWallFuchiHangWalkStop(work) clipWallFunc((work), 7)
/* mode 11 (motionManager.c's avoidSideAdjustWall) */
#define ClipWallAdjustPos(work) clipWallFunc((work), 11)
/* mode 13 (motionManager.c's getFieldCollision) */
#define ClipFloorE(work) clipFloorFunc((work), 13)
/* mode 15 (motionManager.c's checkCliffState) */
#define ClipFloorIH(work) clipFloorFunc((work), 15)
/* mode 14: no ClipFloorR function either (way_sys.c's create_box_bridge:
   $gp clipFloorFunc with 14) */
#define ClipFloorR(work) clipFloorFunc((work), 14)

int ChangeFieldCollisionDebugMode(int drawRay);
void SetCollisionFilter(int (*filter)(void *obj)); /* derived name */
#else
void ClipWallDebug(ClipWork *work);
inline void ClipWall(ClipWork *work);
void ClipWallR(ClipWork *work);
void ClipWallWaveForce(ClipWork *work);
void ClipWallFuchiHangWalkStop(ClipWork *work);
void ClipWallField(ClipWork *work);
void ClipWallEField(ClipWork *work);
void ClipWallBoxStop(ClipWork *work);
void ClipWallAdjustPos(ClipWork *work);
void ClipWallE(ClipWork *work);
void ClipWallCheckCB(ClipWork *work, int filter);
void ClipWallFieldCheckCB(ClipWork *work, int filter);
void ClipFloor(ClipWork *work);
void ClipFloorE(ClipWork *work);
void ClipFloorR(ClipWork *work);
void ClipFloorIH(ClipWork *work);
void ClipFloorCheckCB(ClipWork *work, int filter);
void ClipCollision(ClipWork *self);
int ChangeFieldCollisionDebugMode(int drawRay);
#endif

void LoadCollision(void **self, char *fname);
void DrawCollision(int mode);
int ClipPlane(int work);
void GetOrientOfWall(void *out, void *wallEnt, ObjNode *src);
void SetSimplePlane(float *self, float a, float b, float c, float d);
int GetWallAttribute(ClipWork *w);
int GetFloorAttribute(ClipWork *w);
int CompareAttribute(unsigned int a, unsigned int b);
void GetWallGlobalInfo(void *pts, void *nrm, char *w, void *m);
inline float GetDistanceFromPlane(void *plane, void *pos);
float GetYDistanceFromPlane(float *plane, float *pos);
float GetYProjectionOfPlane(float *plane, float *pos);
void ResetCollisionPC(void);
int PositionOfExit(float *pos, int attr);
void GetGlobalWallPlane(float *plane, WallCfg *wall);

/* compiled in place */
#ifndef VERSION_JUN26
void ClipFloorByGObj(ClipWork *work, struct GObj *gobj);
#endif

void DrawCollisionRay(ClipWork *ray);
void DrawGObjFloorCollision(struct GObj *gobj, int col);
void DrawGObjWallCollision(struct GObj *gobj, int col);
void GetReflectionElement(ClipWork *work, float arg0, float arg1);
void MakeExitAttributeIndex(void);
void MakeCollisionDependGObjList(void);

#endif /* FIELDCOLLISION_H */
