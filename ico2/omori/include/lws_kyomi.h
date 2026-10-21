/*
 * ico2/omori/include/lws_kyomi.h
 *
 * The declarations of what lws_kyomi.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef LWS_KYOMI_H
#define LWS_KYOMI_H

struct GObj *CreateKyomiGObj(void);
void SetParamKyomiGObj(struct GObj *gobj, float *root, float *param);

#endif /* LWS_KYOMI_H */
