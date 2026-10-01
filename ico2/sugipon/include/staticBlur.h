/*
 * ico2/sugipon/include/staticBlur.h
 *
 * The declarations of what staticBlur.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef STATICBLUR_H
#define STATICBLUR_H

void SetAuraInspireParam(float a0);
void SetMotionBlur(int val);
void SetStaticBlur(int x);
void MotionBlur(void);
void FullScreenEffectBefore(void);
void FullScreenEffectAfter(void);
void makeFullScreenFlareBefore(int mode);
void makeFullScreenFlareAfter(int mode);
void depthField(float depth, float alpha, float rate);
void GetSunWorldPos(int a0);
int InitStaticBlur(void);
void StaticBlur(void);
void StaticBlurDL(void);
void SetDepthFadeParam(float start, float width, int level);
void InitializeStaticBlur(void);
void _initStaticBlur(void);
void SetAuraEffect(void);

#endif /* STATICBLUR_H */
