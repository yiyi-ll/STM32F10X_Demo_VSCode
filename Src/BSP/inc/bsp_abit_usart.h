#ifndef __BSP_ABIT_USART_H
#define __BSP_ABIT_USART_H

#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_rcc.h"

#define USART_TX        GPIO_Pin_9
#define USART_RX        GPIO_Pin_10

void bsp_abit_usart_init(uint32_t baund);

#endif //__BSP_ABIT_USART_H