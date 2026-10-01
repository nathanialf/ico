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

/* the camera box (group) record: the name, centre and half-size at 0x20 and
 * 0x2C, the pin range at 0x38 and the kind word at 0x44; the 0x4C stride is
 * camera-editor.c's */
typedef struct { /* field names derived */
    char name[0x20];
    float cx, cy, cz; /* 0x20 */
    float sx, sy, sz; /* 0x2C */
    int pinFirst;     /* 0x38 */
    int pinLast;      /* 0x3C */
    char pad40[0x44 - 0x40];
    int kind; /* 0x44 */
    char pad48[0x4C - 0x48];
} BoxRec;

/* A camera pin, one item record of a camera set (0x5C bytes, copied whole):
 * the camera position and the point it looks at, two offsets of the look-at
 * point, the on flag, the field of view, the radius inside which the pin damps
 * the other pins' weights, and the hand camera's eye and look-at rates and two
 * angle limits.  CameraMove (camera-ico2.c) blends the pins by distance; the
 * editor steps pos, look, on and fov, draws range, and writes the stage's
 * hand-camera rate into its default at 0x48, sixteen bytes past eyeRate. */
typedef struct { /* field names derived */
    float pos[3];         /* 0x00, the camera position */
    float look[3];        /* 0x0C, the point the camera looks at */
    float ofs[3];         /* 0x18, the look-at offset, turned to the target's facing */
    int on;               /* 0x24, the pin takes part in the blend */
    float fov;            /* 0x28 */
    int word2C;           /* 0x2C */
    float range;          /* 0x30 */
    int word34;           /* 0x34 */
    float eyeRate;        /* 0x38, the hand camera's eye rate */
    float atRate;         /* 0x3C, the hand camera's look-at rate */
    float limitP;         /* 0x40, the hand camera's angle limits */
    float limitV;         /* 0x44 */
    float handCameraRate; /* 0x48 */
    float float4C;        /* 0x4C */
    float ofsB[3];        /* 0x50, the look-at offset added as it is */
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
inline void debug_NMarker(float *pos, int r, int g, int b, float size);
inline void debug_Marker(float *pos, int r, int g, int b, float size, float pulse);
inline void debug_Arrow(float len, void *from, void *to, int r, int g, int b);
inline void InitCameraEditor(void);
inline int debug_CameraEditor(void);
inline void CameraEdit_reset_box(int a0);
inline void CameraEdit_reset_pin(int a0, int a1);
inline void CameraEdit_reflect_box(int a0);
inline void CameraEdit_reflect_pin(int a0, int a1);
inline int CameraEdit_BOX_NUMBER(void);
inline int CameraEdit_PIN_NUMBER(int a0);
inline int CameraEdit_PIN_NUMBER_ALL(int *a0, int a1);
inline int CameraEdit_BOX(int a0);
inline PinRec *CameraEdit_PIN(int a0, int a1);
inline void CameraEdit_DispPin(int box, int pin);
inline void ConvertCameraSetBuffer(int n, S4C *item, char *groups);
inline void StickToTrans(int a0, int a1, int a2, int a3, float *out, int a5);
inline void menu_2(MenuThread *m);
inline void group_select(MenuThread *m);
/* compiled in place */
int CameraEdit_add_pin(int box, char *src);
void dispCameraGroupType2(int box, unsigned char sel);
void menuGroupEdit(MenuThread *m);
void menuGroupSelect(MenuThread *m);
void menuPinEdit(MenuThread *m);
void menuPinSelect(MenuThread *m);
void test_camedit(void);
void wakeup_cameraedit(void);

/* a quadword read as four floats or as two doublewords */
typedef union Mat4 { /* field names derived */
    float f[4];
    long long q[2];
} Mat4;

int CameraEdit_add_box(S4C *src);

#endif /* CAMERA_EDITOR_H */
