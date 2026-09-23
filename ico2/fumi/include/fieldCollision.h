/*
 * ico2/fumi/include/fieldCollision.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what fieldCollision.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef FIELDCOLLISION_H
#define FIELDCOLLISION_H

/* RECONSTRUCTION: one wall of a collision set, 0x50 bytes (the table
 * stride). The corners are what GetWallGlobalInfo transforms, the height
 * and normal are what clip_wall_1 reads, the angle is GetWallGlobalInfo's
 * 0x44 short and the attribute is the word the _clipW filters test. */
typedef struct FcWallEnt {
    float pt[4][4]; /* 0x00 corners */
    float height;   /* 0x40 */
    short angle;    /* 0x44 */
    short _46;
    int attr;       /* 0x48 */
    float *normal;  /* 0x4C */
} FcWallEnt;

/* The functions fieldCollision.c defines `inline` (all but the sixteen it
 * compiles in place), in the order the ROM emits their out-of-line copies:
 * gcc 2.9 writes deferred functions at the end of the file in the order of
 * their first declaration, so this block is that order. */
int ClipWallDebug(void *a0);
int ClipWall(void *a0);
int ClipWallR(void *a0);
int ClipWallWaveForce(void *a0);
int ClipWallFuchiHangWalkStop(void *a0);
int ClipWallField(void *a0);
int ClipWallEField(void *a0);
int ClipWallBoxStop(void *a0);
int ClipWallAdjustPos(void *a0);
void ClipWallE(void *a0);
void ClipWallCheckCB(void *a0, int a1);
void ClipWallFieldCheckCB(void *a0, int a1);
int ClipFloor(void *a0);
int ClipFloorE(void *a0);
int ClipFloorR(void *a0);
int ClipFloorIH(void *a0);
void ClipFloorCheckCB(void *a0, int a1);
void ClipCollision(int *self);
int ChangeFieldCollisionDebugMode(int a0);
void LoadCollision(int *self, int a1);
void DrawCollision(int a0);
int ClipPlane(int a0);
void GetOrientOfWall(void *a0, void *a1, int *a2);
void SetSimplePlane(float *self, float a, float b, float c, float d);
int GetWallAttribute(int a0);
int GetFloorAttribute(int a0);
int CompareAttribute(unsigned int a, unsigned int b);
void GetWallGlobalInfo(char *pts, void *nrm, char *w, void *m);
float GetDistanceFromPlane(void *a0, void *a1);
float GetYDistanceFromPlane(float *a0, float *a1);
float GetYProjectionOfPlane(float *a0, float *a1);
void ResetCollisionPC(void);
int PositionOfExit(int a0, int a1);
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

#endif /* FIELDCOLLISION_H */
