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

extern void *light_AddAmbientObject(int obj);
extern void light_AddLight(int a, int b, int c);
extern void light_DispVolume(void);
extern void light_DrawCursor(float *dir, int mode);
extern void light_GetColorAnalog(float *col);
extern void light_KillAllFixLight(void);
extern void light_MakeLightMatrix(char *a, int b);
extern void light_getAmbientLight(char *a, int b);
extern void light_getNearLight(char *a, int b);
extern void light_killLinkAmbient();
extern void light_killLinkLight(char *node);
extern void light_resetFlatLight(void);

#endif /* LIGHT_H */
