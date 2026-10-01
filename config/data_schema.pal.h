/*
 * config/data_schema.pal.h -- record types of the data-only ico2000.a members
 * whose consumers do not yet share a header that defines them.
 *
 * tools/gen_data_c.py includes this header in the C it writes for a member
 * whose row in config/data_schema.pal.txt names it. Each record is the layout
 * its readers fix; the field names come from those readers (named below).
 * When the record moves into its owner's header, the schema row names that
 * header instead and the record leaves this file. Types only: no member's
 * values are ever written here (docs/LEGAL.md).
 */
#ifndef DATA_SCHEMA_PAL_H
#define DATA_SCHEMA_PAL_H



/* camera-set: one camera data file name, 0x20 bytes. Readers:
 * ico2/omori/src/camera-ico2.c and camera-editor.c. Owner:
 * ico2/omori/include/camera-ico2.h. */
typedef struct { /* field names derived */
    char path[32]; /* 0x00, "camdata/..." */
} CameraSetFile; /* derived name */

/* unmapped_002ADBA0: one hint, 0x10 bytes. Reader:
 * ico2/omori/src/lws_kyomi.c (struct HintDef). Owner:
 * ico2/omori/include/lws_kyomi.h. */
typedef struct { /* field names derived */
    int stage;          /* 0x00, compared with stage_no */
    int no;             /* 0x04 */
    float time;         /* 0x08, seconds */
    unsigned int flags; /* 0x0C */
} HintDef; /* derived name */


/* attack-def: one attack kind, 0x24 bytes. Reader: ico2/omori/src/
 * attackhit.c (AttackKindEntry). Owner: ico2/omori/include/attackhit.h. */
typedef struct { /* field names derived */
    int word0;          /* 0x00 */
    int word4;          /* 0x04 */
    int word8;          /* 0x08 */
    int wordC;          /* 0x0C */
    int motion;         /* 0x10, the attacking motion */
    int node;           /* 0x14, GetFocusNodePos's node */
    float radius;       /* 0x18 */
    float power;        /* 0x1C */
    unsigned int flags; /* 0x20 */
} AttackKindEntry; /* derived name */

/* generator-sub-position: one safe position offset, 0x10 bytes. Reader:
 * ico2/omori/src/generator.c (SafePosOffset). Owner:
 * ico2/omori/include/generator.h. */
typedef struct { /* field names derived */
    float x;  /* 0x00 */
    float y;  /* 0x04 */
    float z;  /* 0x08 */
    int kind; /* 0x0C, matched with GObj+8 */
} SafePosOffset; /* derived name */





#endif /* DATA_SCHEMA_PAL_H */
