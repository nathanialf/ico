/*
 * ico2/sugipon/include/lineManager.h
 *
 * The declarations of what lineManager.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef LINEMANAGER_H
#define LINEMANAGER_H

void Draw2DLineSeg_Loop(int *from, int *to, int *color);
void Draw2DLineSeg_Start(void);
void DrawLine(void *from, void *to, void *color, int z);
void DrawLineG(void *from, void *fromColor, void *to, void *toColor, int z);
int _getLine(float *o1, float *o2, float *from, float *to);
void Draw2DLine(int *from, int *to, int *color, int z);
void Draw2DLineG(int *from, int *fromColor, int *to, int *toColor, int z);

#endif /* LINEMANAGER_H */
