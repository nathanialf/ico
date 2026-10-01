/*
 * ico2/omori/include/camera-editor.h
 *
 * The declarations of what camera-editor.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef CAMERA_EDITOR_H
#define CAMERA_EDITOR_H

/* a camera-set group record as the editor converts it: its item range and
   the address of its item records */
typedef struct S4C { /* field names derived */
    int pad0[14];
    int first;    /* 0x38, the group's first item record */
    int end;      /* 0x3C, one past its last item record */
    int pad40[2];
    int items;    /* 0x48, the address of the item records, held as a word */
} S4C;

/* a camera-set item record, 0x5C bytes, copied whole */
typedef struct {
    int w[23];
} S5C;

/* the camera box (group) record: the name, centre and half-size at 0x20 and
 * 0x2C, the pin range at 0x38 and the kind word at 0x44; the 0x4C stride is
 * camera-editor.c's */
typedef struct {
    char name[0x20];
    float cx, cy, cz; /* 0x20 */
    float sx, sy, sz; /* 0x2C */
    int pinFirst;     /* 0x38 */
    int pinLast;      /* 0x3C */
    char pad40[0x44 - 0x40];
    int kind; /* 0x44 */
    char pad48[0x4C - 0x48];
} BoxRec;

/* the camera pin record the pin editor edits in place: the two vec3s the
 * editor's rows step, the type word at 0x24, the marker size at 0x28, and
 * the hand-camera rate at 0x48; the other words are named by offset, the
 * values the pin default gives them */
typedef struct {
    float pos[3];             /* 0x00 */
    float look[3];            /* 0x0C */
    float f18;                /* 0x18 */
    int w1C[2];               /* 0x1C */
    int type;                 /* 0x24 */
    float size;               /* 0x28 */
    int w2C[2];               /* 0x2C */
    int w34;                  /* 0x34 */
    float f38, f3C, f40, f44; /* 0x38 */
    float handCameraRate;     /* 0x48 */
    float f4C;                /* 0x4C */
    float f50, f54, f58;      /* 0x50 */
} PinRec;

extern PinRec cameraPinDefault;
extern BoxRec cameraGroupDefault;
extern int curmenu;
extern int print_y;
extern unsigned char exit_f;
/* A menu of the camera editor: its thread record, then the menu that opened
   it, which it wakes and hands back to on exit, and the menu's argument. */
typedef struct MenuThread { /* field names derived */
    char thread[0x70];
    char *parent; /* 0x70 */
    int arg;      /* 0x74 */
} MenuThread;

/* the functions camera-editor.c defines `inline` */
void debug_NMarker(int *self, int a1, int a2, int a3, float t);
void debug_Marker(int *buf, int a1, int a2, int a3, float f12, float f13);
void debug_Arrow(float len, void *from, void *to, int r, int g, int b);
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
void menu_2(MenuThread *m);
void group_select(MenuThread *m);
/* compiled in place */
int CameraEdit_add_pin(int box, char *src);
void DispCameraGroup(int box, unsigned char sel);
void EnterMenu(void *a0, int a1, void *a2);
void dispCameraGroupType2(int box, unsigned char sel);
void dispCameraPinType2(int box, int from, int to, int type);
void menuGroupEdit(MenuThread *m);
void menuGroupSelect(MenuThread *m);
void menuPinEdit(MenuThread *m);
void menuPinSelect(MenuThread *m);
void saveEditedDataBinary(int no, int a1, int a2);
void test_camedit(void);
void wakeup_cameraedit(void);

/* a quadword read as four floats or as two doublewords */
typedef union Mat4 {
    float f[4];
    long long q[2];
} Mat4;

int CameraEdit_add_box(S4C *src);

#endif /* CAMERA_EDITOR_H */
