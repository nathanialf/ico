/*
 * ico2/seki/include/BgAnimation.h
 *
 * The declarations of what BgAnimation.c defines, for the files that use
 * them.  The file name is derived.
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
/* unprototyped, as bga_SetFrame: stage_SetAnimation passes a fourth word
   that the three-parameter definition does not read */
void bga_SetCamFrame();
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
