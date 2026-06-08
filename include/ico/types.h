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

/* The 0x15C sub-object slot is an INT handle the engine casts to a pointer at
 * use — not a clean Sub15C*. Reading it int-typed reproduces the developer's
 * TBAA: it may-alias adjacent int writes, so the load reloads (not hoisted),
 * matching byte-for-byte WITHOUT the per-function int-typed-reload hacks
 * (COOKBOOK §8.22). Pointer-chain users still match (no aliasing trigger).
 * Use this accessor for 0x15C; keep p_15C in the struct for layout only. */
#define GOBJ_SUB(o)  ((Sub15C *)*(int *)&((GObj *)(o))->p_15C)

typedef struct GObj    GObj;
typedef struct Sub15C  Sub15C;   /* *(GObj   + 0x15C) — per-object sub state */
typedef struct Obj800  Obj800;   /* *(Sub15C + 0x800) */
typedef struct Obj7F0  Obj7F0;   /* *(Sub15C + 0x7F0) — cage-fix geometry */
typedef struct GeoNode GeoNode;  /* *(Obj7F0  + 0x20) */
typedef struct GeoSub  GeoSub;   /* *(GeoNode + 0x8)  */

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
    char    _pad0[0x4];
    int     f_4; /* 0x4 */
    int     f_8; /* 0x8 */
    int     f_C; /* 0xC */
    char    _pad10[0x8];
    int     f_18; /* 0x18 */
    int     f_1C; /* 0x1C */
    int     f_20; /* 0x20 */
    int     f_24; /* 0x24 */
    int     f_28; /* 0x28 */
    char    _pad2C[0x4];
    int     f_30; /* 0x30 */
    char    _pad34[0x8];
    int     f_3C; /* 0x3C */
    char    _pad40[0x4];
    int     f_44; /* 0x44 */
    char    _pad48[0x8];
    int     f_50; /* 0x50 */
    int     f_54; /* 0x54 */
    int     f_58; /* 0x58 */
    char    _pad5C[0x10];
    char    f_6C; /* 0x6C */
    char    _pad6D[0x3];
    int     f_70; /* 0x70 */
    int     f_74; /* 0x74 */
    char    _pad78[0xC];
    int     f_84; /* 0x84 */
    int     f_88; /* 0x88 */
    char    _pad8C[0x44];
    int     f_D0; /* 0xD0 */
    char    _padD4[0xAC];
    int     f_180; /* 0x180 */
    char    _pad184[0x10];
    int     f_194; /* 0x194 */
    int     f_198; /* 0x198 */
    int     f_19C; /* 0x19C */
    char    _pad1A0[0x24];
    int     f_1C4; /* 0x1C4 */
    int     f_1C8; /* 0x1C8 */
    char    _pad1CC[0x14];
    int     f_1E0; /* 0x1E0 */
    char    _pad1E4[0x8C];
    int     f_270; /* 0x270 */
    int     f_274; /* 0x274 */
    int     f_278; /* 0x278 */
    char    _pad27C[0x15C];
    int     f_3D8; /* 0x3D8 */
    char    _pad3DC[0xC4];
    int     f_4A0; /* 0x4A0 index */
    char    _pad4A4[0x8];
    int     f_4AC; /* 0x4AC */
    char    _pad4B0[0x8];
    int     f_4B8; /* 0x4B8 */
    char    _pad4BC[0x1C];
    int     f_4D8; /* 0x4D8 */
    char    _pad4DC[0x8];
    int     f_4E4; /* 0x4E4 */
    char    _pad4E8[0x44];
    int     f_52C; /* 0x52C */
    char    _pad530[0x2C0];
    Obj7F0 *p_7F0; /* 0x7F0 — cage-fix geometry */
    char    _pad7F4[0xC];
    Obj800 *p_800; /* 0x800 */
    char    _pad804[0x10];
    int     f_814; /* 0x814 */
};

struct Obj800 {
    int     f_0; /* 0x0 */
    int     f_4; /* 0x4 */
    int     f_8; /* 0x8 */
    int     f_C; /* 0xC */
    int     f_10; /* 0x10 */
    int     f_14; /* 0x14 */
    char    _pad18[0x4];
    int     f_1C; /* 0x1C */
    int     f_20; /* 0x20 */
    void   *p_24; /* 0x24 */
    int     f_28; /* 0x28 */
    char    _pad2C[0x18];
    int     f_44; /* 0x44 */
    char    _pad48[0x8];
    int     f_50; /* 0x50 */
    char    _pad54[0x4];
    int     f_58; /* 0x58 */
    char    _pad5C[0x4];
    char    f_60; /* 0x60 */
    char    _pad61[0x3F];
    int     f_A0; /* 0xA0 */
    char    _padA4[0x6C];
    int     f_110; /* 0x110 */
    int     f_114; /* 0x114 */
    char    _pad118[0x28];
    int     f_140; /* 0x140 */
    char    _pad144[0x7C];
    int     f_1C0; /* 0x1C0 */
    int     f_1C4; /* 0x1C4 */
    int     f_1C8; /* 0x1C8 */
    char    _pad1CC[0xA4];
    int     f_270; /* 0x270 */
    char    _pad274[0x4];
    int     f_278; /* 0x278 */
};

/* Cage-fix geometry, reached via Sub15C + 0x7F0 (sugipon/cageFix.c).
 * Field names are offset-derived (no binary string evidence). */
struct GeoSub {
    void   *p_0;          /* 0x0 — object matrix passed to TurnObjectMatrix */
};

struct GeoNode {
    char    _pad0[0x8];
    GeoSub *p_8;          /* 0x8 */
};

struct Obj7F0 {
    void    *p_0;         /* 0x00 — model / CD-file pointer */
    char     _pad4[0x1C];
    GeoNode *p_20;        /* 0x20 */
    char     _pad24[0x18];
    float    f_3C;        /* 0x3C */
    int      f_40;        /* 0x40 */
};

#endif /* ICO_TYPES_H */
