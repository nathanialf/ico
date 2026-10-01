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
float *dummyGetWindVector(float *power, float *pos);
float *getParallelWindVector(float *power, float *pos);

#endif /* WINDFIELD_H */
