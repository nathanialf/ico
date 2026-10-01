/* libc.a member stdio.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include <stdlib.h>
#include <string.h>
#include <reent.h>
#include <libc_internal.h>

#define __SAPP 0x0100
#define __SOFF 0x1000
#define SEEK_END 2

int __sread(void *cookie, char *buf, int n)
{
    Fil *fp = (Fil *)cookie;
    int ret;

    ret = _read_r(fp->data, fp->file, buf, n);
    if (ret >= 0) {
        fp->offset += ret;
    } else {
        fp->flags &= ~__SOFF;
    }
    return ret;
}

int __swrite(void *cookie, char *buf, int n)
{
    Fil *fp = (Fil *)cookie;

    if (fp->flags & __SAPP) {
        (void)_lseek_r(fp->data, fp->file, 0, SEEK_END);
    }
    fp->flags &= ~__SOFF;
    return _write_r(fp->data, fp->file, buf, n);
}

long __sseek(void *cookie, long offset, int whence)
{
    Fil *fp = (Fil *)cookie;
    long ret;

    ret = _lseek_r(fp->data, fp->file, offset, whence);
    if (ret == -1L) {
        fp->flags &= ~__SOFF;
    } else {
        fp->flags |= __SOFF;
        fp->offset = ret;
    }
    return ret;
}

int __sclose(void *cookie)
{
    Fil *fp = (Fil *)cookie;

    return _close_r(fp->data, fp->file);
}
