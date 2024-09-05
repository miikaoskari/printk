#include <stddef.h>
#include <stdarg.h>

typedef void (*putc_func_t)(char c);
static putc_func_t pputc = NULL;

void set_putc(putc_func_t func)
{
    pputc = func;
}

void pputs(const char *str)
{
    while (*str) {
        pputc(*str++);
    }
}

void printk(const char *format, ...)
{
    if (pputc == NULL) {
        return;
    }

    va_list args;
    va_start(args, format);

    while (*format) {
        if (*format == '%') {
            format++;
            switch (*format) {
                case 'c': {
                    char c = (char)va_arg(args, int);
                    pputc(c);
                    break;
                }
                case 's': {
                    const char *str = va_arg(args, const char *);
                    pputs(str);
                    break;
                }
                case 'd': {
                    int num = va_arg(args, int);
                    if (num < 0) {
                        pputc('-');
                        num = -num;
                    }
                    char buffer[10];
                    int i = 0;
                    do {
                        buffer[i++] = (num % 10) + '0';
                        num /= 10;
                    } while (num > 0);
                    while (i > 0) {
                        pputc(buffer[--i]);
                    }
                    break;
                }
                case 'x': {
                    unsigned int num = va_arg(args, unsigned int);
                    char buffer[8];
                    int i = 0;
                    do {
                        int digit = num % 16;
                        buffer[i++] = (digit < 10) ? (digit + '0') : (digit - 10 + 'a');
                        num /= 16;
                    } while (num > 0);
                    while (i > 0) {
                    pputc(buffer[--i]);
                    }
                    break;
                }
                default:
                    pputc('%');
                    pputc(*format);
                    break;
            }
        } else {
            pputc(*format);
        }
        format++;
    }

    va_end(args);
}
