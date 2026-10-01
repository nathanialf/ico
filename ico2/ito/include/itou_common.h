/*
 * ico2/ito/include/itou_common.h, the `ito` programmer's shared header: the
 * degree and radian conversions act_bird, queen, gather_effect and lightning
 * use, and the mail queue a game object carries.
 */
#ifndef ITOU_COMMON_H
#define ITOU_COMMON_H

/* degrees to radians */
static __inline__ float degrees_to_radians(float deg) /* derived name */
{
    return deg * 6.2831855f / 360.0f;
}

/* radians to degrees */
static __inline__ float radians_to_degrees(float rad) /* derived name */
{
    return rad * 360.0f / 6.2831855f;
}

/* The mail queue a game object carries at 0x54: the mails sent to it since
   its last frame and what each one carries. */
typedef struct GObjMailEntry { /* field names derived */
    unsigned int mail;         /* 0x0 */
    void *data;                /* 0x4 */
} GObjMailEntry;

typedef struct GObjMailQueue { /* field names derived */
    char pad0[4];              /* 0x00 */
    int num;                   /* 0x04 */
    GObjMailEntry e[1];        /* 0x08 */
} GObjMailQueue;

#endif /* ITOU_COMMON_H */
