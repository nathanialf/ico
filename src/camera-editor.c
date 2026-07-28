#include "common.h"

typedef struct { char _0[4]; float f4; char _8[8]; float f10; } EdS;




extern char D_006326D8;
extern int D_006326D0;
extern int ACTGameView_Init();
extern int D_0028A898[];
void EnterMenu(void) {
    D_0028A898[0] = 1;
}

void saveEditedDataBinary(void) {
    D_0028A898[0] = 0;
}

float saveEditedData(EdS *a0, float arg) {
    float r;
    a0->f4 += a0->f10 * arg;
    if (a0->f4 < 0.0f) {
        r = 0.0f;
    } else if (a0->f4 > 10.0f) {
        r = 10.0f;
    } else {
        r = a0->f4;
    }
    a0->f4 = r;
    return r;
}

void gif_test(int *a0, EdS *a1, float f12) {
    int cond;
    if (*(unsigned char *)((char *)a1 + 0x19) != 0) {
        cond = 1;
    } else {
        cond = ACTGameView_Init(*a0, *(int *)a1) != 0;
    }
    if (cond) {
        float r;
        a1->f4 = f12;
        if (a1->f4 < 0.0f) {
            r = 0.0f;
        } else if (a1->f4 > 20.0f) {
            r = 20.0f;
        } else {
            r = a1->f4;
        }
        a1->f4 = r;
    }
}

int DebugDispBox(int *a0, int *a1)
{
    if (((unsigned char *)a1)[0x19] != 0) {
        return 1;
    }
    return ACTGameView_Init(*a0, a1[0]) != 0;
}

extern char D_0055A5C0[];
extern int D_00632028;
extern void *func_0013A0F8(int heap, int size, const char *file, int line);
extern void iosSemaCreate(int a0);
extern void iosThreadJoin(void *a0);
extern void iosThreadWakeup(void *a0, int a1, void *a2, void *a3, int a4, int a5, int a6);

void DispCameraGroup(void *a0, int a1, int a2) {
    void *r = func_0013A0F8(D_00632028, 0x78, D_0055A5C0, 0xD9);
    iosThreadWakeup(r, 1, a0, r, D_00632028, 0x1000, 0x17);
    *(int *)((char *)r + 0x74) = a1;
    *(int *)((char *)r + 0x70) = a2;
    iosThreadJoin(r);
    D_006326D0 = (int)r;
    if (a2 != 0) {
        iosSemaCreate(a2);
    }
}

INCLUDE_ASM("asm/nonmatchings/src/camera-editor", drawXZArrow);

INCLUDE_ASM("asm/nonmatchings/src/camera-editor", DispAxisArrow);

extern void gif_SpriteOrg(int code, long data);

void dispCameraPinType2(int *a0, int *a1, int *a2, unsigned char *a3) {
    gif_SpriteOrg(0, 3);
    gif_SpriteOrg(1, (long)a3[0] | ((long)a3[1] << 8) | ((long)a3[2] << 16) | ((long)a3[3] << 24));
    gif_SpriteOrg(4, (long)a0[0] | ((long)a0[1] << 16) | ((long)a0[2] << 32));
    gif_SpriteOrg(4, (long)a1[0] | ((long)a1[1] << 16) | ((long)a1[2] << 32));
    gif_SpriteOrg(4, (long)a2[0] | ((long)a2[1] << 16) | ((long)a2[2] << 32));
}

INCLUDE_ASM("asm/nonmatchings/src/camera-editor", CameraEdit_DispPinType2);

INCLUDE_ASM("asm/nonmatchings/src/camera-editor", dispCameraGroupType2);

INCLUDE_ASM("asm/nonmatchings/src/camera-editor", dispBox);

INCLUDE_ASM("asm/nonmatchings/src/camera-editor", CameraEdit_DispBoxType2_Plane);

INCLUDE_ASM("asm/nonmatchings/src/camera-editor", CameraEdit_DispBoxType2);

extern void CameraEdit_DispBoxType2(int a0, int a1, int a2, int a3);

void menuGroupSelect(int a0, int a1, int a2) {
    CameraEdit_DispBoxType2(a0, a1, a1 + 1, a2);
}

INCLUDE_ASM("asm/nonmatchings/src/camera-editor", menuGroupEdit);

INCLUDE_ASM("asm/nonmatchings/src/camera-editor", menuPinSelect);

INCLUDE_ASM("asm/nonmatchings/src/camera-editor", menuPinEdit);

INCLUDE_ASM("asm/nonmatchings/src/camera-editor", wakeup_cameraedit);

INCLUDE_ASM("asm/nonmatchings/src/camera-editor", test_camedit);

INCLUDE_ASM("asm/nonmatchings/src/camera-editor", func_00186978);

INCLUDE_ASM("asm/nonmatchings/src/camera-editor", _CameraEdit_del_box);

INCLUDE_ASM("asm/nonmatchings/src/camera-editor", _CameraEdit_del_pin);

INCLUDE_ASM("asm/nonmatchings/src/camera-editor", CameraEdit_add_box);

INCLUDE_ASM("asm/nonmatchings/src/camera-editor", CameraEdit_add_pin);

INCLUDE_ASM("asm/nonmatchings/src/camera-editor", CameraEdit_del_box);

extern int *D_00632610;
extern int *D_00632614;
extern void _CameraEdit_del_pin(int *a0, void *a1);

void CameraEdit_del_pin(void *a0) {
    _CameraEdit_del_pin(D_00632610, a0);
    _CameraEdit_del_pin(D_00632614, a0);
}

extern void CameraEdit_add_box(int a0, int a1, int a2);

void CameraEdit_DispBox(int a0, int a1)
{
    CameraEdit_add_box(D_00632610, a0, a1);
    CameraEdit_add_box(D_00632614, a0, a1);
}

INCLUDE_ASM("asm/nonmatchings/src/camera-editor", CameraEdit_Reflect);

extern void func_001897A8(int a0, int a1);

void CameraEdit_Save(void) {
    int *p = D_00632610;
    func_001897A8(p[1], p[0]);
}

extern void drawXZArrow(int a0, int a1, int a2);

void debug_NMarker(int a0) {
    int *p = D_00632610;
    drawXZArrow(a0, p[1], p[0]);
}

extern void debug_ArrowM(int *buf, int a1, int a2, int a3, float f12, float f13) __asm__("debug_Arrow");
extern void func_00243B18(int *buf, int *p, float t);

void debug_Marker(int *self, int a1, int a2, int a3, float t)
{
    int buf[4];
    func_00243B18(buf, self, -1.0f);
    debug_ArrowM(buf, a1, a2, a3, t, 0.0f);
}

void debug_Arrow(void) {}

void InitCameraEditor(void) {}

void debug_CameraEditor(void) {
    D_006326D0 = 0;
    D_006326D8 = 0;
}

