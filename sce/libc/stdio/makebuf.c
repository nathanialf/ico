/* libc.a member makebuf.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include "common.h"
#include <reent.h>

struct D520 {
    char pad0[8];
    PObjBlk *blk; /* 0x8 */
};

extern void fiprintf();
extern void abort(void);

/* Only st_mode is reached here, at 0x04; the 0x70 size is what the ROM's
   0xB0 frame proves (locals 0x00..0x70, callee-saved homes above it).  The
   trailing bytes are padding, not an attested field layout. */
struct stat {
    short st_dev;          /* 0x00 */
    unsigned short st_ino; /* 0x02 */
    unsigned int st_mode;  /* 0x04 */
    char pad008[0x68];     /* 0x08 */
};

#define __SLBF 0x0001
#define __SNBF 0x0002
#define __SOPT 0x0400
#define __SNPT 0x0800
#define __SMOD 0x0080
#define S_IFMT 0xF000
#define S_IFCHR 0x2000
#define S_IFREG 0x8000
#define BUFSIZ 1024

extern int _fstat_r(Reent *ptr, int fd, struct stat *st);
extern void *_malloc_r(Reent *ptr, unsigned int size);
extern int isatty(int fd);
extern long __sseek(void *a0, int a1, int a2);
extern void _cleanup_r(Reent *ptr);

void __smakebuf(Fil *fp)
{
    unsigned int size;
    int couldbetty;
    void *p;
    struct stat st;

    if (fp->flags & __SNBF) {
        fp->bf.base = fp->p = fp->nbuf;
        fp->bf.size = 1;
        return;
    }
    if (fp->file < 0 || _fstat_r(fp->data, fp->file, &st) < 0) {
        couldbetty = 0;
        size = BUFSIZ;
        fp->flags |= __SNPT;
    } else {
        couldbetty = (st.st_mode & S_IFMT) == S_IFCHR;
        size = BUFSIZ;
        if ((st.st_mode & S_IFMT) == S_IFREG && fp->seek == (void *)__sseek) {
            fp->blksize = size;
            fp->flags |= __SOPT;
        } else {
            fp->flags |= __SNPT;
        }
    }
    if ((p = _malloc_r(fp->data, size)) == 0) {
        fp->flags |= __SNBF;
        fp->bf.base = fp->p = fp->nbuf;
        fp->bf.size = 1;
        return;
    }
    fp->data->cleanup = (void *)_cleanup_r;
    fp->flags |= __SMOD;
    fp->bf.base = fp->p = (unsigned char *)p;
    fp->bf.size = size;
    if (couldbetty && isatty(fp->file)) {
        fp->flags |= __SLBF;
    }
}
