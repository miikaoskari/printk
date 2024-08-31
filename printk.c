#include <stdio.h>
#include <stdarg.h>

int vprint()
{

    return 0;
}


int printk(char *buffer, unsigned int buflen, const char *fmt, ...)
{
    int ret;
    va_list args;
    va_start(args, fmt);

    ret = vprint();

    va_end(args);

    return ret;
}
