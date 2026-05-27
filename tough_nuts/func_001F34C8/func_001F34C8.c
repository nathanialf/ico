#include "matching.h"
#include "regpin.h"

extern int D_00632010;
extern int func_0013A0F8(int handle, int size, const char *file, int line);
extern int func_001B7FE8(int a, int b, int c, int d, int e, int f, int g, int h);
extern void func_0019F4E8(int *a0, int *a1);
extern void func_00105F00(int *arg, int b);
extern const char D_0061A850[16];
extern float D_004C6330[4];
struct E36 { char pad[0xC]; int field; char pad2[0x14]; };
extern struct E36 D_006124F8[];

typedef struct { long long d[8]; } WBody;
typedef struct __attribute__((packed)) { long long w; } WUB8;

void func_001F34C8(int *self, int i, int arg1)
{
    struct {
        int *self;
        int i;
        int pad[2];
        WBody body;
    } req;
    WBody body2;
    register int *src REG("$18") = (int *)arg1;
    register int n REG("$17");
    int *buf = (int *)((int *)self[0x15C / 4])[0x800 / 4];
    int flag = (src[0x30 / 4] & 0xFF00) ? 5 : 4;
    float scale = 0.0f;

    req.self = self;
    req.i = i;
    req.body = *(WBody *)src;
    ((int *)&req.body)[0x30 / 4] = flag;

    buf[0x50 / 4] = 1;
    buf[0x54 / 4] = func_0013A0F8(D_00632010, 4, D_0061A850, 0x2C7);

    for (n = 0; n < 1; n++) {
        int idx = buf[0];
        int *obj;
        D_004C6330[2] = ((float *)&D_006124F8[idx])[0] * (float)n / scale;
        obj = (int *)func_001B7FE8(0xA, 0x45, -1, n == 0, (int)&req.body, -1, 7, 0);
        func_0019F4E8(obj, (int *)&req);
        func_00105F00((int *)(obj[0x15C / 4] + 0xA0), (int)D_004C6330);
        ((int *)buf[0x54 / 4])[n] = (int)obj;
    }

    body2 = *(WBody *)src;
    ((int *)&body2)[0x30 / 4] = 0xD;
    {
        int *obj2 = (int *)func_001B7FE8(0x2D, 9, -1, 0, (int)&body2, -1, 7, 0);
        *(WUB8 *)(obj2[0x15C / 4]) = *(WUB8 *)&req;
        buf[0x5C / 4] = (int)obj2;
    }
}
