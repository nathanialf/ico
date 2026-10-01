/*
 * ico2/sugipon/include/windField.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what windField.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
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
