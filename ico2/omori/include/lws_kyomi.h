/*
 * ico2/omori/include/lws_kyomi.h
 *
 * The declarations of what lws_kyomi.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef LWS_KYOMI_H
#define LWS_KYOMI_H

/* no argument in this build: the body sets a0 before reading it (0x239AA4)
   and bga_ApplyDObject's call (0x1F476C) passes none */
struct GObj *CreateKyomiGObj(void);
void SetParamKyomiGObj(struct GObj *gobj, float *root, float *param);

#endif /* LWS_KYOMI_H */
