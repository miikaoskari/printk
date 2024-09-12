#ifndef PRINTK_H
#define PRINTK_H

#include <stdarg.h>
#include <stdint.h>

typedef void (*putc_func_t)(char c);

void set_putc(putc_func_t func);
void printk(const char *format, ...);

#endif /* PRINTK_H */
