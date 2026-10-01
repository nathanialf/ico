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

/* motion-def: one frame-timed trigger of a motion, a frame and a number
 * (ico2/sugipon/src/frameDependSequence.c, FDSSlot). */
typedef struct { /* field names derived */
    float t; /* 0x00, the frame */
    int no;  /* 0x04 */
} FDSSlot; /* derived name */

/* motion-def: one motion kind, 0x194 bytes, indexed by the motion id at
 * Sub15C+0x4A0. Readers: frameDependSequence.c (FDSRecord: eff, se, vib, the
 * weapon frame), motionOrientManager.c (name, rootUpdateMode, the shift and
 * trigger ranges, playMode, palSpeedRatio, interpFrames, playSpeedRatio,
 * blendKind), motionViewer.c (the shift range), motionFileManager.c
 * (node_id), motionManager2.c (rate0, rate1), ico2/fumi/src/act-game.c
 * (the priority-input frames, modeBits, flags), commonact.c (the direction
 * frames). */
typedef struct { /* field names derived */
    FDSSlot eff[12];          /* 0x000, particle effects */
    FDSSlot se[12];           /* 0x060, sound effects */
    char name[48];            /* 0x0C0 */
    FDSSlot vib[2];           /* 0x0F0, pad vibrations */
    int word100;              /* 0x100 */
    int word104;              /* 0x104 */
    int word108;              /* 0x108 */
    int word10C;              /* 0x10C */
    int word110;              /* 0x110 */
    int word114;              /* 0x114 */
    int rootUpdateMode;       /* 0x118 */
    int word11C;              /* 0x11C */
    float float120;           /* 0x120 */
    int word124;              /* 0x124 */
    float float128;           /* 0x128 */
    int word12C;              /* 0x12C */
    int word130;              /* 0x130 */
    int node_id;              /* 0x134 */
    float weaponFrame;        /* 0x138 */
    int shiftStart;           /* 0x13C */
    int shiftLength;          /* 0x140 */
    int triggerStart;         /* 0x144 */
    int triggerEnd;           /* 0x148 */
    int trigger2Start;        /* 0x14C */
    int playMode;             /* 0x150, 1 loops */
    int trigger2End;          /* 0x154 */
    float float158;           /* 0x158 */
    float palSpeedRatio;      /* 0x15C, applied when systemStatus[0] is set */
    float rate0;              /* 0x160 */
    float interpFrames;       /* 0x164 */
    float rate1;              /* 0x168 */
    int word16C;              /* 0x16C */
    int word170;              /* 0x170 */
    float playSpeedRatio;     /* 0x174 */
    int blendKind;            /* 0x178, index into blendMotionKind, 320 for none */
    int word17C;              /* 0x17C */
    short priInputBegin;      /* 0x180 */
    short girlDirFrames;      /* 0x182 */
    short priInputEnd;        /* 0x184 */
    short dirFrames;          /* 0x186 */
    unsigned int modeBits;    /* 0x188 */
    unsigned int flags;       /* 0x18C */
    unsigned int flags2;      /* 0x190 */
} MotionRec; /* derived name */

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


/* enemy-def: one enemy kind, 0x1C bytes. Reader: ico2/sugipon/src/enemy.c
 * (EnemyDef). Owner: ico2/sugipon/include/enemy.h. */
typedef struct { /* field names derived */
    int model;         /* 0x00, the model id, 0x610 for none */
    int particle;      /* 0x04, the particle object, -1 for none */
    float life;        /* 0x08 */
    float float0C;     /* 0x0C */
    float scale;       /* 0x10 */
    float dodge;       /* 0x14 */
    unsigned int attr; /* 0x18, paraIndex in bits 0-7, flyType 8-9, battleType 10-11 */
} EnemyDef; /* derived name */

/* layout-cloth-def: one laid-out cloth, 0x68 bytes. Readers:
 * ico2/sugipon/src/attackCheckBoundary.c (LayoutClothDef), flag.c. Owner:
 * ico2/sugipon/include/attackCheckBoundary.h. */
typedef struct { /* field names derived */
    char name[32];     /* 0x00 */
    float pt[4][3];    /* 0x20 */
    int kind;          /* 0x50, the cloth type in the low four bits */
    unsigned int attr; /* 0x54, ClothAttr: gen_data_c parses no enum, so the
                          reader's enum type stays in attackCheckBoundary.c */
    int rows;          /* 0x58 */
    int count;         /* 0x5C, the columns, and the boundaries a manager lays out */
    float length;      /* 0x60 */
    float weight;      /* 0x64 */
} LayoutClothDef; /* derived name */


#endif /* DATA_SCHEMA_PAL_H */
