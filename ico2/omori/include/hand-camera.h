/*
 * ico2/omori/include/hand-camera.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what hand-camera.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef HAND_CAMERA_H
#define HAND_CAMERA_H

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order hand-camera.c's inline tail has. */
void ClearHandCameraCorrect(void);
void InitHandCameraCorrect(void);
void SetLimitHandCameraCorrect(float a0, float a1);

void HandCameraCorrect(void *a0, void *a1, int a2, float f12, float f13, float f14);
void HandyCamera_TargetMoveType(void *a0, void *a1);
void RotateAccordingToStick_PatternThree(float *a, float *b, float x, float y);
void SetCurrentInfo(void *a0, void *a1);

#endif /* HAND_CAMERA_H */
