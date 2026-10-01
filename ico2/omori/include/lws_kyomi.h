/*
 * ico2/omori/include/lws_kyomi.h
 *
 * The declarations of what lws_kyomi.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef LWS_KYOMI_H
#define LWS_KYOMI_H

/* one row of hintTable, the data-only member that holds the hints: the stage
 * and number a hint belongs to, its time and its flags.  It differs from
 * lws_kyomi.c's per-GObj HintInfo in one field: time is a float here
 * (seconds), an int there (frames); CreateKyomiGObj converts one into the
 * other. */
struct HintDef { /* field names derived */
    int stage;
    int no;
    float time;
    int flags;
};

extern struct HintDef hintTable[]; /* derived name */
struct GObj *CreateKyomiGObj(int no);
void DebugHintStart(struct GObj *gobj);
void FinishHint(int no);
char *GetBuffHintSaveInfo(void);
int GetSizeHintSaveInfo(void);
void Hint_Init(void);
int IsTopHint(struct GObj *gobj);
void MakeHintSaveInfo(void);
void ReadHintSaveInfo(void);
void SetParamKyomiGObj(struct GObj *gobj, float *root, float *param);
void SleepHint(int no);
void WakeupHint(int no);

#endif /* LWS_KYOMI_H */
