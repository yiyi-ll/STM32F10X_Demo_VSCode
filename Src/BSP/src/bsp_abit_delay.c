#include "bsp_abit_delay.h"

static uint8_t beat_us = 0;
static uint16_t beat_ms = 0;

void bsp_abit_delay_init(uint8_t SYSTICK)
{
#ifdef SUPPORT_OS
    // CoreDebug->DEMCR &= ~(CoreDebug_DEMCR_TRCENA_Msk);
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
    // DWT_CYCCNT = 0;
    // DWT_CTRL &= ~(DWT_CTRL_CYCCNTENA_Msk);
    // DWT_CTRL |= DWT_CTRL_CYCCNTENA_Msk;
    DWT->CYCCNT = 0;
    DWT->CTRL |= (1 << 0);
#else
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);

    beat_us = SYSTICK / 8;
    beat_ms = (uint16_t)beat_us * 1000;
#endif
}

static uint32_t bsp_abit_get_cnt()
{
    return (uint32_t)DWT->CYCCNT;
}

void bsp_abit_delay_us(uint32_t nus)
{
    uint32_t ticks = 0;
    uint32_t told = 0;
    uint32_t tnow = 0;
    uint32_t tcnt = 0;

#ifdef SUPPORT_OS
    ticks = nus * (SystemCoreClock / 1000000);
    told = DWT->CYCCNT;

    while(1)
    {
        tnow = DWT->CYCCNT;
        if(tnow != told)
        {
            if(tnow > told)
                tcnt += tnow - told;
            else
                tcnt += TICKSMAX - told + tnow;
            
            told = tnow;

            if(tcnt >= ticks)
                break;
        }
    }

    // while(DWT->CYCCNT - start < temp);
#else
    SysTick->LOAD = beat_us * nus;
    SysTick->VAL = 0x00;
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;

    do
    {
        temp = SysTick->CTRL;
    } while ((temp & 0x01) && !(temp & (1 << 16)));
    
    SysTick->CTRL &= ~(SysTick_CTRL_ENABLE_Msk);
    SysTick->VAL = 0x00;
#endif
}

void bsp_abit_delay_ms(uint32_t nms)
{
    uint32_t ticks = 0;
    uint32_t told = 0;
    uint32_t tnow = 0;
    uint32_t tcnt = 0;

#ifdef SUPPORT_OS
    ticks = nms * (SystemCoreClock / 1000000) * 1000;
    told = DWT->CYCCNT;

    while(1)
    {
        tnow = DWT->CYCCNT;
        if(tnow != told)
        {
            if(tnow > told)
                tcnt += tnow - told;
            else
                tcnt += TICKSMAX - told + tnow;
            
            told = tnow;

            if(tcnt >= ticks)
                break;
        }
    }

    // while(DWT->CYCCNT - start < temp);
#else
    SysTick->LOAD = (uint32_t)beat_ms * nms;
    SysTick->VAL = 0x00;
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;

    do
    {
        temp = SysTick->CTRL;
    } while ((temp & 0x01) && !(temp & (1 << 16)));
    
    SysTick->CTRL &= ~(SysTick_CTRL_ENABLE_Msk);
    SysTick->VAL = 0x00;
#endif
}