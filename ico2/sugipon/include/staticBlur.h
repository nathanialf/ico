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
void blur(int n, void *col);
void MotionBlur(void);
void FullScreenEffectBefore(void);
void FullScreenEffectAfter(void);

#endif /* STATICBLUR_H */
