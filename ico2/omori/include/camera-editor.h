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

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: one record, previously repeated character for character in 2 TUs. */
typedef struct {
    int w[19];
} S4C;

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: one record, previously repeated character for character in 2 TUs. */
typedef struct {
    int w[23];
} S5C;

/* The functions camera-editor.c defines `inline`, in the order the ROM emits
 * their out-of-line copies: gcc 2.9 writes deferred functions at the end of
 * the file in the order of their first declaration, so this block is that
 * order. */
void debug_NMarker(int *self, int a1, int a2, int a3, float t);
void debug_Marker(int *buf, int a1, int a2, int a3, float f12, float f13);
void debug_Arrow(void);
void InitCameraEditor(void);
int debug_CameraEditor(void);
void CameraEdit_reset_box(int a0);
void CameraEdit_reset_pin(int a0, int a1);
void CameraEdit_reflect_box(int a0);
void CameraEdit_reflect_pin(int a0, int a1);
int CameraEdit_BOX_NUMBER(void);
int CameraEdit_PIN_NUMBER(int a0);
int CameraEdit_PIN_NUMBER_ALL(int *a0, int a1);
int CameraEdit_BOX(int a0);
int CameraEdit_PIN(int a0, int a1);
void CameraEdit_DispPin(int box, int pin);
void ConvertCameraSetBuffer(int n, S4C *item, char *groups);
void StickToTrans(int a0, int a1, int a2, int a3, float *out, int a5);
void menu_2(char *m);
void group_select(char *m);

/* compiled in place */
int CameraEdit_add_pin(int box, char *src);
void DispCameraGroup(int box, unsigned char sel);
void EnterMenu(void *a0, int a1, void *a2);
void dispCameraGroupType2(int box, unsigned char sel);
void dispCameraPinType2(int box, int from, int to, int type);
void menuGroupEdit(char *m);
void menuGroupSelect(char *m);
void menuPinEdit(char *m);
void menuPinSelect(char *m);
void saveEditedDataBinary(int no, int a1, int a2);
void test_camedit(void);
void wakeup_cameraedit(void);

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: one record, previously repeated character for character in 2 TUs. */
typedef union Mat4 {
    float f[4];
    long long q[2];
} Mat4;


#endif /* CAMERA_EDITOR_H */
