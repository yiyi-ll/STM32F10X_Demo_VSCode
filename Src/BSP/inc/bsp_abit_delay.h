#ifndef __BSP_ABIT_DELAY_H
#define __BSP_ABIT_DELAY_H

#include "misc.h"
#include "system_stm32f10x.h"

#ifndef SUPPORT_OS
#define SUPPORT_OS              1
#endif

#ifdef SUPPORT_OS
#include "core_cm3.h"
#endif

// #define DWT_CTRL                *(volatile uint32_t *)0xE0001000
// #define DWT_CYCCNT              *(volatile uint32_t *)0xE0001004
// #define DWT_CTRL_CYCCNTENA_Pos  0
// #define DWT_CTRL_CYCCNTENA_Msk  (1 << 0)

typedef struct
{
    __IO uint32_t CTRL;
    __IO uint32_t CYCCNT;
} DWT_Type;

#define DWT_BASE                    (0xE0001000)  
#define DWT                         ((DWT_Type *)DWT_BASE)
#define TICKSMAX                    (0xFFFFFFFF) 

void bsp_abit_delay_init(uint8_t SYSTICK);

void bsp_abit_delay_us(uint32_t nus);

void bsp_abit_delay_ms(uint32_t nms);

#endif //__BSP_ABIT_DELAY_H