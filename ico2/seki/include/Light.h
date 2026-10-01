/*
 * ico2/seki/include/Light.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what Light.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef LIGHT_H
#define LIGHT_H

#include <libvu0.h>

struct GObj;
struct Sub15C;

/* RECONSTRUCTION: the per-object light matrix record at *(Sub15C + 0x874)
 * (typedef.h's Sub15C keeps the slot as void *).  Rung: ROM bytes for every
 * offset, the reading translation units for the roles; names are role names
 * (no string evidence).  light_MakeLightMatrix builds the normal light
 * matrix at 0x00 from the three directions at 0x80 and the colour matrix at
 * 0x40 from the colours at 0xB0 and the ambient at 0xE0 (its last word, 0xEC,
 * is the scale), and tests the mode at 0xF0; light_getNearLight fills the
 * directions and colours; DObj.c copies the mode and tests it against 4,
 * Packet.c hands it to pac_makePacket and RegistPacket.c gates the light
 * packet on it.  The members are the SDK's 16-byte aligned vector types:
 * with that alignment gcc adds a row's variable offset to the record base
 * before the member displacement (expr.c, expand_assignment), which is the
 * ROM's one base-first addu shared by light_getNearLight's 0x8C and 0xBC
 * stores; a 4-byte aligned layout adds the displacement first and costs a
 * second address register (measured). */
typedef struct LightMatrix {
    sceVu0FMATRIX normal;  /* 0x00 */
    sceVu0FMATRIX color;   /* 0x40 */
    sceVu0FVECTOR dir[3];  /* 0x80 */
    sceVu0FVECTOR col[3];  /* 0xB0 */
    sceVu0FVECTOR ambient; /* 0xE0 */
    int mode;              /* 0xF0 */
} LightMatrix;

/* obj-light: one object light, 0x10 bytes. Reader: ico2/seki/src/Light.c
 * (float [][4]: the colour scaled by 1/256). */
typedef struct {  /* field names derived */
    float col[3]; /* 0x00, 0..255 */
    float range;  /* 0x0C */
} ObjLight;

/* the object light table light_AddLight indexes by the object's light number */
extern const ObjLight objectLight[];

struct Light; /* Light.c's light list node */

struct AmbientVolume; /* Light.c's ambient volume node */

struct AmbientVolume *light_AddAmbientObject(int obj);
struct Light *light_AddLight(struct GObj *self, int b, int kind);
void light_DispVolume(void);
void light_DrawCursor(float *dir, int mode);
void light_GetColorAnalog(float *col);
void light_KillAllFixLight(void);
void light_MakeLightMatrix(struct Sub15C *a, int b);
void light_getAmbientLight(struct Sub15C *a, int b);
void light_getNearLight(struct Sub15C *a, int b);
void light_killLinkAmbient(struct AmbientVolume *p);
void light_killLinkLight(struct Light *p);
void light_resetFlatLight(void);
int light_Tool(void);
void light_ResetLight(void);

#endif /* LIGHT_H */
