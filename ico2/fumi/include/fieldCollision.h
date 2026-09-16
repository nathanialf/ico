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

extern int ChangeFieldCollisionDebugMode(int a0);
extern void ClipCollision(int *self);
extern int ClipFloor(void *a0);
extern void ClipFloorByGObj(void *work, int gobj);
extern int ClipFloorE(void *a0);
extern int ClipFloorR(void *a0);
extern int ClipWall(void *a0);
extern int ClipWallBoxStop(void *a0);
extern int ClipWallField(void *a0);
extern int ClipWallFuchiHangWalkStop(void *a0);
extern int ClipWallWaveForce(void *a0);
extern int CompareAttribute(unsigned int a, unsigned int b);
extern void DrawCollision(int a0);
extern void DrawCollisionRay(char *ray);
extern void DrawGObjFloorCollision(char *gobj, int col);
extern void DrawGObjWallCollision(char *gobj, int col);
extern float GetDistanceFromPlane(void *a0, void *a1);
extern int GetFloorAttribute(int a0);
extern void GetGlobalWallPlane(float *plane, int *r);
extern void GetOrientOfWall(void *a0, void *a1, int *a2);
extern void GetReflectionElement(char *a0, float arg0, float arg1);
extern int GetWallAttribute(int a0);
extern void GetWallGlobalInfo(char *pts, void *nrm, char *w, void *m);
extern float GetYDistanceFromPlane(float *a0, float *a1);
extern float GetYProjectionOfPlane(float *a0, float *a1);
extern void MakeExitAttributeIndex(void);
extern int PositionOfExit(int a0, int a1);
extern void SetSimplePlane(float *self, float a, float b, float c, float d);
extern void _Clip(char *a0, int a1);
extern void __ClipFloorWithDrawRay(char *w, int a1);
extern void __ClipWallWithDrawRay(char *w, int a1);
extern int clip_floor_1(void *a0, int a1, int a2);
extern int clip_wall_1(void *a0, int a1, int a2, int a3);

#endif /* FIELDCOLLISION_H */
