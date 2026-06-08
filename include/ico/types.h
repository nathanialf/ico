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
typedef struct Obj7F0  Obj7F0;   /* *(Sub15C + 0x7F0) — shared geometry/model obj (~25 TUs) */
typedef struct GeoNode GeoNode;  /* *(Obj7F0  + 0x20) */
typedef struct GeoSub  GeoSub;   /* *(GeoNode + 0x8)  */

struct GObj {
    char    _pad0[0x8];
    int     f_8;              /* 0x8   */
    char    _pad_c[0x150];    /* 0xC .. 0x15B */
    Sub15C *p_15C;            /* 0x15C — sub-object pointer */
    char    _pad160[0x4];
    void   *p_164;           /* 0x164 — actor/action-state object (engine-wide,
                                polymorphic target; type each TU's view locally) */
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
    char    _pad78[0x4];
    int     f_7C; /* 0x7C */
    char    _pad80[0x4];
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
    char    _pad27C[0xF4];
    int     f_370; /* 0x370 */
    char    _pad374[0x64];
    int     f_3D8; /* 0x3D8 */
    char    _pad3DC[0xB4];
    int     f_490; /* 0x490 — char-status index */
    char    _pad494[0xC];
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
    char    _pad530[0x4];
    int     f_534; /* 0x534 */
    int     f_538; /* 0x538 */
    int     f_53C; /* 0x53C */
    int     f_540; /* 0x540 */
    char    _pad544[0x2AC];
    Obj7F0 *p_7F0; /* 0x7F0 — cage-fix geometry */
    char    _pad7F4[0xC];
    void   *p_800; /* 0x800 — untyped (no consumers yet) */
    char    _pad804[0x10];
    int     f_814; /* 0x814 */
};

/* Geometry/model object hanging off Sub15C + 0x7F0. The p_7F0 field is read
 * in ~25 TUs (weapon, torch, boy, rope, enemy, box, spider, chain, ...), so
 * this is shared-core; only cageFix.c walks the +0x20 matrix chain so far.
 * Fields grow as TUs are typed; names are offset-derived (no string evidence). */
struct GeoSub {
    void   *p_0;          /* 0x0 — object matrix passed to TurnObjectMatrix */
};

struct GeoNode {
    char    _pad0[0x8];
    GeoSub *p_8;          /* 0x8 */
};

struct Obj7F0 {
    void    *p_0;         /* 0x00 — model / geometry node pointer */
    int      f_4;         /* 0x04 */
    int      f_8;         /* 0x08 */
    int      f_C;         /* 0x0C */
    int      f_10;        /* 0x10 */
    char     _pad14[0xC];
    GeoNode *p_20;        /* 0x20 */
    char     _pad24[0x18];
    float    f_3C;        /* 0x3C */
    int      f_40;        /* 0x40 */
};

#endif /* ICO_TYPES_H */
