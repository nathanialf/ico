/*
 * ico2/sugipon/include/windField.h
 *
 * The declarations of what windField.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef WINDFIELD_H
#define WINDFIELD_H

void ExecWindField(float f);
float *GetWindVector(float *power, float *pos);
void InitWindField(int mode, float str, void *center, void *dir);
void drawSenpuukiHaneUnit(float scale);
void drawSenpuuki(float scale);
void StopWindField(void);
void drawLines(char *a0);
void drawSenpuukiHane(void);
void drawSenpuukiUnit(void);
void drawSenpuukiBase(void);

#endif /* WINDFIELD_H */
