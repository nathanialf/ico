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
    int     f_C;  /* 0xC */
    char    _pad10[0x64];
    int     f_74;  /* 0x74 */
    char    _pad78[0xC];
    int     f_84;  /* 0x84 */
    char    _pad88[0x158];
    int     f_1E0;  /* 0x1E0 */
    char    _pad1E4[0x2BC];
    int     f_4A0;  /* 0x4A0 — index (motionOrient) */
    char    _pad4A4[0x8];
    int     f_4AC;  /* 0x4AC */
    char    _pad4B0[0x8];
    int     f_4B8;  /* 0x4B8 */
    char    _pad4BC[0x1C];
    int     f_4D8;  /* 0x4D8 */
    char    _pad4DC[0x8];
    int     f_4E4;  /* 0x4E4 */
    char    _pad4E8[0x44];
    int     f_52C;  /* 0x52C */
    char    _pad530[0x2D0];
    Obj800 *p_800;  /* 0x800 */
    char    _pad804[0x10];
    int     f_814;  /* 0x814 */
};

struct Obj800 {
    int     f_0;  /* 0x0 */
    int     f_4;  /* 0x4 */
    char    _pad8[0x4];
    int     f_C;  /* 0xC */
    int     f_10;  /* 0x10 */
    char    _pad14[0x8];
    int     f_1C;  /* 0x1C */
    int     f_20;  /* 0x20 */
    void   *p_24;  /* 0x24 */
    int     f_28;  /* 0x28 */
    char    _pad2C[0x24];
    int     f_50;  /* 0x50 */
    char    _pad54[0x4];
    int     f_58;  /* 0x58 */
    char    _pad5C[0x44];
    int     f_A0;  /* 0xA0 */
    char    _padA4[0x6C];
    int     f_110;  /* 0x110 */
    int     f_114;  /* 0x114 */
    char    _pad118[0x28];
    int     f_140;  /* 0x140 */
};

#endif /* ICO_TYPES_H */
