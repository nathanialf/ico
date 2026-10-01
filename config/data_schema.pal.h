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

/* act-intrlist: one actor mail entry, 0x18 bytes; lists end at the entry
 * whose kind is 429. Readers: ico2/fumi/src/act.c (BeforeFunc,
 * act_check_intr_list, act_check_mail, as IntrMail) and
 * ico2/fumi/src/commonact.c (ACTRunIntrCorrect, as IntrRec). */
typedef struct { /* field names derived */
    void (*motion)(int);                            /* 0x00, motion thread 21 */
    void (*extra)(int);                             /* 0x04, motion thread 22 */
    void (*handler)(char *self, int id, void *arg); /* 0x08, every frame the mail is held */
    void (*accept)(char *self, int id, void *arg);  /* 0x0C, when the mail is accepted */
    unsigned short kind;                            /* 0x10, the mail id */
    short mode;                                     /* 0x12, the act mode it switches to */
    unsigned int flags;                             /* 0x14, bit 18: entry live */
} IntrMail; /* derived name */

/* obj-layout: one placed object of a stage, 0x4C bytes, indexed by the
 * object's GObj+8. The layout of ico2/common/include/typedef.h's GenGeo, with
 * the types the member's values need: 0x24 holds the object's act function in
 * 498 rows and 0x28 the address of a GObj pointer in one, and 0x34 and 0x3C
 * hold words where GenGeo has pad bytes. Readers: ico2/omori/src/generator.c
 * (GVGeo2: rot, enemyKind, reviveCount, motherLabel, kind), objact.c (0x34),
 * ebrain.c and ico2/fumi/src/enemy_act.c (flags), ico2/fumi/src/act.c
 * (actChangeActMain, 0x40), way_sys.c and motionManager.c (kind). */
typedef struct { /* field names derived */
    float scale[3];             /* 0x00 */
    float rot[3];               /* 0x0C */
    float pos[3];               /* 0x18 */
    void (*actMain)(int);       /* 0x24, the object's act function */
    char **gobjHolder;          /* 0x28, receives the object's GObj */
    int mdl;                    /* 0x2C */
    int enemyKind;              /* 0x30, the enemy kind a generator calls */
    int action;                 /* 0x34, index into obj-action's objAction */
    int word38;                 /* 0x38 */
    int word3C;                 /* 0x3C */
    unsigned short procMask;    /* 0x40, shifted left 10 for isysGObjProcAddS */
    short reviveCount;          /* 0x42, enemies left to revive, -1 for unlimited */
    unsigned short motherLabel; /* 0x44, the label of the generator the object belongs to */
    unsigned char kind;         /* 0x46, the object kind */
    unsigned char byte47;       /* 0x47 */
    unsigned int flags;         /* 0x48 */
} GenGeo; /* derived name */



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
