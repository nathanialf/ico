#include "common.h"

extern char D_0061EEC8[];
extern int D_0063A438;
extern int iosMallocDebug(int handle, int size, char *file, int line);
/* .data — carved VMA 0x4E5A90..0x4E5AA0; bytes verified against baserom/pal/baseelf.rom */
unsigned int D_004E5A90[4] = {
    0x00000000, 0x00000080, 0x000000FF, 0x00000080,
};
extern int D_0063B148;
extern void CopyVector(void *dst, void *src);
extern void *MatrixDrive_GetMatrix(void);
extern void _UnitMatrix(void *a0);
extern void gif_EndPacket(void);
extern void gif_SetAlpha(int a0, int a1, int a2);
extern void gif_SetZTest(int a0);
extern void gif_StartPacketPri(int a0);
extern void prim_DispWireSphere(void *a0, int a1, int a2, float a3);
extern void _ACTWait();
extern int actInitialize();
extern void actInitialize_ext_charcter();
typedef union { float f[4]; long long ll[2]; } AcbVec;
typedef struct {
    AcbVec pos;      /* 0x00 */
    AcbVec rot;      /* 0x10 */
    AcbVec scale;    /* 0x20 */
    int *obj;        /* 0x30 */
    int unk34[3];    /* 0x34 */
} AcbLayout;
extern AcbLayout D_004E45C0;
extern char *CreateLayoutedGObj(int id, int a1, int a2, int a3, void *a4, int a5, int a6, int a7);
/* prototypes: their order is the inline tail's emission order */
int InitAttackCheckBoundaryGeo(int unused, void *obj);
void AttackCheckBoundaryGeo(void *a0);
void AttackCheckBoundaryDL(char *obj);
void actAttackCheckBoundaryStart(int *self);
float GetAttackCheckBoundaryRadius(char *a0);
char *CreateAttackCheckBoundary(int *obj, float x, float y, float z, float r);
int GetAttackCheckBoundaryManagerStatus(char *a0);
void SetAttackCheckBoundaryAttribute(char *a0, int a1);
static inline char *createAttackCheckBoundaryGObj(AcbLayout *lay)
{
    return CreateLayoutedGObj(0x3F, 0x4B, -1, 0, lay, -1, 7, 1);
}
inline int InitAttackCheckBoundaryGeo(int unused, void *obj)
{
  int buf = iosMallocDebug(D_0063A438, 0xC, D_0061EEC8, 0x1B);
  int *p = *((int **) (((char *) obj) + 0x30));
  int new_var4;
  int *new_var2;
  int *new_var3;
  int new_var;
  new_var2 = p;
 do { new_var4 = (int) p; ; } while (0);
  *((int *) (buf + 4)) = 0;
  new_var3 = (int *) buf;
  *new_var2 = 0;
  *new_var3 = new_var4;
  *((int *) (buf + 8)) = 0;
  return buf;
}
inline void AttackCheckBoundaryGeo(void *a0) {
    int *a = *(int **)((char *)a0 + 0x15C);
    int *b = *(int **)a;
    if (b == 0) return;
    if (*(int *)((char *)b + 0x16C) == 0) {
        *(int *)((char *)a0 + 0x16C) = 0;
    }
}
inline void AttackCheckBoundaryDL(char *obj)
{
    char *m = *(char **)(*(char **)(obj + 0x15C) + 0x830);
    float r;

    if (D_0063B148 == 0) {
        return;
    }
    if (*(int *)(m + 4) != 0) {
        return;
    }
    gif_StartPacketPri(0xB);

    gif_SetZTest(1);
    gif_SetAlpha(1, 5, 0x80);
    _UnitMatrix(MatrixDrive_GetMatrix());
    CopyVector((char *)MatrixDrive_GetMatrix() + 0x30,
               *(char **)(*(char **)(obj + 0x15C) + 0xC) + 0x30);
    r = GetAttackCheckBoundaryRadius(obj);
    prim_DispWireSphere(D_004E5A90, 4, 4, r);
    do {
        gif_EndPacket();
    } while (0);
}
inline void SetAttackCheckBoundaryAttribute(char *a0, int a1) {
    *(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 8) = a1;
}
inline float GetAttackCheckBoundaryRadius(char *a0) {
    return *(float *)(*(char **)(*(char **)(a0 + 0x15C) + 0x870) + 0x20);
}
inline char *CreateAttackCheckBoundary(int *obj, float x, float y, float z, float r)
{
    AcbLayout lay = D_004E45C0;

    lay.pos.f[0] = x;
    lay.pos.f[1] = y;
    lay.pos.f[2] = z;
    lay.scale.f[0] = r;
    lay.obj = obj;
    *obj = 0;
    return createAttackCheckBoundaryGObj(&lay);
}
inline void actAttackCheckBoundaryStart(int *self)
{
    int *p = actInitialize(self);
    long long v;
    actInitialize_ext_charcter(self);
    _ACTWait(1);
    v = *(long long *)((char *)p + 0x18);
    v |= 1LL << 32;
    *(long long *)((char *)p + 0x18) = v;
}
INCLUDE_ASM("asm/nonmatchings/src/attackCheckBoundary", AttackCheckBoundaryBeforeFunc);
INCLUDE_ASM("asm/nonmatchings/src/attackCheckBoundary", InitAttackCheckBoundaryManagerGeo);
INCLUDE_ASM("asm/nonmatchings/src/attackCheckBoundary", AttackCheckBoundaryManagerGeo);
void AttackCheckBoundaryManagerDL(void) {}
inline int GetAttackCheckBoundaryManagerStatus(char *a0) {
    return *(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 8);
}
