/*
 * ico2/seki/include/Light.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what Light.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef LIGHT_H
#define LIGHT_H

void *light_AddAmbientObject(int obj);
void light_AddLight(int a, int b, int c);
void light_DispVolume(void);
void light_DrawCursor(float *dir, int mode);
void light_GetColorAnalog(float *col);
void light_KillAllFixLight(void);
void light_MakeLightMatrix(char *a, int b);
void light_getAmbientLight(char *a, int b);
void light_getNearLight(char *a, int b);
void light_killLinkAmbient();
void light_killLinkLight(char *node);
void light_resetFlatLight(void);

#endif /* LIGHT_H */
