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

#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
void HandCameraCorrect(void *eye, void *at, float stickX, float stickZ, float rate);
#else
void HandCameraCorrect(void *eye, void *at, int mode, float stickX, float stickZ, float rate);
#endif

#endif /* HAND_CAMERA_H */
