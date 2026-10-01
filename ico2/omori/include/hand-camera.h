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
void SetLimitHandCameraCorrect(float a0, float a1);

void HandCameraCorrect(void *a0, void *a1, int a2, float f12, float f13, float f14);

#endif /* HAND_CAMERA_H */
