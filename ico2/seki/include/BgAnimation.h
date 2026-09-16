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

extern void bga_CalcAnimation(char *p, int a1, int a2);
extern void bga_CalcSdfCamera(char *p, int a1);
extern int bga_CheckAnimationFinish(char *p);
extern int bga_CheckAnimationFrame(char *p, int frame, int reset);
extern int bga_CheckAnimationFrameIn(char *p, int in, int out);
extern int bga_CheckSdfCameraFinish(char *p);
extern int bga_CheckSdfCameraFrame(char *p, int frame, int reset);
extern int bga_CheckSdfCameraFrameIn(char *p, int in, int out);
extern void bga_DispLightning(void);
extern int bga_InitData(char *data);
extern void bga_ResetAnimation(void);
extern void bga_SetCamFrame(char *p, int frame, int mode);
extern void bga_SetCameraForceOff(void);
extern void bga_SetFrame();
extern void bga_SetUniqAnimationFlag(int val);

#endif /* BGANIMATION_H */
