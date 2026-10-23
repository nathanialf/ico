/*
 * ico2/omori/include/hand-camera.h
 *
 * The declarations of what hand-camera.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef HAND_CAMERA_H
#define HAND_CAMERA_H

void ClearHandCameraCorrect(void);
void InitHandCameraCorrect(void);
void SetLimitHandCameraCorrect(float limitP, float limitV);

/* five arguments: the body (0x1926C0) reads a0, a1, f12, f13, f14 and sets a2 itself */
void HandCameraCorrect(void *eye, void *at, float stickX, float stickZ, float rate);

#endif /* HAND_CAMERA_H */
