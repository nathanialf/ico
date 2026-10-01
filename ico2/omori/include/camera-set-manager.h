/*
 * ico2/omori/include/camera-set-manager.h
 *
 * The declarations of what camera-set-manager.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef CAMERA_SET_MANAGER_H
#define CAMERA_SET_MANAGER_H

/* the current stage's camera set, its group count, and its group and pin
   tables */
extern void *TopCameraSetDataOfCurrentStage;
extern int NumOfGroup;
extern void *TopOfCameraGroup;
extern void *TopOfCameraPin;

void InitCameraSetManager(void);

#endif /* CAMERA_SET_MANAGER_H */
