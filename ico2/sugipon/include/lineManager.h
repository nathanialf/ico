/*
 * ico2/sugipon/include/lineManager.h
 *
 * The declarations of what lineManager.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef LINEMANAGER_H
#define LINEMANAGER_H

void Draw2DLineSeg_Loop(int *a0, int *a1, int *a2);
void Draw2DLineSeg_Start(void);
void DrawLine(void *p1, void *p2, void *color, int z);
void DrawLineG(void *p0, void *c0, void *p1, void *c1, int z);
int _getLine(float *o1, float *o2, float *p1, float *p2);
void Draw2DLine(int *p1, int *p2, int *color, int z);

#endif /* LINEMANAGER_H */
