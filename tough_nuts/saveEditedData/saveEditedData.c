#include "common.h"

extern int D_00286A98[];

void EnterMenu(void) {
    D_00286A98[0] = 1;
}


void saveEditedDataBinary(void) {
    D_00286A98[0] = 0;
}

/* m2c scaffold from asm/aug6/nonmatchings/omori/src/camera-editor/saveEditedData.s (target mipsel-gcc-c, context-free).
 * NOT a match — reshape into a goto-CFG-mirror + recover intent (see decomp-match skill). */
void saveEditedData(void *a0, float arg0) {
    float *p = (float *)a0;
    float prod = p[4] * arg0;
    float v = p[1] + prod;
    p[1] = v;
    if (v < 0.0f) {
        p[1] = 0.0f;
        return;
    }
    prod = 10.0f;
    if (!(v > 10.0f)) {
        prod = v;
    }
    p[1] = prod;
}


INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-editor", gif_test);

extern int ACTGameView_Init(int a0, int a1);

int DebugDispBox(void *a0, char *a1) {
    if (*(unsigned char *)(a1 + 0x19) != 0) {
        return 1;
    }
    return ACTGameView_Init(*(int *)a0, *(int *)a1) != 0;
}

extern void *iosFree(int heap, int size, const char *file, int line);
extern void iosThreadWakeup(void *a0, int a1, void *a2, void *a3, int a4, int a5, int a6);
extern void iosThreadJoin(void *a0);
extern void iosSemaCreate(int a0);
extern int D_0062A328;
extern int D_0062A9B0;
extern char D_00554780[];

void DispCameraGroup(void *a0, int a1, int a2) {
    void *r = iosFree(D_0062A328, 0x78, D_00554780, 0xD9);
    iosThreadWakeup(r, 1, a0, r, D_0062A328, 0x1000, 0x17);
    *(int *)((char *)r + 0x74) = a1;
    *(int *)((char *)r + 0x70) = a2;
    iosThreadJoin(r);
    D_0062A9B0 = (int)r;
    if (a2 != 0) {
        iosSemaCreate(a2);
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-editor", drawXZArrow);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-editor", DispAxisArrow);

extern void gif_SpriteOrg(int code, long data);

void dispCameraPinType2(int *a0, int *a1, int *a2, unsigned char *a3) {
    gif_SpriteOrg(0, 3);
    gif_SpriteOrg(1, (long)a3[0] | ((long)a3[1] << 8) | ((long)a3[2] << 16) | ((long)a3[3] << 24));
    gif_SpriteOrg(4, (long)a0[0] | ((long)a0[1] << 16) | ((long)a0[2] << 32));
    gif_SpriteOrg(4, (long)a1[0] | ((long)a1[1] << 16) | ((long)a1[2] << 32));
    gif_SpriteOrg(4, (long)a2[0] | ((long)a2[1] << 16) | ((long)a2[2] << 32));
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-editor", CameraEdit_DispPinType2);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-editor", dispCameraGroupType2);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-editor", dispBox);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-editor", CameraEdit_DispBoxType2_Plane);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-editor", CameraEdit_DispBoxType2);

extern void CameraEdit_DispBoxType2(int a0, int a1, int a2, int a3);

void menuGroupSelect(int a0, int a1, int a2) {
    CameraEdit_DispBoxType2(a0, a1, a1 + 1, a2);
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-editor", menuGroupEdit);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-editor", menuPinSelect);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-editor", menuPinEdit);

extern void menuGroupEdit(int a0, int a1);

void wakeup_cameraedit(int a0, int a1) {
    menuGroupEdit(a0, a1 & 0xFF);
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-editor", test_camedit);

extern int test_camedit[];
extern void DispCameraGroup(void *a0, int a1, int a2);

void _CameraEdit_del_box(void) {
    DispCameraGroup(test_camedit, 0, 0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-editor", _CameraEdit_del_pin);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-editor", CameraEdit_add_box);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-editor", CameraEdit_add_pin);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-editor", CameraEdit_del_box);

extern int *D_0062A8F0;
extern int *D_0062A8F4;
extern void _CameraEdit_del_pin(int *a0, void *a1);

void CameraEdit_del_pin(void *a0) {
    _CameraEdit_del_pin(D_0062A8F0, a0);
    _CameraEdit_del_pin(D_0062A8F4, a0);
}

extern void CameraEdit_add_box(int a0, int a1, int a2);

void CameraEdit_DispBox(int a0, int a1)
{
    CameraEdit_add_box(D_0062A8F0, a0, a1);
    CameraEdit_add_box(D_0062A8F4, a0, a1);
}

extern void dispCameraGroupType2(int a0, unsigned char a1);

void CameraEdit_Reflect(int a0, unsigned char a1) {
    dispCameraGroupType2(a0, a1);
}

extern void func_00186CA8(int a0, int a1);

void CameraEdit_Save(void) {
    int *p = D_0062A8F0;
    func_00186CA8(p[1], p[0]);
}

extern void drawXZArrow(int a0, int a1, int a2);

void debug_NMarker(int a0) {
    int *p = D_0062A8F0;
    drawXZArrow(a0, p[1], p[0]);
}

extern void func_00240038(int *buf, int *p, float t);
extern void debug_Arrow();

/* parked: needs real matching. See tough_nuts/debug_Marker/notes.md */
INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-editor", debug_Marker);

void debug_Arrow() {
}

void InitCameraEditor(void) {
}

extern int D_0062A9B0;
extern unsigned char D_0062A9B8;

void debug_CameraEditor(void) {
    D_0062A9B0 = 0;
    D_0062A9B8 = 0;
}


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_00286F00;  /* stride 0x10 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_00286F04;  /* stride 0x10 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_00286F08;  /* stride 0x10 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_00286F0C;  /* stride 0x10 */

/* end struct shapes */
