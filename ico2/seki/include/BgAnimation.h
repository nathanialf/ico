/*
 * ico2/seki/include/BgAnimation.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what BgAnimation.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef BGANIMATION_H
#define BGANIMATION_H

/* set when an animation's camera cut restarts the global timer; the stream
   motion player resynchronises on it and clears it */
extern int bgaStreamSync;
void bga_CalcAnimation(char *p, int a1, int a2);
void bga_CalcSdfCamera(char *p, int a1);
int bga_CheckAnimationFinish(char *p);
int bga_CheckAnimationFrame(char *p, int frame, int reset);
int bga_CheckAnimationFrameIn(char *p, int in, int out);
int bga_CheckSdfCameraFinish(char *p);
int bga_CheckSdfCameraFrame(char *p, int frame, int reset);
int bga_CheckSdfCameraFrameIn(char *p, int in, int out);
void bga_DispLightning(void);
int bga_InitData(char *data);
void bga_ResetAnimation(void);
void bga_SetCamFrame(char *p, int frame, int mode);
void bga_SetCameraForceOff(void);
void bga_SetFrame();
void bga_SetUniqAnimationFlag(int val);

struct BgaLightningDef;

void bga_addLightning(int kind, struct BgaLightningDef *a1, float *vec, int id, int t0, float f);
void bga_ResetCamera(void);
int bga_GetCameraMatrix(void *p);
void bga_InitBGA(void);
float bga_GetZoom(void);

#endif /* BGANIMATION_H */
