#include "bsp_abit_printf.h"

#ifdef __GNUC__
    #define PUTCHAR_TROTOTYPE int __io_putchar(int ch)
#else
    #define PUTCHAR_TROTOTYPE int fputc(int ch, FILE *f)
#endif

PUTCHAR_TROTOTYPE
{
    while((USART1->SR & 0x40) == RESET);
    USART1->DR = (uint8_t) ch;

    return ch;
}

int _write(int fd, char *pBuffer, int size)
{
    for(int i = 0; i < size; i++)
        __io_putchar(*pBuffer++);
    
    return size;
}