/*
 * ico2/omori/include/camera-editor.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what camera-editor.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef CAMERA_EDITOR_H
#define CAMERA_EDITOR_H

extern int CameraEdit_BOX(int a0);
extern int CameraEdit_BOX_NUMBER(void);
extern int CameraEdit_PIN(int a0, int a1);
extern int CameraEdit_PIN_NUMBER_ALL(int *a0, int a1);
extern int CameraEdit_add_pin(int box, char *src);
extern void CameraEdit_reflect_pin(int a0, int a1);
extern void CameraEdit_reset_pin(int a0, int a1);
extern void DispCameraGroup(int box, unsigned char sel);
extern void EnterMenu(void *a0, int a1, void *a2);
extern void InitCameraEditor(void);
extern void debug_Arrow(void);
extern void debug_Marker(int *buf, int a1, int a2, int a3, float f12, float f13);
extern void debug_NMarker(int *self, int a1, int a2, int a3, float t);
extern void dispCameraGroupType2(int box, unsigned char sel);
extern void dispCameraPinType2(int box, int from, int to, int type);
extern void menuGroupEdit(char *m);
extern void menuGroupSelect(char *m);
extern void menuPinEdit(char *m);
extern void menuPinSelect(char *m);
extern void saveEditedDataBinary(int no, int a1, int a2);
extern void test_camedit(void);
extern void wakeup_cameraedit(void);

#endif /* CAMERA_EDITOR_H */
