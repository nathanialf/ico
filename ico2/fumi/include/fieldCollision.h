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

int ChangeFieldCollisionDebugMode(int a0);
void ClipCollision(int *self);
int ClipFloor(void *a0);
void ClipFloorByGObj(void *work, int gobj);
int ClipFloorE(void *a0);
int ClipFloorR(void *a0);
int ClipWall(void *a0);
int ClipWallBoxStop(void *a0);
int ClipWallField(void *a0);
int ClipWallFuchiHangWalkStop(void *a0);
int ClipWallWaveForce(void *a0);
int CompareAttribute(unsigned int a, unsigned int b);
void DrawCollision(int a0);
void DrawCollisionRay(char *ray);
void DrawGObjFloorCollision(char *gobj, int col);
void DrawGObjWallCollision(char *gobj, int col);
float GetDistanceFromPlane(void *a0, void *a1);
int GetFloorAttribute(int a0);
void GetGlobalWallPlane(float *plane, int *r);
void GetOrientOfWall(void *a0, void *a1, int *a2);
void GetReflectionElement(char *a0, float arg0, float arg1);
int GetWallAttribute(int a0);
void GetWallGlobalInfo(char *pts, void *nrm, char *w, void *m);
float GetYDistanceFromPlane(float *a0, float *a1);
float GetYProjectionOfPlane(float *a0, float *a1);
void MakeExitAttributeIndex(void);
int PositionOfExit(int a0, int a1);
void SetSimplePlane(float *self, float a, float b, float c, float d);
void _Clip(char *a0, int a1);
void __ClipFloorWithDrawRay(char *w, int a1);
void __ClipWallWithDrawRay(char *w, int a1);
int clip_floor_1(void *a0, int a1, int a2);
int clip_wall_1(void *a0, int a1, int a2, int a3);

#endif /* FIELDCOLLISION_H */
