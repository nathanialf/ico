#ifndef ICO_TYPES_H
#define ICO_TYPES_H

/*
 * Engine object shapes recovered from the binary via
 * tools/dump_all_struct_shapes.py (offsets/widths from load mnemonics).
 *
 * `GObj` = the game object passed as `self` to per-object functions. The
 * name is the engine's own term, re-derived from the public PAL ICO-decomp's
 * Char/GObj list API (GetCharGObjList / MakeCharGObjList) — a reference, not
 * a verbatim copy. Sub-object struct and field names are MECHANICAL
 * (offset-derived); a field gets a meaningful name only when the binary gives
 * evidence (e.g. a debug string). Padding is explicit so every field sits at
 * its exact recovered offset — a wrong offset is caught by the SHA-1 gate.
 *
 * Structs grow as TUs are typed; only add a field with a verified access.
 */

typedef struct GObj    GObj;
typedef struct Sub15C  Sub15C;   /* *(GObj   + 0x15C) — per-object sub state */
typedef struct Obj800  Obj800;   /* *(Sub15C + 0x800) */

struct GObj {
    char    _pad0[0x8];
    int     f_8;              /* 0x8   */
    char    _pad_c[0x150];    /* 0xC .. 0x15B */
    Sub15C *p_15C;            /* 0x15C — sub-object pointer */
    char    _pad160[0x4];
    int     f_164;            /* 0x164 */
    char    _pad168[0x4];
    int     f_16C;            /* 0x16C */
};

struct Sub15C {
    char    _pad0[0xC];
    int     f_C;              /* 0xC   */
    char    _pad10[0x64];     /* 0x10 .. 0x73 */
    int     f_74;             /* 0x74  */
    char    _pad78[0x428];    /* 0x78 .. 0x49F */
    int     f_4A0;            /* 0x4A0 — index (motionOrient stride base) */
    char    _pad4a4[0x35C];   /* 0x4A4 .. 0x7FF */
    Obj800 *p_800;            /* 0x800 */
    char    _pad804[0x10];    /* 0x804 .. 0x813 */
    int     f_814;            /* 0x814 */
};

struct Obj800 {
    char    _pad0[0x4];
    int     f_4;              /* 0x4   */
    char    _pad8[0x4];       /* 0x8 .. 0xB */
    int     f_C;              /* 0xC   */
    int     f_10;             /* 0x10  */
    char    _pad14[0x8];      /* 0x14 .. 0x1B */
    int     f_1C;             /* 0x1C  */
    int     f_20;             /* 0x20  */
    void   *p_24;             /* 0x24  */
    int     f_28;             /* 0x28  */
    char    _pad2c[0x2C];     /* 0x2C .. 0x57 */
    int     f_58;             /* 0x58  */
    char    _pad5c[0xB4];     /* 0x5C .. 0x10F */
    int     f_110;            /* 0x110 */
    int     f_114;            /* 0x114 */
    char    _pad118[0x28];    /* 0x118 .. 0x13F */
    int     f_140;            /* 0x140 */
};

#endif /* ICO_TYPES_H */
