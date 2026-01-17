#include "core/uprint.h"

static Comm_Interface_t *uprint_comm = NULL;

static void uprint_send(char c)
{
    uprint_comm->send((uint8_t *)&c, 1);
}

static void uprint_puts(const char *s)
{
    while(*s) uprint_send(*s++);
}

static void uprint_putu(uint32_t n, uint8_t base)
{
    char buf[12];
    char *p = buf + sizeof(buf);

    const char *digits = "0123456789ABCDEF";

    *(--p) = '\0';
    if(n == 0)
    {
        *(--p) = '0';
    }else
    {
        while(n){
            *(--p) = digits[n % base];
            n /= base;
        }
    }

    uprint_puts(p);
}

static void uprint_puti(int32_t n)
{
    if(n < 0)
    {
        uprint_send('-');
        n = -n;
    }
    uprint_putu(n, 10);
}

void uprint_setup(Comm_Interface_t *comm)
{
    uprint_comm = comm;
}

void uprint(const char *fmt, ...)
{
    if(uprint_comm == NULL) return;

    va_list args;
    va_start(args, fmt);
    while(*fmt)
    {
        if(*fmt == '%')
        {
            switch (*(++fmt))
            {
                case 'd': uprint_puti(va_arg(args, int)); break;
                case 'u': uprint_putu(va_arg(args, unsigned), 10); break;
                case 'x': uprint_putu(va_arg(args, unsigned), 16); break;
                case 's': uprint_puts(va_arg(args, char*)); break;
                case 'c': uprint_send(va_arg(args, int)); break;
                case '%': uprint_send('%'); break;
                default:  uprint_send(*fmt); break;
            }
            fmt++;
        }else
        {
            uprint_send(*fmt++);
        }
    }

    va_end(args);
}